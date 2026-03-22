%{
#include<stdio.h>
#include "tokens.h"
FILE *out;
%}

DIGIT      [0-9]
LETTER     [a-zA-Z]
ID         {LETTER}({LETTER}|{DIGIT})*

%%
"DECLARE"  { fprintf(out, "DECLARE\n"); return DECLARE; }
"SET"      { fprintf(out, "SET\n"); return SET; }
"AS"       { fprintf(out, "AS\n"); return AS; }
"TO"       { fprintf(out, "TO\n"); return TO; }
"PRINT"    { fprintf(out, "PRINT\n"); return PRINT; }
{ID}       { fprintf(out, "IDENTIFIER(%s)\n", yytext); return IDENTIFIER; }
{DIGIT}+   { fprintf(out, "NUMBER(%s)\n", yytext); return NUMBER; }
"+"        { fprintf(out, "PLUS\n"); return PLUS; }
"-"        { fprintf(out, "MINUS\n"); return MINUS; }
"*"        { fprintf(out, "MULTIPLY\n"); return MULTIPLY; }
"/"        { fprintf(out, "DIVIDE\n"); return DIVIDE; }
"("        { fprintf(out, "LPAREN\n"); return LPAREN; }
")"        { fprintf(out, "RPAREN\n"); return RPAREN; }
[ \t\n]+       {}
.              { fprintf(out, "UNKNOWN(%s)\n", yytext); }
%%

int yywrap(){
    return 1;
}
