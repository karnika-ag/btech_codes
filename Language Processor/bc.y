%{
#include<stdio.h>
#include<stdlib.h>
#define YYSTYPE double
%}	

%token NUM

%%

pgm: expr  {printf("%f",$$);}
     ;

expr: expr '+' expr1  {$$=$1+$3;}
      |expr '-' expr1  {$$=$1-$3;}
      |expr1
      ;

expr1 : expr1 '*' expr2 {$$=$1*$3;}
        |expr1 '/' expr2 {$$=$1/$3;}
        |expr2
        ;

expr2 : '(' expr ')' {$$=$2;}
         |
         NUM  
         ;
      

%%
#include<ctype.h>
#include "lex.yy.c"
int main(int argc,char *argv[])
{
yyin=fopen(argv[1],"r");
if(!yyparse())
printf("parsing complete\n");
else
{
printf("parsing failed\n");
return 0;
}
fclose(yyin);
return 0;
}
