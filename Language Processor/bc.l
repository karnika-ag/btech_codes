digit [0-9]
%%
{digit}*[.]{digit}+ {yylval=atof(yytext); return NUM;}
{digit}+ {yylval=atof(yytext);return NUM;}
[A-Za-z] ;
. return yytext[0];

%%
