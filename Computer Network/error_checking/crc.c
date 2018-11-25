#include<stdio.h>
#include<string.h>
#include<math.h>
using namespace std;
char code[500];
int arr[][8]={{1,3,5,7,9,11,0},{2,3,6,7,10,11,0},{1,5,6,7,0},{8,9,10,11,0}};
int main()
{
printf("enter code which sender sends\n");
scanf("%s",code);
int i,j;
/*
for(i=0;i<4;i++)
{
   j=0;
   while(arr[i][j]!=0)
   {
   printf("%d  ",arr[i][j]);
   j++;
   }
   printf("\n");
}
*/
int ans=0,pos,count,k;
int len=strlen(code);
ans=0;
for(i=0;i<4;i++)
{
  k=0;
  count=0;
  while(arr[i][k]!=0)
  {
     pos=arr[i][k];
     pos--;
     if(pos<len)
     {
        if( code[pos]-'0')
        {
          count++;
        }
     }
     k++;
  }
  if(count&1)
  ans+=(int)pow(2,i);
}

printf("error is in position %d\n",ans);
printf("flip bit at position %d from %d to ",ans,(code[ans-1]-'0'));
if(code[ans-1]-'0')
printf("0\n"); 
else
printf("1\n");
return 0;
}
