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
    int status = 0;
    const char *inputFilename = argv[1];
    FILE *inputFile = fopen(inputFilename, "r");

    // Lexing
    InputBuffer ib;
    int initial_size = 10000; // TODO Fix appendTokenToBuffer to resize
    runLexer(inputFile, &ib);

    // Parser
    status = runParser(&ib);

    for (i = 0; i < ib.buffer.size(); i++ ) {
        printf("type: %s; content: %s\n", tokenToString(ib.buffer[i].type).c_str(), ib.buffer[i].content.c_str());
    }
    printf("\n");

    fclose(inputFile);
    return status;
}
