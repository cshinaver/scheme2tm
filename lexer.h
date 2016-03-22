#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <deque>

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
    Token() {};
    Token(token_t t, std::string content) : type(t), content(content) {};
    token_t type;
    std::string content;
};


struct InputBuffer {
    std::vector<std::deque<Token> > buffer;
};

void runLexer(std::ifstream &inputFile, InputBuffer &ib);
std::string tokenToString(token_t t);

#endif
