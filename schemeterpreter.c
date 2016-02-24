#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

int main(int argc, char *argv[]) {
    int i;
    const char *inputFilename = argv[1];
    FILE *inputFile = fopen(inputFilename, "r");

    // Lexing
    InputBuffer ib;
    int initial_size = 100;
    ib.buffer = malloc(initial_size);
    ib.bufsize = initial_size;
    ib.bufcount = 0;
    runLexer(inputFile, &ib);


    fclose(inputFile);
    free(ib.buffer);
    return 0;
}
