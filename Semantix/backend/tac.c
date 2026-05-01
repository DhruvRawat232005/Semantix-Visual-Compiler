#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tac.h"

#define MAX_TAC 200

char tac[MAX_TAC][100];
int tacIndex=0;
int tempCount=1;

char* newTemp(){
    static char temp[10];
    sprintf(temp,"t%d",tempCount++);
    return temp;
}

char* generateExpr(ASTNode* node){
    if(!node) return "";
    if(strcmp(node->type,"NUMBER")==0){
        return node->value;
    }
    if(strcmp(node->type,"IDENTIFIER")==0) {
        return node->value;
    }
    if(strcmp(node->type,"OP")==0){
        char* left=generateExpr(node->left);
        char* right=generateExpr(node->right);
        char* temp=newTemp();
        sprintf(tac[tacIndex++],"%s = %s %s %s",temp,left,node->value,right);
        return temp;
    }
    return "";
}

void generateTAC(ASTNode* root){
    if(strcmp(root->type,"DECLARE")==0){
        char* result=generateExpr(root->left);
        sprintf(tac[tacIndex++],"%s = %s",root->value,result);
    }
    else if(strcmp(root->type,"SET")==0){
        char* result=generateExpr(root->left);
        sprintf(tac[tacIndex++],"%s = %s",root->value,result);
    }
    else if(strcmp(root->type,"PRINT")==0){
        char* result = generateExpr(root->left);
        sprintf(tac[tacIndex++], "PRINT %s", result);
    }
}

void writeTACToFile(){
    FILE* file=fopen("output/ir.txt","w");
    for(int i=0;i<tacIndex;i++){
        fprintf(file,"%s\n",tac[i]);
    }
    fclose(file);
}