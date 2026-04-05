#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"

#define MAX_SYMBOLS 100

typedef struct{
    char name[50];
    int value;
    int initialized;
} Symbol;

Symbol table[MAX_SYMBOLS];
int symbolCount = 0;

int findSymbol(char* name) {
    for (int i=0;i<symbolCount;i++){
        if (strcmp(table[i].name,name)==0)
            return i;
    }
    return -1;
}

void addSymbol(char* name){
    if (findSymbol(name)!=-1){
        printf("Semantic Error: Duplicate variable %s\n", name);
        return;
    }
    strcpy(table[symbolCount].name, name);
    table[symbolCount].value=0;
    table[symbolCount].initialized=0;
    symbolCount++;
}

void setSymbolValue(char* name,int value){
    int idx=findSymbol(name);
    if (idx==-1){
        printf("Semantic Error: Undeclared variable %s\n", name);
        return;
    }
    table[idx].value = value;
    table[idx].initialized = 1;
}

int getSymbolValue(char* name){
    int idx=findSymbol(name);
    if (idx==-1) {
        printf("Semantic Error: Undeclared variable %s\n", name);
        return 0;
    }
    return table[idx].value;
}

int evaluate(ASTNode* node){
    if (!node) return 0;
    if (strcmp(node->type,"NUMBER")==0)
        return atoi(node->value);
    if (strcmp(node->type,"IDENTIFIER")==0)
        return getSymbolValue(node->value);
    if (strcmp(node->type,"OP")==0){
        int left = evaluate(node->left);
        int right = evaluate(node->right);
        if (strcmp(node->value, "+")==0) return left+right;
        if (strcmp(node->value, "-")==0) return left-right;
        if (strcmp(node->value, "*")==0) return left*right;
        if (strcmp(node->value, "/")==0) return left/right;
    }
    return 0;
}

void processStatement(ASTNode* node){
    if(strcmp(node->type,"DECLARE")==0) {
        addSymbol(node->value);
        int val=evaluate(node->left);
        setSymbolValue(node->value,val);
    }
    else if(strcmp(node->type,"SET")==0) {
        if(findSymbol(node->value)==-1) {
            addSymbol(node->value);
        }
        int val = evaluate(node->left);
        setSymbolValue(node->value, val);
    }
    else if(strcmp(node->type,"PRINT")==0) {
        int val = evaluate(node->left);
        printf("Output: %d\n", val);
    }
}

void printSymbolTable() {
    FILE *file = fopen("output/symbol_table.txt", "w");
    fprintf(file, "Name\tValue\n");
    for (int i = 0; i < symbolCount; i++) {
        fprintf(file, "%s\t%d\n", table[i].name, table[i].value);
    }
    fclose(file);
}