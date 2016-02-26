#include "lexer.h"
#include "parser.h"

typedef struct Stacks {
    Token *buffer;
    int count;
    int max_count;
} Stack;

void pushStack(Token t, Stack *s) {
    /*
     * Tokens are pushed onto the stack via shallow copy
     * In order to simulate stack,
     * it's easier to put things at the back of the array.
     */
    // TODO deal with stack being too small
    s->buffer[s->count] = t;
    s->count++;
}

Token topOfStack(Stack *s) {
    /*
     * Tokens are pushed onto the stack via shallow copy
     * In order to simulate stack,
     * it's easier to put things at the back of the array.
     */
    // TODO deal with stack being too small
    return s->buffer[s->count - 1];
}


Token popStack(Stack *s) {
    /*
     * Tokens are popped off the stack via shallow copy
     */
    // TODO check if stack is empty
    Token t = s->buffer[s->count -1];
    s->count--;
    return t;
}
int runParser(InputBuffer *ib) {
    int i;
    Stack st;
    Token t;
    int max_stack_count = 500;
    st.buffer = malloc(max_stack_count);
    st.max_count = 500;
    st.count = 0;


    // Push dolla
    t.type = DOLLAR;
    t.content = NULL;
    pushStack(t, &st);
    // Push Start, pop start push stmt
    //    t.type = STMT;
    //    t.content = NULL;
    //    pushStack(t, &st);

    t.type = RIGHTPAREN;
    pushStack(t, &st);
    t.type = ARGS;
    pushStack(t, &st);
    t.type = IDENT;
    pushStack(t, &st);
    t.type = LEFTPAREN;
    pushStack(t, &st);

    // Read through all symbols in input buffer and parse
    for (i = 0; i < ib->bufcount; i++) {
        //printf("%i\n", ib->buffer[i].type);


        if (ib->buffer[i].type == IDENT) {
            if (topOfStack(&st).type == IDENT) {
                popStack(&st);
            }
            else {
                printf("Invalid Syntax: unexpected %s\n",tokenToString(IDENT));
                return 1;
            }
        }
        else if (ib->buffer[i].type == STRING) {
            if (topOfStack(&st).type == ARGS) {
                // do nothing
            }
            else if (topOfStack(&st).type == IDENT) {
                printf("Invalid Syntax: got %s expected %s\n",tokenToString(STRING),tokenToString(IDENT));
                return 1;

            }
        }
        else if (ib->buffer[i].type == NUMBER) {
            if (topOfStack(&st).type == ARGS) {
                // do nothing
            }
            else if (topOfStack(&st).type == IDENT) {
                printf("Invalid Syntax: got %s expected %s\n",tokenToString(NUMBER),tokenToString(IDENT));
                return 1;
            }
        }
        else if (ib->buffer[i].type == LEFTPAREN) {
            if (topOfStack(&st).type == LEFTPAREN) {
                popStack(&st);
            }
            else if (topOfStack(&st).type == ARGS) {
                popStack(&st);
                t.type = RIGHTPAREN;
                pushStack(t, &st);
                t.type = ARGS;
                pushStack(t, &st);
                t.type = IDENT;
                pushStack(t, &st);
            }
            else if (topOfStack(&st).type == RIGHTPAREN) {
                printf("Invalid Syntax: got %s expected %s\n",tokenToString(LEFTPAREN),tokenToString(RIGHTPAREN));
                return 1;
            }
            else if (topOfStack(&st).type == IDENT) {
                printf("Invalid Syntax: got %s expected %s\n",tokenToString(LEFTPAREN),tokenToString(IDENT));
                return 1;
            }
        }
        else if (ib->buffer[i].type == RIGHTPAREN) {
            if (topOfStack(&st).type == RIGHTPAREN) {
                popStack(&st);
            }
            else if (topOfStack(&st).type == ARGS) {
                popStack(&st); // pop args off stack
                i--; // so we can check again for more args
            }
            else if (topOfStack(&st).type == LEFTPAREN) {
                printf("Invalid Syntax: got %s expected %s\n",tokenToString(RIGHTPAREN),tokenToString(LEFTPAREN));
                return 1;
            }
            else if (topOfStack(&st).type == IDENT) {
                printf("Invalid Syntax: got %s expected %s\n",tokenToString(RIGHTPAREN),tokenToString(IDENT));
                return 1;
            }
            else {
                printf("\n\nTHIS HAPPENED?!\n\n");
            }
        }
        else {
            printf("Invalid Syntax: unknown error...\n");
            return 1;
        }

        // checks to see if we got to the dollar sign successfuly
        if (topOfStack(&st).type == DOLLAR) {
            printf("Successful Parse!\n");
            return 0;
        }
    }
    printf("Invalid Syntax: unfinished statement \n");
    return 1;
}