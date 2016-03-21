#include <stack>

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

int printErr(token_t inType, token_t stackType){
    printf("Invalid Syntax: got %s expected %s\n",tokenToString(inType).c_str(),tokenToString(stackType).c_str());
    return 1;
}

int runParser(InputBuffer *ib) {
    int i;
    std::stack<Token> st;
    int max_stack_count = 500;


    // Starting symbol expanded
    pushStack(Token(DOLLAR, ""), &st);
    pushStack(Token(RSTMT, ""), &st);
    pushStack(Token(STMT, ""), &st);

    // Read through all symbols in input buffer and parse
    for (i = 0; i < ib->buffer.size(); i++) {
        //printf("%i\n", ib->buffer[i].type);

        const Token stackTop = topOfStack(&st);

        switch (stackTop.type) {
            case STMT:
                popStack(&st);
            case RSTMT:
                pushStack(Token(RIGHTPAREN, ""), &st);
                pushStack(Token(ARGS, ""), &st);
                pushStack(Token(IDENT, ""), &st);
                pushStack(Token(LEFTPAREN, ""), &st);
                break;
            default:
                break;
        }

        switch (ib->buffer[i].type) {
            case IDENT:
                if (stackTop.type == IDENT)
                    popStack(&st);
                else
                    return printErr(IDENT,stackTop.type);
                break;
            case STRING:
                if (stackTop.type == IDENT)
                    return printErr(STRING,IDENT);
                break;
            case NUMBER:
                if (stackTop.type == IDENT)
                    return printErr(NUMBER,IDENT);
                break;
            case LEFTPAREN:
                switch (stackTop.type) {
                    case LEFTPAREN:
                        popStack(&st);
                        break;
                    case ARGS:
                        popStack(&st);
                        pushStack(Token(RIGHTPAREN, ""), &st);
                        pushStack(Token(ARGS, ""), &st);
                        pushStack(Token(IDENT, ""), &st);
                        break;
                    case RIGHTPAREN:
                    case IDENT:
                        return printErr(LEFTPAREN,stackTop.type);
                    default:
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
                        return printErr(RIGHTPAREN, stackTop.type);
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
