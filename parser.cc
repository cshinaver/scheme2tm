#include <stack>
#include <iostream>

#include "lexer.h"
#include "parser.h"

void pushStack(Token t, std::stack<Token> *s) {
    /*
     * Tokens are pushed onto the stack via shallow copy
     * In order to simulate stack,
     * it's easier to put things at the back of the array.
     */
    // TODO deal with stack being too small
    s->push(t);
}

Token topOfStack(std::stack<Token> *s) {
    /*
     * Tokens are pushed onto the stack via shallow copy
     * In order to simulate stack,
     * it's easier to put things at the back of the array.
     */
    // TODO deal with stack being too small
    return s->top();
}


Token popStack(std::stack<Token> *s) {
    /*
     * Tokens are popped off the stack via shallow copy
     */
    // TODO check if stack is empty
    Token t = s->top();
    s->pop();
    return t;
}

int printGotTokenExpectedTypeError(token_t inType, token_t stackType){
    std::cerr << "Invalid Syntax: got " << tokenToString(inType) << ", expected " << tokenToString(stackType) << std::endl;
    return 1;
}

int runParser(InputBuffer *ib) {
    int i;
    std::stack<Token> st;


    // Starting symbol expanded
    pushStack(Token(DOLLAR, ""), &st);
    pushStack(Token(RSTMT, ""), &st);
    pushStack(Token(STMT, ""), &st);

    // Read through all symbols in input buffer and parse
    for (i = 0; i < ib->buffer.size(); i++) {

        const Token stackTop = topOfStack(&st);

        switch (ib->buffer[i].type) {
            case IDENT:
                if (stackTop.type == IDENT)
                    popStack(&st);
                else
                    return printGotTokenExpectedTypeError(IDENT,stackTop.type);
                break;
            case STRING:
                switch (stackTop.type) {
                    case STRING:
                        popStack(&st);
                        break;
                    case ARGS:
                        popStack(&st);
                        pushStack(Token(ARGS, ""), &st);
                        pushStack(Token(STRING, ""), &st);
                        i--;
                        break;
                    default:
                        return printGotTokenExpectedTypeError(STRING,IDENT);
                }
                break;
            case NUMBER:
                switch (stackTop.type) {
                    case NUMBER:
                        popStack(&st);
                        break;
                    case ARGS:
                        popStack(&st);
                        pushStack(Token(ARGS, ""), &st);
                        pushStack(Token(NUMBER, ""), &st);
                        i--;
                        break;
                    default:
                        return printGotTokenExpectedTypeError(STRING,IDENT);
                }
                break;
            case LEFTPAREN:
                switch (stackTop.type) {
                    case LEFTPAREN:
                        popStack(&st);
                        break;
                    case ARGS:
                        popStack(&st);
                        pushStack(Token(ARGS, ""), &st);
                        pushStack(Token(STMT, ""), &st);
                        i--;
                        break;
                    case RSTMT:
                        popStack(&st);
                        pushStack(Token(RSTMT, ""), &st);
                        pushStack(Token(STMT, ""), &st);
                        i--;
                        break;
                    case STMT:
                        popStack(&st);
                        pushStack(Token(RIGHTPAREN, ""), &st);
                        pushStack(Token(ARGS, ""), &st);
                        pushStack(Token(IDENT, ""), &st);
                        pushStack(Token(LEFTPAREN, ""), &st);
                        i--;
                        break;
                    default:
                        return printGotTokenExpectedTypeError(LEFTPAREN,stackTop.type);
                        break;
                }
                break;
            case RIGHTPAREN:
                switch (stackTop.type) {
                    case RIGHTPAREN:
                        popStack(&st);
                        break;
                    case ARGS:
                        popStack(&st); // pop args off stack
                        i--; // so we can check again for more args
                        break;
                    case LEFTPAREN:
                    case IDENT:
                        return printGotTokenExpectedTypeError(RIGHTPAREN, stackTop.type);
                    default:
                        printf("\n\nTHIS HAPPENED?!\n\n");
                }
                break;
            default:
                printf("Invalid Syntax: unknown error...\n");
                return 1;
        }
    }

    // when RSTMT is the empty string
    if (topOfStack(&st).type == RSTMT)
        popStack(&st);

    // checks to see if we got to the dollar sign at the end of the input
    if (topOfStack(&st).type == DOLLAR) {
        printf("Successful Parse!\n");
        return 0;
    }

    printf("Invalid Syntax: unfinished statement \n");
    return 1;
}
