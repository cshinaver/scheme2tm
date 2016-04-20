#include <stdio.h>
#include <cstring>
#include <fstream>
#include <stdlib.h>

#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

enum COMMAND {
  LEX,
  PARSE,
  EVAL,
};

void usage() {
    printf("usage: scheme2tm test.scm\n");
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
        else if (strcmp(argv[1], "-eval") == 0) {
            progCommand = EVAL;
            inputFilename = argv[2];
        }
        else {
            usage();
        }
    }
    else if (argc == 2) {
        progCommand = EVAL;
        inputFilename = argv[1];
    }

    std::ifstream inputFile(inputFilename);

    InputBuffer ib;
    int status;
    std::vector<stmt *> stmts;
    switch (progCommand) {
        case LEX:
            // Lexing
            runLexer(inputFile, ib);
            for (auto i : ib.buffer) {
                for (auto j: i) {
                    printf(
                        "type: %s; content: %s\n",
                        tokenToString(j.type).c_str(),
                        j.content.c_str()
                    );
                }
            }
            break;
        case PARSE:
            // Lexing
            runLexer(inputFile, ib);
            // Parser
            status = runParser(ib, stmts);
            break;
        case EVAL:
            // Lexing
            runLexer(inputFile, ib);
            // Parser
            status = runParser(ib, stmts);
            // Evaluating
            runEvaluator(stmts);
    }


    return status;
}
