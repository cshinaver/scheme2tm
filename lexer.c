#include "lexer.h"

void appendTokenToBuffer(token_t t, InputBuffer *ib) {
    /*
     * TODO: needs to handle realloc'ing if buffer is not big enough
     */
    if (ib->bufcount == ib->bufsize) {
        //TODO implement resizing
    }
    ib->buffer[ib->bufcount] = t;
    ib->bufcount += 1;
}

int isWhitespace(char c) {
    if (c == ' ') {
        return 1;
    }
    return 0;
}

void runLexer(FILE *inputFile, InputBuffer *ib) {
    /*
     * Runs lexer
     * Assumes input file is already open
     */
    char c;
    while (fscanf(inputFile, "%c", &c) != EOF) {
        if (isWhitespace(c)) {
            appendTokenToBuffer(WS, ib);
        }
    }
}
