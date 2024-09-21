#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode* create_node(NodeType type, const char *value){
    ASTNode* node = (ASTNode*) malloc(sizeof(ASTNode));
    node->type = type;
    strcpy(node->value, value);
    node->left = NULL;
    node->right = NULL;
    return node;
}


ASTNode* create_binary_op(NodeType type, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*) malloc(sizeof(ASTNode));
    node->type = type;
    node->left = left;
    node->right = right;
    return node;
}

void print_ast(ASTNode* node) {
    if(node == NULL) return;

    if(node->type == NODE_VAR_DECL || node->type == NODE_IDENTIFIER || node->type == NODE_NUMBER){
        printf("Node Type: %d, Value: %s\n", node->type, node->value);
    }

    if(node->type == NODE_BINARY_OP) {
        printf("Binary Operation: \n");
        print_ast(node->left);
        print_ast(node->right);
    }
}

