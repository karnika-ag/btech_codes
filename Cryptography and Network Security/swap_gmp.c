#include<gmp.h>
#include<stdio.h>
swap(mpz_t a , mpz_t b)
{
	mpz_t temp;
	mpz_init(temp);
	mpz_set(temp,a);
	mpz_set(a,b);
	mpz_set(b,temp);
	gmp_printf ("Inside swap function  a: %Zd b: %Zd\n", a, b);
}
int main()
{
	mpz_t a,b;
	int i;
	mpz_init(a);
	mpz_init(b);
	printf("Enter 2 numbers: ");
	int n1,n2;
	scanf("%d %d",&n1,&n2);
	mpz_set_ui(a,n1);
	mpz_set_ui(b,n2);
	gmp_printf ("Before function call  a: %Zd b: %Zd\n", a, b);
	swap(a,b);
	//mpz_swap(a,b);
	gmp_printf ("After function call   a: %Zd b: %Zd\n", a, b);
	printf("hello\n");
	return 0;
}
