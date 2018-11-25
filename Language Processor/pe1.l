digit [0-9]
%%
[ \t]  ;
{digit}+ {yylval=atoi(yytext);return NUM;}
[A-Za-z] ;
. return yytext[0];

%%
