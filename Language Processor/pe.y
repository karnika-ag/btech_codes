%{
#include<stdio.h>
#include<stdlib.h>
#define YYSTYPE double
double st[100];
int top=0;

%}	

%token NUM

%%

pgm: expr  {printf("%f",st[--top]);}
     ;

expr: expr expr '+' {xpr_eval(0);}
      |expr expr '-' {xpr_eval(1);}
      |expr expr '*' {xpr_eval(2);}
      |expr expr '/' {xpr_eval(3);}
      | NUM {push();}
      ;
/*      |expr1
      ;

expr1 : expr1 expr2 '*' {eval('*');}
        |expr1 expr2 '/' {eval('/');}
        |expr2
        ;

expr2 :  NUM  { push(); }
         ;
      
*/

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

push()
{
st[top++]=yylval;
printf("*%f* ",st[top-1]);
}

xpr_eval(int ch)
{
double a=st[--top];
double b=st[--top];
printf("(%f %f) ",a,b);
switch(ch)
{
case 0: st[top++]=b+a;break;
case 1: st[top++]=b-a;break;
case 2: st[top++]=b*a;break;
case 3: st[top++]=b/a;break;  
}
printf("%f ",st[top-1]);
}
