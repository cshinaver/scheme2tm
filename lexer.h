#include <stdio.h>
#include <stdlib.h>

#define MAX_IDENT_SIZE 100

typedef enum {
    IDENT,
    STRING,
    LEFTPAREN,
    RIGHTPAREN,
    WS,
} token_t;

typedef struct Tokens {
    token_t type;
    char *content;
} Token;


typedef struct InputBuffers {
    Token *buffer;
    int bufsize;
    int bufcount;
} InputBuffer;

void runLexer(FILE *inputFile, InputBuffer *ib);
char *tokenToString(token_t t);
