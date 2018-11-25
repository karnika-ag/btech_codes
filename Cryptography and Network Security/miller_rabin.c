#include<stdio.h>
#include<gmp.h>
int main(int argc,char *argv[])
{
mpz_t n,t,a,q,i,n1,k,k1,j;
mpz_init(n);
mpz_init(t);
mpz_init(n1);
mpz_init(a);
mpz_init(q);
mpz_init(i);
mpz_init(k);
mpz_init(k1);
mpz_init(j);
int flag=0;
int count=0;
if(argc<2)
{
printf("enter the no u want to check whether its prime or not");
return;
}
mpz_set_str(n,argv[1],10);
mpz_set_ui(k,0);
mpz_set_ui(i,2);
mpz_sub_ui(n1,n,1);
while(1)
{
mpz_mod(t,n1,i);
if(mpz_cmp_ui(t,0)==0)
{
mpz_add_ui(k,k,1);
mpz_div(n1,n1,i);
}
else
{
mpz_set(q,n1);
break;
}
}
gmp_printf("%Zd=(2^%Zd)%Zd\n",n,k,q);

gmp_randstate_t st;
gmp_randinit_mt(st);
mpz_sub_ui(n1,n,1);

	while(1)
	{
	mpz_urandomm(a,st,n1);
	gmp_printf("a:%Zd",a);
	flag=0;
	count++;
	if(count>6)
	break;
	mpz_powm(t,a,q,n);
		if(mpz_cmp_ui(t,1)==0)
		{
		printf(" inconclusive\n");
		}
		else
		{
		mpz_set_ui(j,0);
			while(mpz_cmp(j,k)!=0)
			{
			unsigned long temp= mpz_get_ui(j);
			mpz_pow_ui(t,i,temp);
			mpz_mul(t,t,q);
			mpz_powm(t,a,t,n);
			gmp_printf(" t:%Zd ",t);
				if(mpz_cmp(t,n1)==0)
				{
				printf("inconclusive\n");
				flag=1;
				break;
				}
			mpz_add_ui(j,j,1);
			}
			if(flag==0)
			{
			printf("composite\n");
			break;
			}
		}
	}
}
