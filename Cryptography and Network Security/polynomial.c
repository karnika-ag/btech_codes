#include<stdio.h>
#include<gmp.h>
int main(int argc,char *argv[])
{
int d1,d2,i;

printf("enter the first polynomial degree\n");
scanf("%d",&d1);
int p1[d1+1];
printf("Enter coefficients\n");
for(i=0;i<=d1;i++)
{
printf(" x^%d:",i);
scanf("%d",&p1[i]);
}

printf("enter the second polynomial degree\n");
scanf("%d",&d2);
int p2[d2+1];
printf("Enter coefficients\n");
for(i=0;i<=d2;i++)
{
printf(" x^%d:",i);
scanf("%d",&p2[i]);
}

printf("Both the polynomials are:\n");
for(i=d1;i>=0;i--)
{
printf("%d(x^%d)",p1[i],i);
if(i!=0)
printf("+");
}
printf("\n");
for(i=d2;i>=0;i--)
{
printf("%d(x^%d)",p2[i],i);
if(i!=0)
printf("+");
}

}
