%{
#include<stdio.h>
#include<stdlib.h>
%}
%token INT FLOAT CHAR DOUBLE VOID LONG CONST TYPEDEF STRUCT
%token FOR DO WHILE BREAK CONTINUE
%token IF ELSE SWITCH CASE DEFAULT
%token NUM ID MAIN
%token DOT RETURN
%left ADD SUB MUL DIV AE SE ME DE
%left LE GE EE NE LT GT LO LA BO BA BXOR
%right ASGN MOD "else"
%left '{'
%%
pgm : data_type MAIN '(' ')' block
      ;

block : '{' stmtlist '}'
;
stmtlist : block
|
stmtlist stmt
|
;
stmt : decl ';'
|assignment ';'
|ifelsestmt
|whilestmt|switchstmt
;
decl : data_type { set_datatype(); } varlist //set_datatype() will store datatype in tmp
;
varlist : varlist ',' ID { var_decl();}
|
ID { var_decl(); } //var_decl store id in symbol table
;
assignment : ID { check_decl(); push();} assgn1 //check_decl() checks for redeclaration
;
assgn1 : ASGN {push();} expr {exp_asgn_evaluate();}
//evaluate expr
|
AE {push1("+");} expr{exp_evaluate(); } {exp_asgn_evaluate();} //shorthand operators
//grm rules
|
SE {push1("-");} expr{exp_evaluate(); } {exp_asgn_evaluate();}
|
ME {push1("*");} expr{exp_evaluate(); } {exp_asgn_evaluate();}
|
DE {push1("/");} expr{exp_evaluate(); } {exp_asgn_evaluate();}
;
ifelsestmt : IF '(' expr ')' { if_fun();} ifelsebody elsestmt //if_fun checks for cond nt satisfied
;
elsestmt : ELSE {else_fun();} ifelsebody {if_end();} //else_fun() to write goto of if end
| {if_end();}
;
ifelsebody : block
|
stmt
;
whilestmt : {while_begin();} WHILE '(' expr ')' {while_body();} whilebody
; //while_begin() to generate a label for while at start
whilebody : block {while_end();} //while_end() to write goto to while_begin label
|
stmt {while_end();}
;
switchstmt : SWITCH '(' expr ')' {switch_begin();} '{' switchbody '}'
;
switchbody : switchcase {switch_end();}
;
switchcase : CASE NUM {switchcase_fun();} ':' switcheval breakstmt
|
DEFAULT {switchdefault_fun();} ':' switcheval switchend
|
;
breakstmt : BREAK {break_fun();} ';' switchcase
|{no_break_fun();} switchcase
;
switchend : BREAK {break_fun();} ';'
|{no_break_fun();}
;
switcheval : stmtlist
;
expr : expr LO {push();} expr2 {exp_evaluate();}
|
expr2 //exp_evaluate() is to print 3 addr code as all values will be in stack
;expr2 : expr2 LA {push();} expr3 {exp_evaluate();}
|
expr3
;
expr3 : expr3 BO {push();} expr4 {exp_evaluate();}
|
expr4
;
expr4 : expr4 BXOR {push();} expr5 {exp_evaluate();}
|
expr5
;
expr5 : expr5 BA {push();} expr6 {exp_evaluate();}
|
expr6
;
expr6 : expr6 LT {push();} expr7 {exp_evaluate();}
|expr6 LE {push();} expr7 {exp_evaluate();}
|expr6 GT {push();} expr7 {exp_evaluate();}
|expr6 GE {push();} expr7 {exp_evaluate();}
|expr6 NE {push();} expr7 {exp_evaluate();}
|expr6 EE {push();} expr7 {exp_evaluate();}
|expr7
;
expr7 : expr7 ADD {push();} expr8 {exp_evaluate();}
|expr7 SUB {push();} expr8 {exp_evaluate();}
|expr8
;
expr8 : expr8 MUL {push();} expr9 {exp_evaluate();}
|expr8 DIV {push();} expr9 {exp_evaluate();}
|expr9
;
expr9 : expr10 MOD {push();} expr9 {exp_evaluate();}
|
expr10
;
expr10 : '(' expr ')'
| ID { check_decl();push();}
| NUM { push(); }
| SUB expr10 { unary_minus(); } // for unary minus here itself once write 3 addr code
//nd then push tht operator on stack
;
data_type : INT
|FLOAT
|CHAR
|DOUBLE
|VOID
|LONG
|BOOL
;
%%
#include <ctype.h>
#include"lex.yy.c"
int ltrack[200][20];
int lcount[200]={0};
int lab_no[200];
int lineno=0;
struct store
{
int flag;
char op1[100];
int no;
} fetch[10000];
int count=0;
char st[1000][10];
int top=0;
int tmp_no=0;
char temp[8];
int lab_store[200];
int lnum=0;
int ltop=0;
int switch_store[1000];
int stop=0;
char dtype[10];
struct SymbolTable
{
char id[20];
char type[10];
}sym_store[10000];
int sym_count=0;
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
outputcode();
return 0;
}
yyerror(char *s)
{
printf("Syntax Error In Line : %d : %s %s\n", yylineno, s, yytext );
}
push()
{
strcpy(st[++top],yytext);
}
push1(char ch[])
{
char ext[10];
strcpy(st[++top],"=");
strcpy(ext,st[top-1]);
strcpy(st[++top],ext);
strcpy(st[++top],ch);
}
unary_minus()
{
sprintf(temp,"t%d",tmp_no);fetch[lineno].flag=0;
strcpy(fetch[lineno].op1,temp);
strcat(fetch[lineno].op1,"=");
strcat(fetch[lineno].op1,"-");
strcat(fetch[lineno].op1,st[top]);
strcpy(st[top],temp);
tmp_no++;
lineno++;
}
exp_evaluate()
{
sprintf(temp,"t%d",tmp_no);
fetch[lineno].flag=0;
strcpy(fetch[lineno].op1,temp);
strcat(fetch[lineno].op1,"=");
strcat(fetch[lineno].op1,st[top-2]);
strcat(fetch[lineno].op1,st[top-1]);
strcat(fetch[lineno].op1,st[top]);
top-=2;
strcpy(st[top],temp);
tmp_no++;
lineno++;
}
exp_asgn_evaluate()
{
fetch[lineno].flag=0;
strcpy(fetch[lineno].op1,st[top-2]);
strcat(fetch[lineno].op1,"=");
strcat(fetch[lineno].op1,st[top]);
top-=3;
lineno++;
}
if_fun()
{
lnum++;
fetch[lineno].flag=1;
strcpy(fetch[lineno].op1,"if(not ");
strcat(fetch[lineno].op1,st[top]);
strcat(fetch[lineno].op1,") goto ");
ltrack[lnum][lcount[lnum]++]=lineno;
lab_store[++ltop]=lnum;
lineno++;
}
else_fun()
{
int x;
lnum++;
x=lab_store[ltop--];
fetch[lineno].flag=1;
strcpy(fetch[lineno].op1,"goto ");
ltrack[lnum][lcount[lnum]++]=lineno;
lineno++;
int u=0;
for(u=0;u<lcount[x];u++)
fetch[ltrack[x][u]].no=lineno;
lab_store[++ltop]=lnum;}
if_end()
{
int y;
y=lab_store[ltop--];
int u=0;
for(u=0;u<lcount[y];u++)
fetch[ltrack[y][u]].no=lineno;
top--;
}
while_begin()
{
lnum++;
lab_store[++ltop]=lnum;
lab_no[lnum]=lineno;
}
while_body()
{
lnum++;
fetch[lineno].flag=1;
strcpy(fetch[lineno].op1,"if(not ");
strcat(fetch[lineno].op1,st[top]);
strcat(fetch[lineno].op1,") goto ");
ltrack[lnum][lcount[lnum]++]=lineno;
lab_store[++ltop]=lnum;
lineno++;
}
while_end()
{
int x,y;
y=lab_store[ltop--];
x=lab_store[ltop--];
fetch[lineno].flag=1;
strcpy(fetch[lineno].op1,"goto ");
fetch[lineno].no=lab_no[x];
lineno++;
int u=0;
for(u=0;u<lcount[y];u++)
fetch[ltrack[y][u]].no=lineno;
top--;
}
switch_begin()
{
lnum++;
lab_store[++ltop]=lnum;
lnum++;
lab_store[++ltop]=lnum;
switch_store[++stop]=1;
}
switchcase_fun()
{
int x,y,ck;
ck=switch_store[stop--];
if(ck==1)
{
x=lab_store[ltop--];}
else if(ck==2)
{
y=lab_store[ltop--];
x=lab_store[ltop--];
}
int u=0;
for(u=0;u<lcount[x];u++)
fetch[ltrack[x][u]].no=lineno;
lnum++;
lab_store[++ltop]=lnum;
fetch[lineno].flag=1;
strcpy(fetch[lineno].op1,"if(");
strcat(fetch[lineno].op1,st[top]);
strcat(fetch[lineno].op1,"!=");
strcat(fetch[lineno].op1,yytext);
strcat(fetch[lineno].op1,") goto ");
ltrack[lab_store[ltop]][lcount[lab_store[ltop]]++]=lineno;
lineno++;
if(ck==2)
{
u=0;
for(u=0;u<lcount[y];u++)
fetch[ltrack[y][u]].no=lineno;
}
}
switchdefault_fun()
{
int x,y,ck;
ck=switch_store[stop--];
if(ck==1)
{
x=lab_store[ltop--];
}
else if(ck==2)
{
y=lab_store[ltop--];
x=lab_store[ltop--];
}
int u=0;
for(u=0;u<lcount[x];u++)
fetch[ltrack[x][u]].no=lineno;
lnum++;
lab_store[++ltop]=lnum;
if(ck==2)
{
u=0;
for(u=0;u<lcount[y];u++)
fetch[ltrack[y][u]].no=lineno;
}
}
break_fun()
{
switch_store[++stop]=1;
fetch[lineno].flag=1;
strcpy(fetch[lineno].op1,"goto ");ltrack[lab_store[ltop-1]][lcount[lab_store[ltop-1]]++]=lineno;
lineno++;
}
no_break_fun()
{
switch_store[++stop]=2;
lnum++;
lab_store[++ltop]=lnum;
fetch[lineno].flag=1;
strcpy(fetch[lineno].op1,"goto ");
ltrack[lab_store[ltop]][lcount[lab_store[ltop]]++]=lineno;
lineno++;
}
switch_end()
{
int x,y,ck;
ck=switch_store[stop--];
if(ck==1)
{
x=lab_store[ltop--];
}
else if(ck==2)
{
y=lab_store[ltop--];
x=lab_store[ltop--];
}
int u=0;
for(u=0;u<lcount[x];u++)
fetch[ltrack[x][u]].no=lineno;
if(ck==2)
{
u=0;
for(u=0;u<lcount[y];u++)
fetch[ltrack[y][u]].no=lineno;
}
x=lab_store[ltop--];
u=0;
for(u=0;u<lcount[x];u++)
fetch[ltrack[x][u]].no=lineno;
top--;
stop--;
}
set_datatype()
{
strcpy(dtype,yytext);
}
int is_predeclare(char temp[])
{
int i;
for(i=0;i<sym_count;i++)
{
if(!strcmp(sym_store[i].id,temp))
return 1;
}
return 0;}
var_decl()
{
char temp[20];
strcpy(temp,yytext);
if(is_predeclare(temp))
{
yyerror("Redeclaration of variable ");
exit(0);
}
else
{
strcpy(sym_store[sym_count].id,temp);
strcpy(sym_store[sym_count].type,dtype);
sym_count++;
}
}
check_decl()
{
char temp[20];
strcpy(temp,yytext);
int flag=0,i;
for(i=0;i<sym_count;i++)
{
if(!strcmp(sym_store[i].id,temp))
{
flag=1;
break;
}
}
if(!flag)
{
yyerror("Not Predeclared variable ");
exit(0);
}
}
outputcode()
{
int u=0;
for(u=0;u<lcount[lineno];u++)
{
fetch[ltrack[lineno][u]].no=lineno;
}
for(u=0;u<lineno;u++)
{
if(fetch[u].flag==0)
printf("%d: %s\n",u,fetch[u].op1);
else
{
printf("%d: %s ",u,fetch[u].op1);
printf("%d\n",fetch[u].no);
}
}
printf("%d: PGM END\n",lineno);
}
