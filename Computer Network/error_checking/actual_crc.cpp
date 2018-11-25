#include<stdio.h>
#include<string.h>
using namespace std;
#define MAX 100
char code[MAX];
char div[MAX];
int main()
{
   printf("enter the code which receiver receives :  \n");
   scanf("%s",code);
   printf("enter the divisor: \n");
   scanf("%s",div);
   int i,j;
   int l1,l2;
   l1=strlen(code);
   l2=strlen(div);
   j=0;
   for(i=0;i<l1;i++)
   {
     k=i;
     for(j=0;j<l2 ;j++)
     {
         if(k<l1)
         {
	     if(j==0)
	     {
		       while(div[j]<code[k])
		       {
		       j=0;
		       k++;
		       }
	       
	           if(div[j]==code[k])code[k]='0';
	           else code[k]='1';  
	            
	     }
	     else
	     {
		if(div[i]==
	     }
	     
	     k++;
	  }   
     }
   }
   
}
