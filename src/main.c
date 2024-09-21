#include <stdio.h>
#include "lexer.h"


int main() {
    const char *source_code = "int myVar = 42; float y = 3.14; if (x < y) return 0;";
    printf("Source code: %s\n", source_code);


    // Dynamically allocated memory for the tokens array
    tokens = malloc(token_capacity * sizeof(Token));
    if(!tokens){
        printf("Memory allocation failed\n");
        return 1;
    }
    lexer(source_code);

    print_tokens();

    free_tokens();

   // parse();

    return 0;
}