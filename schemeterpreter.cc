#include <stdio.h>
#include <cstring>
#include <stdlib.h>

#include "lexer.h"
#include "parser.h"

enum COMMAND {
  LEX,
  PARSE,
};

void usage() {
    printf("usage: schemeinterpreter test.scm\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    COMMAND progCommand = LEX;
    char *inputFilename;

    if (argc < 2 || argc > 3) {
        usage();
    }

    if (argc == 3) {
         if (strcmp(argv[1], "-lex") == 0) {
            progCommand = LEX;
            inputFilename = argv[2];
        }
        else if (strcmp(argv[1], "-parse") == 0) {
            progCommand = PARSE;
            inputFilename = argv[2];
        }
        else {
            usage();
        }
    }
    else if (argc == 2) {
        progCommand = LEX;
        inputFilename = argv[1];
    }

    FILE *inputFile = fopen(inputFilename, "r");



    InputBuffer ib;
    int status;
    switch (progCommand) {
        case LEX:
            // Lexing
            runLexer(inputFile, &ib);
            for (int i = 0; i < ib.buffer.size(); i++ ) {
                printf("type: %s; content: %s\n",
                    tokenToString(ib.buffer[i].type).c_str(),
                    ib.buffer[i].content.c_str()
                );
            }
            break;
        case PARSE:
            // Lexing
            runLexer(inputFile, &ib);
            // Parser
            status = runParser(&ib);
            break;
    }


    fclose(inputFile);
    return status;
}
