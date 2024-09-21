#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"



/* What is a lexer and how does it work? 
- A lexer is a lexical analyzer 
- Breaks down raw source code into tokens
- It reads input char by char 
- Checks each char to determine if it's a keyword, identifier, #, operator or punctuation
- Creates token array and stores char if it matches one of the categories
- Dismisses other non-relevant chars and whitespace
*/

// Dynamically allocated token array to handle larger programs
Token *tokens = NULL;
int token_count = 0;
int token_capacity = 10;

// Python-like language keywords
const char* keywords[] = {
    "int", "char", "string", "float", "double", 
    "if", "else", "for", "while", "return", "void", 
    "switch", "case", "break", "continue"
};

// Function to check if a token is a keyword
int is_keyword(const char *str) {
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);
    for(int i = 0; i < num_keywords; i++){
        if(strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to dynamically add a token to the token array
void add_token(const char* type, const char* value) {
    // If the token_count is bigger then the capacity of array, we resize the array
    if(token_count >= token_capacity){
        token_capacity *= 2; // Double array capacity
        tokens = realloc(tokens, token_capacity * sizeof(Token));
        if(!tokens){
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }

    strcpy(tokens[token_count].type, type);
    strcpy(tokens[token_count].value, value);
    token_count++;
}

// Function to tokenize the source input 
void lexer(const char *input) {
    int i = 0;
    char token[100];

    while(input[i] != '\0'){
        // Skip whitespace
        if(isspace(input[i])){
            i++;
            continue;
        }
        // Identify keywords and identifiers
        if(isalpha(input[i])){
        int start = 0;
            while (isalnum(input[i])){
                token[start++] = input[i++];

            }
            token[start] = '\0';

            if(is_keyword(token)){
                add_token("KEYWORD", token);
            }
            else {
                add_token("IDENTIFIER", token);
            }
            continue;
        }
        // Identify numbers (including floats)
        if(isdigit(input[i])){
            int start = 0;
            int has_dot = 0;
            while(isdigit(input[i]) || (!has_dot && input[i] == '.')) {
                if(input[i] == '.') {
                    has_dot = 1;
                }
                token[start++] = input[i++];
            }
            token[start] = '\0';
            add_token("NUMBER", token);
            continue;
        }
        // Identify operators
        if(input[i] == '=' || input[i] == '<' || input[i] == '>' || input[i] == '+' || input[i] == '-') {
            token[0] = input[i];
            token[1] = '\0';
            add_token("OPERATOR", token);
            i++;
            continue;
        }
        // Identify punctuation 
        if(input[i] == ';' || input[i] == '(' || input[i] == ')' || 
        input[i] == '[' || input[i] == ']' || input[i] == ':' || 
        input[i] == '{' || input[i] == '}' || input[i] == ','){
            token[0] = input[i];
            token[1] = '\0';
            add_token("PUNCTUATION", token);
            i++;
            continue;
        }
        printf("Unknown character: %c\n", input[i]);
        i++;
    }
}

void print_tokens() {
    for(int i = 0; i < token_count; i++) {
        printf("Token Type: %s, Token Value: %s\n", tokens[i].type, tokens[i].value);
    }
}

    // Free the allocated token array
void free_tokens() {
    free(tokens);
}
