#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

extern int yylex();
extern FILE *yyin;
extern char *yytext;
extern FILE *out;

int currToken;

typedef struct ASTNode {
    char type[20];
    char value[50];
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

ASTNode* createNode(char* type, char* value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    strcpy(node->type, type);
    strcpy(node->value, value);
    node->left = NULL;
    node->right = NULL;
    return node;
}

void advance() {
    currToken = yylex();
}
void match(int expected) {
    if (currToken == expected) {
        advance();
    } else {
        printf("Error: expected %d but got %d\n", expected, currToken);
        exit(1);
    }
}

ASTNode* parseStatement();
ASTNode* parseExpression();
ASTNode* parseTerm();
ASTNode* parseFactor();

ASTNode* parseStatement() {
    ASTNode* node;
    if (currToken == DECLARE) {
        match(DECLARE);
        char var[50];
        if (currToken == IDENTIFIER) {
            strcpy(var, yytext);  
        }
        match(IDENTIFIER);
        match(AS);
        node = createNode("DECLARE", var);
        node->left = parseExpression();
    }
    else if (currToken == SET) {
        match(SET);
        char var[50];
        if (currToken == IDENTIFIER) {
            strcpy(var, yytext);   
        }
        match(IDENTIFIER);
        match(TO);
        node = createNode("SET", var);
        node->left = parseExpression();
    }
    else if (currToken == PRINT) {
        match(PRINT);

        node = createNode("PRINT", "");
        node->left = parseExpression();
    }
    else {
        printf("Syntax Error in Statement\n");
        exit(1);
    }
    return node;
}

ASTNode* parseExpression() {
    ASTNode* left = parseTerm();
    while (currToken == PLUS || currToken == MINUS) {
        char op[2];
        strcpy(op, (currToken == PLUS) ? "+" : "-");
        ASTNode* node = createNode("OP", op);
        advance();
        node->left = left;
        node->right = parseTerm();
        left = node;
    }
    return left;
}

ASTNode* parseTerm() {
    ASTNode* left = parseFactor();
    while (currToken == MULTIPLY || currToken == DIVIDE) {
        char op[2];
        strcpy(op, (currToken == MULTIPLY) ? "*" : "/");
        ASTNode* node = createNode("OP", op);
        advance();
        node->left = left;
        node->right = parseFactor();
        left = node;
    }
    return left;
}

ASTNode* parseFactor() {
    ASTNode* node;
    if (currToken == NUMBER) {
        char temp[50];
        strcpy(temp, yytext);   

        node = createNode("NUMBER", temp);
        advance();
    }
    else if (currToken == IDENTIFIER) {
        char temp[50];
        strcpy(temp, yytext);  
        node = createNode("IDENTIFIER", temp);
        advance();
    }
    else if (currToken == LPAREN) {
        match(LPAREN);
        node = parseExpression();
        match(RPAREN);
    }
    else {
        printf("Syntax Error in Factor\n");
        exit(1);
    }
    return node;
}

void printAST(ASTNode* root, int level, FILE* file) {
    if (root == NULL) return;
    for (int i = 0; i < level; i++)
        fprintf(file, "  ");
    fprintf(file, "%s(%s)\n", root->type, root->value);
    printAST(root->left, level + 1, file);
    printAST(root->right, level + 1, file);
}

int main() {
    yyin = fopen("input/input.txt", "r");
    if (!yyin) {
        printf("Error opening input file\n");
        return 1;
    }
    FILE *astFile = fopen("output/ast.txt", "w");
    if (!astFile) {
        printf("Error opening AST file\n");
        return 1;
    }
    out = fopen("output/tokens.txt", "w");
    if (!out) {
        printf("Error opening tokens file\n");
        return 1;
    }
    advance();
    while (currToken != 0) {
        ASTNode* root = parseStatement();
        printAST(root, 0, astFile);
    }
    printf("AST Generation Successful!\n");
    fclose(astFile);
    fclose(out);
    fclose(yyin);
    return 0;
}
