%{
    #include<stdio.h>
    int num,r,digit=0,count,pcount=0,i;
    char a[20];
%}

%token NUM STRING
%%

pgm: NUM {convert();} pgm
     |
     STRING {printdata();} pgm
     |
     ;


%%

#include <ctype.h>
#include"lex.yy.c"
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

printdata()
{
printf("%s",yytext);
}

convert()
{
 num=atoi(yytext);
        while(num!=0)
        {
            r=num%16;
            digit='0'+r;
            if(digit>'9')
            digit+=7;
            a[count++]=digit;
            num=num/16;
        }
        for(i=count-1;i>=pcount;--i)
                printf("%c",a[i]);
          //printf(" ");
                pcount=count;

}
