#include <ctype.h>

#include "lexer.h"

std::string tokenToString(token_t t) {
    switch (t) {
        case WS:
            return "WS";
            break;
        case IDENT:
            return "IDENT";
            break;
        case STRING:
            return "STRING";
            break;
        case LEFTPAREN:
            return "LEFTPAREN";
            break;
        case RIGHTPAREN:
            return "RIGHTPAREN";
            break;
        case NUMBER:
            return "NUMBER";
            break;
    }
    return NULL;
}

void appendTokenToBuffer(Token t, InputBuffer *ib) {
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

char readCharacter(FILE *inputFile) {
    char c;
    int status = fscanf(inputFile, "%c", &c);
    if (status == EOF) {
        return 0;
    } else {
        return c;
    }
}

char scanIdentifier(char firstCharacter, FILE *inputFile, Token *t) {
    /*
     * Scans to the end of an identifier
     * Returns last character found (as it's not in the identifer)
     * Mallocs buffer space for token
     */
    char currentCharacter;
    t->type = IDENT;
    t->content = new char [MAX_IDENT_SIZE + 1]; // +1 for null terminator
    t->content[0] = firstCharacter;
    int index = 1;
    while (1) {
        currentCharacter = readCharacter(inputFile);
        if (isalpha(currentCharacter)) {
            t->content[index] = currentCharacter;
            index++;
        } else {
            // TODO deal if EOF met
            t->content[index] = 0; // null terminator
            return currentCharacter;
        }
    }
}

char scanString(FILE *inputFile, Token *t) {
    /*
     * Scans to the end of a string
     * Returns last character found (as it's not in the string)
     * Mallocs buffer space for token
     */
    char currentCharacter;
    t->type = STRING;
    t->content = new char [MAX_IDENT_SIZE + 1]; // +1 for null terminator
    int index = 0;
    while (1) {
        currentCharacter = readCharacter(inputFile);
        if (currentCharacter == '"'){
            t->content[index] = 0; // null terminator
            return 0;
        }
        else if (currentCharacter == 0){
            // TODO deal if EOF met
            t->content[index] = 0; // null terminator
            return currentCharacter;
        }
        else {
            t->content[index] = currentCharacter;
            index++;
        }
    }
}

char scanNumber(char firstCharacter, FILE *inputFile, Token *t) {
    /*
     * Scans to the end of a number
     * Returns last number found (as it's not in the string)
     * Mallocs buffer space for token
     */
    char currentCharacter;
    t->type = NUMBER;
    t->content = new char [MAX_IDENT_SIZE + 1]; // +1 for null terminator
    t->content[0] = firstCharacter;
    int index = 1;
    while (1) {
        currentCharacter = readCharacter(inputFile);
        if (isdigit(currentCharacter)){
            t->content[index] = currentCharacter;
            index++;
        } else {
            t->content[index] = 0; // null terminator
            return currentCharacter;
        }
    }
}

void runLexer(FILE *inputFile, InputBuffer *ib) {
    /*
     * Runs lexer
     * Assumes input file is already open
     */
    char currentCharacter;
    char lastReadCharacter = 0;
    int isFinished = 0;
    while (!isFinished) {
        // Some functions go one character too far
        // If there is a last read character, use it instead of reading
        if (lastReadCharacter) {
            currentCharacter = lastReadCharacter;
            lastReadCharacter = 0;
        } else {
            currentCharacter = readCharacter(inputFile);
        }

        // Check if input left
        if (!currentCharacter) {
            isFinished = 1;
            continue;
        }

        if (isspace(currentCharacter)) {
            // Ignore whitespace
            continue;
        }
        else if (isalpha(currentCharacter)) {
            // Identifier
            Token t;
            lastReadCharacter = scanIdentifier(currentCharacter, inputFile, &t);
            appendTokenToBuffer(t, ib);

        }
        else if (isdigit(currentCharacter)) {
            // Number
            Token t;
            lastReadCharacter = scanNumber(currentCharacter, inputFile, &t);
            appendTokenToBuffer(t, ib);

        }
        else if (currentCharacter == '"') {
            // String
            Token t;
            lastReadCharacter = scanString(inputFile, &t);
            appendTokenToBuffer(t, ib);
        }
        else if (currentCharacter == '(') {
            // Leftparen
            Token t;
            t.type = LEFTPAREN;
            t.content = new char [2];
            t.content[0] = '(';
            t.content[1] = 0;
            appendTokenToBuffer(t, ib);
        }
        else if (currentCharacter == ')') {
            // Rightparen
            Token t;
            t.type = RIGHTPAREN;
            t.content = new char [2];
            t.content[0] = ')';
            t.content[1] = 0;
            appendTokenToBuffer(t, ib);
        }
        else if (EOF) {
            // Done
        }
        else {
            printf("You done fucked up yo syntax fool. Failed at char: %c\n",currentCharacter);
            exit(1);
        }
    }
}