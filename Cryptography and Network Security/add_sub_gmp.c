#include<gmp.h>
#include<stdio.h>
int main()
{
	mpz_t mul,sum;
	int 
	mpz_init(mul);
	mpz_init(sum);
	mpz_set_ui(mul,1);
	mpz_set_ui(sum,0);
	gmp_printf ("MUL: %Zd ADD: %Zd\n", mul, sum);
	for(i=1;i<=100;i++)
	{
		mpz_mul_ui(mul,mul,i);
		mpz_add_ui(sum,sum,i);
	}
	gmp_printf ("MUL: %Zd ADD: %Zd\n", mul, sum);
	printf("hello\n");
	return 0;
}
