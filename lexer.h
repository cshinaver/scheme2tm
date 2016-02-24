#include <stdio.h>

typedef enum {
    WS,
} token_t;

typedef struct InputBuffers {
    token_t *buffer;
    int bufsize;
    int bufcount;
} InputBuffer;

void runLexer(FILE *inputFile, InputBuffer *ib);
