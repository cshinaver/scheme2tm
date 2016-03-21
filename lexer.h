#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#define MAX_IDENT_SIZE 100

enum token_t {
    ARGS,
    DOLLAR,
    IDENT,
    LEFTPAREN,
    NUMBER,
    RIGHTPAREN,
    START,
    STMT,
    STRING,
    WS,
};

struct Token {
    token_t type;
    std::string content;
};


struct InputBuffer {
    std::vector<Token> buffer;
};

void runLexer(FILE *inputFile, InputBuffer *ib);
std::string tokenToString(token_t t);

#endif
