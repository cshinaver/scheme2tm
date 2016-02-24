#include "lexer.h"

int isWhitespace(char c) {
    if (c == ' ') {
        return 1;
    }
}

void runLexer(FILE *inputFile) {
    /*
     * Runs lexer
     * Assumes input file is already open
     */
    char c;
    while (fscanf(inputFile, "%c", &c) != EOF) {
        printf("%c\n", c);
    }
}
