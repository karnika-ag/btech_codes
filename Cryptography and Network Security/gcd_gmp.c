#include<stdio.h>
#include<gmp.h>
gcd(mpz_t a , mpz_t b)
{
	if(mpz_cmp(a,b)<0)
	{
		mpz_swap(a,b);
	}
	if(mpz_cmp_si(b,0)==0)
		return;
	mpz_mod(a,a,b);
	mpz_swap(a,b);
	gcd(a,b);
}
int main()
{
	mpz_t a,b,check;
	long long int i;
	mpz_init(a);
	mpz_init(b);
	mpz_init(check);
	printf("Enter 2 numbers: ");
	long long int n1,n2;
	scanf("%lli %lli",&n1,&n2);
	mpz_set_si(a,n1);
	mpz_set_si(b,n2);
	mpz_gcd(check,a,b);
	gcd(a,b);
	printf("gcd of %lli and %lli is ",n1,n2);
	gmp_printf("%Zd\n",a);
	return 0;
}
