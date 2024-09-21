#ifndef AST_H
#define AST_H

typedef enum {
    NODE_VAR_DECL, // Variable declaration
    NODE_ASSIGN, // Assignment
    NODE_BINARY_OP, // Binary operation
    NODE_NUMBER, // Numbers
    NODE_IDENTIFIER // Identifiers
} NodeType;

typedef struct ASTNode {
    NodeType type;
    char value[100];
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

ASTNode* create_node(NodeType type, const char *value);
ASTNode* create_binary_op(NodeType type, ASTNode* left, ASTNode* right);

void print_ast(ASTNode* node);

#endif
