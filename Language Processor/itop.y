%{
#include<stdio.h>
#include<stdlib.h>
%}
%token ID NUM
%left '+' '-' '*' '/'

%%
pgm : expr
      ;

expr : expr '+' {push();} expr1 {pop();}
       |expr '-' {push();} expr1 {pop();}
       |expr1
       ;

expr1 : expr1 '*' {push();} expr2 {pop();}
       |expr1 '/' {push();} expr2 {pop();}
       |expr2
       ;

expr2 : '(' expr {pop();} ')'
        |'-' {push();} expr2 {pop();}
        | ID {printval();}
        | NUM {printval();}
        ;


%%

#include<ctype.h>
#include "lex.yy.c"
char st[100];
int top=0;

int main(int argc, char *argv[])
{
yyin = fopen(argv[1], "r");
if(!yyparse())
printf("\nParsing complete\n");
else
{
printf("\nParsing failed\n");
exit(0);
}
fclose(yyin);
return 0;
}

push()
{
st[top++]=yytext[0];
}

pop()
{
printf("%c",st[top--]);
}
printval()
{
printf("%s",yytext);
}
