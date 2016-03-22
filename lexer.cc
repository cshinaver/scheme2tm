#include <ctype.h>
#include <sstream>
#include <fstream>

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
        case STMT:
            return "STMT";
            break;
        case ARGS:
            return "ARGS";
            break;
    }
    return "";
}

void appendTokenToBuffer(Token t, std::deque<Token> &tokens) {
    /*
     * TODO: needs to handle realloc'ing if buffer is not big enough
     */
    tokens.push_back(t);
}

int isWhitespace(char c) {
    if (c == ' ') {
        return 1;
    }
    return 0;
}

char readCharacter(std::istringstream &line) {
    char c;
    if (line.eof()) {
        return 0;
    } else {
        line.get(c);
        return c;
    }
}

char scanIdentifier(char firstCharacter, std::istringstream &inputFile, Token *t) {
    /*
     * Scans to the end of an identifier
     * Returns last character found (as it's not in the identifer)
     * Mallocs buffer space for token
     */
    char currentCharacter;
    t->type = IDENT;
    char *buffer = new char [MAX_IDENT_SIZE + 1]; // +1 for null terminator
    buffer[0] = firstCharacter;
    int index = 1;
    while (1) {
        currentCharacter = readCharacter(inputFile);
        if (isalpha(currentCharacter)) {
            buffer[index] = currentCharacter;
            index++;
        } else {
            // TODO deal if EOF met
            buffer[index] = 0; // null terminator
            t->content = buffer;
            delete buffer;
            return currentCharacter;
        }
    }
}

char scanString(std::istringstream &inputFile, Token *t) {
    /*
     * Scans to the end of a string
     * Returns last character found (as it's not in the string)
     * Mallocs buffer space for token
     */
    char currentCharacter;
    t->type = STRING;
    char *buffer = new char [MAX_IDENT_SIZE + 1]; // +1 for null terminator
    int index = 0;
    while (1) {
        currentCharacter = readCharacter(inputFile);
        if (currentCharacter == '"'){
            buffer[index] = 0; // null terminator
            t->content = buffer;
            return 0;
        }
        else if (currentCharacter == 0){
            // TODO deal if EOF met
            buffer[index] = 0; // null terminator
            t->content = buffer;
            return currentCharacter;
        }
        else {
            buffer[index] = currentCharacter;
            index++;
        }
    }
}

char scanNumber(char firstCharacter, std::istringstream &inputFile, Token *t) {
    /*
     * Scans to the end of a number
     * Returns last number found (as it's not in the string)
     * Mallocs buffer space for token
     */
    char currentCharacter;
    t->type = NUMBER;
    char *buffer = new char [MAX_IDENT_SIZE + 1]; // +1 for null terminator
    buffer[0] = firstCharacter;
    int index = 1;
    while (1) {
        currentCharacter = readCharacter(inputFile);
        if (isdigit(currentCharacter)){
            buffer[index] = currentCharacter;
            index++;
        } else {
            buffer[index] = 0; // null terminator
            t->content = buffer;
            return currentCharacter;
        }
    }
}

void lexLine(std::istringstream &line, std::deque<Token> &ib) {
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
            currentCharacter = readCharacter(line);
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
            lastReadCharacter = scanIdentifier(currentCharacter, line, &t);
            appendTokenToBuffer(t, ib);

        }
        else if (isdigit(currentCharacter)) {
            // Number
            Token t;
            lastReadCharacter = scanNumber(currentCharacter, line, &t);
            appendTokenToBuffer(t, ib);

        }
        else if (currentCharacter == '"') {
            // String
            Token t;
            lastReadCharacter = scanString(line, &t);
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

void runLexer(std::ifstream &inputFile, InputBuffer &ib) {
    /*
     * Runs lexer
     * Assumes input file is already open
     */
    std::string line;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        ib.buffer.push_back(std::deque<Token>());
        lexLine(iss, ib.buffer[ib.buffer.size() - 1]);  
    }
}
