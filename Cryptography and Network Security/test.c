#include<stdio.h>
#include<gmp.h>
int main()
{
mpz_t a,b;
mpz_init(a);
mpz_init(b);
mpz_inp_str(a,stdin,10);
mpz_inp_str(b,stdin,10);
gmp_printf("%Zs %Zs",a,b);

}
