#include <stdio.h>
#include <string.h>
#include "lexer.c"

void parse() {
    int i = 0;
    while (i < token_count) {
        if(strcmp(tokens[i].type, "KEYWORD") == 0) {
            printf("Parsing declaration of type: %s\n", tokens[i].value);
            i++;

            if(strcmp(tokens[i].type, "IDENTIFIER") == 0) {
                printf("Variable declared: %s\n", tokens[i].value);
                i++;
                    
                if(strcmp(tokens[i].type, "OPERATOR") == 0 && strcmp(tokens[i].value, "=") == 0){
                    i++;

                    if(strcmp(tokens[i].type, "NUMBER") == 0){
                        printf("Assigned value: %s\n", tokens[i].value);
                        i++;
                    }
                }        
                if(strcmp(tokens[i].type, "PUNCTUATION") == 0 && strcmp(tokens[i].value, ";") == 0) {
                    printf("End of statement.\n");
                    i++;
                }
                else {
                    printf("Error: Expected semicolon.\n");
                    return;
                }
            }
            else {
                printf("Error: Expected variable name after type\n");
                return;
            }
        }
        else {
            printf("Error: Expected a type declaration.\n");
            return;
        }
    }
}