alpha [A-Za-z]
digit [0-9]
%%
{alpha}({alpha}|{digit})*  return ID;
{digit}+  return NUM;
[\n \t]   ;
.  return yytext[0];
%%
