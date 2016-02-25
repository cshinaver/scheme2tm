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

Token popStack(Stack *s) {
    /*
     * Tokens are popped off the stack via shallow copy
     */
    // TODO check if stack is empty 
    Token t = s->buffer[s->count -1];
    s->count--;
    return t;
}
void runParser(InputBuffer *ib) {
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
    t.type = STMT;
    t.content = NULL;
    pushStack(t, &st);

    // Read through all symbols in input buffer and parse
    for (i = 0; i < ib->bufcount; i++) {
        if (st.buffer[i].type == STMT) {
            popStack(&st);
            
            t.type = RIGHTPAREN;
            //t.content = ")";
            pushStack(t, &st);
            
            t.type = ARGS;
            //t.content = NULL;
            pushStack(t, &st);
            
            t.type = IDENT;
            //t.content = NULL;
            pushStack(t, &st);
            
            t.type = LEFTPAREN;
            //t.content = "(";
            pushStack(t, &st);
        }
        else if (st.buffer[i].type == IDENT) {
           popStack(&st);  
        }
        else if (st.buffer[i].type == STRING) {
           popStack(&st);  
        }
        else if (st.buffer[i].type == NUMBER) {
           popStack(&st);  
        }
        else if (st.buffer[i].type == ARGS) {
            popStack(&st);
            t.type = ARGS;
            pushStack(t, &st); 
            if (st.buffer[i+1].type == IDENT) {
                t.type = IDENT;
                pushStack(t, &st);
            } 
            else if (st.buffer[i+1].type == STRING) {
                t.type = STRING;
                pushStack(t, &st);
            }
            else if (st.buffer[i+1].type == NUMBER) {
                t.type = NUMBER;
                pushStack(t, &st);
            }
            else if (st.buffer[i+1].type == RIGHTPAREN) {
                t.type = RIGHTPAREN;
                pushStack(t, &st);
            }
            else if (st.buffer[i+1].type == LEFTPAREN) {
                t.type = LEFTPAREN;
                pushStack(t, &st);
            }
            else if (st.buffer[i+1].type == WS) {
                t.type = WS;
                pushStack(t, &st);
            }
            else {
                printf("Error. Invalid Syntax. \n");
                return;
            }
        }
        else if (st.buffer[i].type == DOLLAR) {
            
        }
        else if (st.buffer[i].type == LEFTPAREN) {
            popStack(&st);    
        }
        else if (st.buffer[i].type == RIGHTPAREN) {
            
        }
        else if (st.buffer[i].type == WS) {
            
        } 
    }
}
