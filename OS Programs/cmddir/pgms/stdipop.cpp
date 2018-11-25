#include<stdio.h>
int main()
{
int c;
while((c=getc(stdin))!=EOF)
{
if(putc(c,stdout)==EOF)
break;
}
return 0;
}
