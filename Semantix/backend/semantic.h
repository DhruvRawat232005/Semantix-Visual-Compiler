#ifndef SEMANTIC_H
#define SEMANTIC_H
#include<stdio.h>
typedef struct ASTNode
{
    char type[20];
    char value[50];
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;
void processStatement(ASTNode* node);
void printSymbolTable();
#endif