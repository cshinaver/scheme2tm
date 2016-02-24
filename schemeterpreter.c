#include <stdio.h>

#include "lexer.h"

int main(int argc, char *argv[]) {
    const char *inputFilename = argv[1];
    FILE *inputFile = fopen(inputFilename, "r");
    runLexer(inputFile);
    fclose(inputFile);
    return 0;
}
