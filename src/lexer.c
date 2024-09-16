#include <stdio.h>
#include <ctype.h>
#include <string.h>

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
                printf("Token: KEYWORD (%s)\n", token);
            }
            else {
                printf("token: IDENTIFIER (%s)\n", token);
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
            printf("Token: NUMBER (%s)\n", token);
            continue;
        }

        if(input[i] == '=' || input[i] == '<' || input[i] == '>' || input[i] == '+' || input[i] == '-') {
            printf("Token: OPERATOR (%c)\n", input[i]);
            i++;
            continue;
        }

        if(input[i] == ';' || input[i] == '(' || input[i] == ')'){
            printf("Token: PUNCTUATION %c\n", input[i]);
            i++;
            continue;
        }
        printf("Unknown character: %c\n", input[i]);
        i++;
    }
}