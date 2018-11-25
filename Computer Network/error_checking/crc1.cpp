#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAX 100
using namespace std;
char code[500];
char store[MAX];
int arr[MAX][MAX];
int num[MAX];
int plc[MAX]={1,2,4,8,16,32,64,128};
int val;
void precompute()
{
int i,j,k,tmp,val;
for(i=1;i<=64;i++)
{
   k=0;
   tmp=i;
   while(tmp)
   {
       if(tmp&1)
       {
          arr[k][num[k]]=i;
          num[k]++;
       }
       k++;
       tmp=tmp>>1;
   }   
}
}
int main()
{
precompute();
printf("enter code which sender sends\n");
scanf("%s",code);
int i,j,k;
int len=strlen(code);
k=1;
for(i=0;i<len;i++)
{
   if(find(k)==0)
   {
      store[k]=code[i];
   }
   else
   i--;
   
   k++;
   
}

/*for(i=0;i<=6;i++)
{
   for(j=0;j<64;j++)
   {
   printf("%d  ",arr[i][j]);
   }
   printf("\n");
}*/

int ans=0,pos,count,k;

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
     else
     {
     break;
     }
     k++;
  }
  if(count&1)
  ans+=(int)pow(2,i);
}

printf("error is in position %d\n",ans);
printf("flip bit at position %d from %d to ",ans,(code[ans-1]-'0'));
if(code[ans-1]-'0')
{
printf("0\n"); 
code[ans-1]='0';
printf("correct code is %s \n",code);
}
else
{
printf("1\n");
code[ans-1]='1';
printf("correct code is %s \n",code);
}
return 0;
}
