DIGIT [0-9]

%%
{DIGIT}+     return NUM;
.        return STRING;
%%

