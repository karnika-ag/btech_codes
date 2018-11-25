letter [a-zA-Z]  
digit[0-9]  
%%  
[ \t]		;
[ \n]       {yylineno=yylineno+1;}
int         return INT;     
main        return MAIN;
float       return FLOAT;
char        return CHAR;
double      return DOUBLE;
void        return VOID;
long        return LONG;
const       return CONST;
typedef     return TYPEDEF;
while       return WHILE;
for         return FOR;
do          return DO;
if          return IF;
else        return ELSE;
break       return BREAK;
continue    return BREAK;
switch      return SWITCH;
case        return CASE;
default     {printf("**%s** ",yytext);return DEFAULT;}
struct      return STRUCT;
return      return RETURN;
printf("(".*")")      ;
{digit}+    return NUM;
{letter}({letter}|{digit})*  return ID;
"\\n"|"\\b"|"\\t"|"\\a" ;
">="        return GE;
"<="	    return LE;
"=="        return EE;
"!="        return NE;
"+="        return AE;
"-="        return SE;
"*="        return ME;
"/="        return DE;
"="         return ASGN;
">"         return GT;
"<"         return LT;
"+"         return ADD;
"-"         return SUB;
"*"         return MUL;
"/"         return DIV;
"@"         return MOD;
"."         return DOT;
"&&"        return LA;
"||"        return LO;
"&"         return BA;
"|"         return BO;
"^"         return BXOR;
\/\/.*               ;
\/\*(.*\n)*.*\*\/    ;
. return yytext[0];
%%
