#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 200

char tac[MAX_LINES][100];
int tac_cnt=0;

typedef struct{
    char name[20];
    int value;
    int isConst;
} ConstEntry;

ConstEntry table[100];
int table_cnt=0;

int isNumber(char *str){
    for(int i=0;str[i];i++){
        if(!isdigit(str[i])) 
            return 0;
    }
    return 1;
}

int findConst(char *name){
    for (int i=0;i<table_cnt;i++){
        if(strcmp(table[i].name,name)==0 && table[i].isConst)
            return table[i].value;
    }
    return -99999; 
}

void setConst(char *name, int value){
    for (int i=0; i<table_cnt;i++){
        if(strcmp(table[i].name, name)==0){
            table[i].value=value;
            table[i].isConst=1;
            return;
        }
    }
    strcpy(table[table_cnt].name, name);
    table[table_cnt].value=value;
    table[table_cnt].isConst=1;
    table_cnt++;
}

void optimize(){
    FILE *in=fopen("output/ir.txt", "r");
    FILE *out=fopen("output/optimized.txt", "w");
    if(!in || !out){
        printf("Error opening files\n");
        return;
    }
    while(fgets(tac[tac_cnt],sizeof(tac[tac_cnt]),in)){
        tac_cnt++;
    }
    for(int i=0;i<tac_cnt;i++){
        char lhs[20],op1[20],op2[20],op[5];
        if (strncmp(tac[i],"PRINT",5)==0){
            sscanf(tac[i],"PRINT %s",op1);
            int val=findConst(op1);
            if (val!=-99999){
                fprintf(out,"PRINT %d\n",val);
            } 
            else{
                fprintf(out,"%s",tac[i]);
            }
            continue;
        }
        if (sscanf(tac[i],"%s = %s",lhs,op1)==2 &&
            strchr(tac[i],'+')==NULL &&
            strchr(tac[i],'*')==NULL &&
            strchr(tac[i],'-')==NULL &&
            strchr(tac[i],'/')==NULL) {
            if(isNumber(op1)){
                setConst(lhs, atoi(op1));
                fprintf(out, "%s = %s\n", lhs, op1);
            } 
            else{
                int val = findConst(op1);
                if (val != -99999) {
                    setConst(lhs, val);
                    fprintf(out, "%s = %d\n", lhs, val);
                } else {
                    fprintf(out, "%s", tac[i]);
                }
            }
            continue;
        }
        if (sscanf(tac[i],"%s = %s %s %s",lhs,op1,op,op2)==4){
            int val1=isNumber(op1) ? atoi(op1) : findConst(op1);
            int val2=isNumber(op2) ? atoi(op2) : findConst(op2);
            if(val1!=-99999 && val2!=-99999){
                int result = 0;
                if(strcmp(op,"+")==0) 
                    result=val1+val2;
                else if(strcmp(op,"-")==0) 
                    result=val1-val2;
                else if(strcmp(op,"*")==0) 
                    result=val1*val2;
                else if(strcmp(op,"/")==0) 
                    result=val1/val2;
                setConst(lhs, result);
                fprintf(out, "%s = %d\n", lhs, result);
            }
            else {
                if (val1!=-99999)
                    sprintf(op1, "%d", val1);
                if (val2!=-99999)
                    sprintf(op2, "%d", val2);
                fprintf(out, "%s = %s %s %s\n", lhs, op1, op, op2);
            }
        }
    }
    fclose(in);
    fclose(out);
    printf("Optimization Complete!\n");
}
