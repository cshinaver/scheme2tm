#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "parser.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: schemeinterpreter test.scm\n");
        exit(1);
    }
    int i;
    const char *inputFilename = argv[1];
    FILE *inputFile = fopen(inputFilename, "r");

    // Lexing
    InputBuffer ib;
    int initial_size = 10000; // TODO Fix appendTokenToBuffer to resize
    ib.buffer = malloc(initial_size);
    ib.bufsize = initial_size;
    ib.bufcount = 0;
    runLexer(inputFile, &ib);

    // Parser
    runParser(&ib);

    for (i = 0; i < ib.bufcount; i++ ) {
        printf("type: %s; content: %s\n", tokenToString(ib.buffer[i].type), ib.buffer[i].content);
        free(ib.buffer[i].content);
    }

    fclose(inputFile);
    free(ib.buffer);
    return 0;
}
