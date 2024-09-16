#include <stdio.h>

void lexer(const char *input);

int main() {
    const char *source_code = "int myVar = 42; float y = 3.14; if (x < y) return 0;";
    printf("Source code: %s\n", source_code);
    lexer(source_code);
    return 0;
}