#include <stdio.h>
#include <ctype.h>
#include <string.h>


typedef struct {
    char type[20];
    char value[100];
} Token;

Token tokens[100];
int token_count = 0;


const char* keywords[] = {
    "int", "char", "string", "float", "double", 
    "if", "else", "for", "while", "return", "void", 
    "switch", "case", "break", "continue"
};

int is_keyword(const char *str) {
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

    for(int i = 0; i < num_keywords; i++){
        if(strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void add_token(const char* type, const char* value) {
    strcpy(tokens[token_count].type, type);
    strcpy(tokens[token_count].value, value);
    token_count++;
}

void lexer(const char *input) {
    int i = 0;
    char token[100];

    while(input[i] != '\0'){
        if(isspace(input[i])){
            i++;
            continue;
        }

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

        if(input[i] == '=' || input[i] == '<' || input[i] == '>' || input[i] == '+' || input[i] == '-') {
            token[0] = input[i];
            token[i] = '\0';
            add_token("OPERATOR", token);
            i++;
            continue;
        }

        if(input[i] == ';' || input[i] == '(' || input[i] == ')'){
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