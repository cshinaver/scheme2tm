#include <stdio.h>

typedef struct InputBuffers {
    token_t *buffer;
    int bufsize;
    int bufcount;
} InputBuffer;

void runLexer(FILE *inputFile, InputBuffer *ib);
