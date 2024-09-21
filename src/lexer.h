#ifndef LEXER_H
#define LEXER_H
#include <stdlib.h>

typedef struct {
    char type[20];
    char value[100];
} Token;

extern Token *tokens;  // Declare token array
extern int token_count;
extern int token_capacity; 

void lexer(const char *input);
void print_tokens();
void free_tokens();

#endif
