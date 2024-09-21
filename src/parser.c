#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "ast.h"

ASTNode* parse_declaration(int* i);
ASTNode* parse_expression(int* i);
ASTNode* parse_assignment(int* i);


void parse() {
    int i = 0;
    ASTNode* root = NULL;

    while (i < token_count) {
        if (strcmp(tokens[i].type, "KEYWORD") == 0) {
            if (strcmp(tokens[i].value, "if") == 0) {
                // Handle if-statement
                printf("Parsing if-statement\n");
                i++;  // Skip the 'if' keyword

                // Expect '('
                if (strcmp(tokens[i].type, "PUNCTUATION") == 0 && strcmp(tokens[i].value, "(") == 0) {
                    i++;  // Skip '('
                    // Parse the condition (e.g., x < y)
                    ASTNode* condition = parse_expression(&i);

                    // Expect ')'
                    if (strcmp(tokens[i].type, "PUNCTUATION") == 0 && strcmp(tokens[i].value, ")") == 0) {
                        i++;  // Skip ')'
                        printf("Parsed condition in if-statement.\n");
                        print_ast(condition);  // For debugging, print the condition AST
                    } else {
                        printf("Error: Expected ')' after condition in if-statement.\n");
                        return;
                    }
                } else {
                    printf("Error: Expected '(' after 'if'.\n");
                    return;
                }
            } else {
                // Handle other keywords like variable declarations
                root = parse_declaration(&i);
            }
        } else {
            printf("Error: Unexpected token: %s\n", tokens[i].value);
            return;
        }
    }

    if (root != NULL) {
        print_ast(root);  // Print the AST for debugging
    }
}

ASTNode* parse_declaration(int* i) {
    printf("Parsing declaration of type: %s\n", tokens[*i].value);

    ASTNode* var_decl = create_node(NODE_VAR_DECL, tokens[*i].value);
    (*i)++;

    // Expect an identifier
    if(strcmp(tokens[*i].type, "IDENTIFIER") == 0) {
                ASTNode* identifier = create_node(NODE_IDENTIFIER, tokens[*i].value);
                (*i)++;

                // Expect an assignment operator (=)
                if(strcmp(tokens[*i].type, "OPERATOR") == 0 && strcmp(tokens[*i].value, "=") == 0){
                    (*i)++; 
                    ASTNode* expression = parse_expression(i);

                    ASTNode* assignment = create_binary_op(NODE_ASSIGN, identifier, expression);
                    (*i)++;

                    // Expect a semicolon
                    if(strcmp(tokens[*i].type, "PUNCTUATION") == 0 && strcmp(tokens[*i].value, ";") == 0) {
                        printf("End of statement.\n");
                        (*i)++;
                        return assignment;
                }   else {
                        printf("Error: Expected semicolon.\n");
                        return NULL;
                }
            }
        } 
        else {
            printf("Error: Expected variable name after type\n");
            return NULL;
        }
        return NULL;    
    }
     
ASTNode* parse_expression(int* i) {
    ASTNode* left = NULL;

    if (strcmp(tokens[*i].type, "NUMBER") == 0 || strcmp(tokens[*i].type, "IDENTIFIER") == 0) {
        left = create_node(strcmp(tokens[*i].type, "NUMBER") == 0 ? NODE_NUMBER : NODE_IDENTIFIER, tokens[*i].value);
        (*i)++;
    } else {
        printf("Error: Expected identifier or number in expression.\n");
        return NULL;
    }
    
    if (strcmp(tokens[*i].type, "OPERATOR") == 0) {
        const char* operator = tokens[*i].value;
        (*i)++;

        ASTNode* right = NULL;

        if(strcmp(tokens[*i].type, "NUMBER") == 0 || strcmp(tokens[*i].type, "IDENTIFIER") == 0) {
            right = create_node(strcmp(tokens[*i].type, "NUMBER") == 0 ? NODE_NUMBER : NODE_IDENTIFIER, tokens[*i].value);
            (*i)++;   
        }else {
            printf("Error: Expected identifier or number after operator.\n");
            return NULL;
        }
        return create_binary_op(NODE_BINARY_OP, left, right);
    }
    return left;
}
