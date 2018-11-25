%{
#include<stdio.h>
#include<stdlib.h>
int st[100];
int top=0;

%}	

%token NUM

%%

pgm: expr  {printf("%d",st[top--]);}
     ;

expr: expr expr '+' {xpr_eval(0);}
      |expr expr '-' {xpr_eval(1);}
      |expr expr '*' {xpr_eval(2);}
      |expr expr '/' {xpr_eval(3);}
      | NUM {push();}
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

push()
{
st[top++]=yylval;
printf("*%d* ",st[top-1]);
}

xpr_eval(int ch)
{
int a=st[--top];
int b=st[--top];
printf("(%d %d) ",a,b);
switch(ch)
{
case 0: st[top++]=b+a;break;
case 1: st[top++]=b-a;break;
case 2: st[top++]=b*a;break;
case 3: st[top++]=b/a;break;  
}
printf("%d ",st[top-1]);
}
