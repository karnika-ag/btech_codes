#include<stdio.h>
#include<gmp.h>
int main(int argc,char *argv[])
{
mpz_t a,i,t,q,ans1,ans2,ans,n;
mpz_init(a);
mpz_init(t);
mpz_init(q);
mpz_init(i);
mpz_init(ans1);
mpz_init(ans2);
mpz_init(ans);
mpz_init(n);
int count=0;
if(argc<2)
{
printf("Please give the number\n");
return;
}
mpz_set_str(n,argv[1],10);
mpz_set_str(a,argv[1],10);
mpz_set_ui(ans,1);
mpz_set_ui(i,2);
while(mpz_cmp_ui(a,1)!=0)
{
mpz_mod(t,a,i);
if(mpz_cmp_ui(t,0)==0)
{
count++;
mpz_div(a,a,i);
}
else if(count>0)
{
mpz_pow_ui(ans1,i,count);
mpz_pow_ui(ans2,i,count-1);
mpz_sub(ans1,ans1,ans2);
mpz_mul(ans,ans,ans1);
mpz_nextprime(i,i);
count=0;
}
else
{
mpz_nextprime(i,i);
}
}
mpz_pow_ui(ans1,i,count);
mpz_pow_ui(ans2,i,count-1);
mpz_sub(ans1,ans1,ans2);
mpz_mul(ans,ans,ans1);
gmp_printf("phi of %Zd is %Zd ",n,ans);
}
