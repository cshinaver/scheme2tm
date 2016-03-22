#include <stack>
#include <iostream>
#include <sstream>
#include <deque>

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

void shittyErrorFunction() {
    std::cerr << "awwwwwwww man das bad" << std::endl;
    exit(1);
}

args *parseArgs(std::deque<Token> &inputDeque, std::stack<Token> &st) {
    args *newArgs = new args;
    long double *val;
    const Token stackTop = st.top();
    if (stackTop.type == ARGS) {
        if (inputDeque.empty()) {
            st.pop();
            return newArgs;
        }
        const Token inputTop = inputDeque.front();
        std::string *s;
        switch (inputTop.type) {
            case LEFTPAREN:
                st.pop();
                st.push(Token(ARGS, ""));
                st.push(Token(STMT, ""));
                newArgs->argStmt = parseStmt(inputDeque, st);
                newArgs->nextArg = parseArgs(inputDeque, st);
                break;
            case STRING:
                s = new std::string;
                *s = inputTop.content;
                newArgs->argString = s;
                inputDeque.pop_front();
                newArgs->nextArg = parseArgs(inputDeque, st);
                break;
            case NUMBER:
                val = new long double;
                *val = stold(inputTop.content);
                newArgs->argNum = val;
                inputDeque.pop_front();
                newArgs->nextArg = parseArgs(inputDeque, st);
                break;
            case RIGHTPAREN:
                st.pop();
                return newArgs;
        default:
            shittyErrorFunction();
        }
    }
    return newArgs;
}


stmt *parseStmt(std::deque<Token> &inputDeque, std::stack<Token> &st) {
    stmt *newStmt = new stmt;

    if (st.top().type == STMT) {
        // Pop left paren
        if (inputDeque.front().type == LEFTPAREN) {
            inputDeque.pop_front();
        }
        else {
            shittyErrorFunction();
        }

        // Pop ident
        if (inputDeque.front().type == IDENT) {
            if (inputDeque.front().content == "println") {
                newStmt->ident = inputDeque.front().content;
                inputDeque.pop_front();
            }
            else if (inputDeque.front().content == "add") {
                newStmt->ident = inputDeque.front().content;
                inputDeque.pop_front();
            }
            else {
                shittyErrorFunction();
            }
        }
        else {
            shittyErrorFunction();
        }

        // Pop args
        st.push(Token(ARGS, ""));
        newStmt->stmtArgs = parseArgs(inputDeque, st);

        // Pop right paren
        if (inputDeque.front().type == RIGHTPAREN) {
            inputDeque.pop_front();
        }
        else {
            shittyErrorFunction();
        }

        // Pop stmt
        st.pop();
    }

    return newStmt;

}

int runParser(InputBuffer &ib, std::vector<stmt *> &stmts) {
    int i;
    std::stack<Token> st;
    stmt *stmt_head;


    // Starting symbol expanded

    // Read through all symbols in input buffer and parse
    for (auto inputStmt : ib.buffer) {
        pushStack(Token(DOLLAR, ""), &st);
        pushStack(Token(STMT, ""), &st);
        stmt_head = parseStmt(inputStmt, st);
        stmts.push_back(stmt_head);
        if (inputStmt.empty() && st.top().type == DOLLAR) {
            continue;
        }
        else {
            std::cerr << "Invalid Syntax: unfinished statement" << std::endl;
            return 1;
        }
    }
    return 0;
}
