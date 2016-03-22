#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <stack>
#include <deque>

struct stmt;
struct args {
    std::string type;
    std::string content;
    args *nextArg = NULL;
    stmt *argStmt = NULL; 
    std::string *argString = NULL; 
    std::string *argNum = NULL; 
};

struct stmt {
    std::string ident;
    args *stmtArgs;
    std::string value;
};

int runParser(InputBuffer &ib, stmt *&stmt_head);
args *parseArgs(std::deque<Token> &inputDeque, std::stack<Token> &st);
stmt *parseStmt(std::deque<Token> &inputDeque, std::stack<Token> &st);

#endif
