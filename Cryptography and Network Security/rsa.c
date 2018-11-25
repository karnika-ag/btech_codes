#include<stdio.h>
#include<gmp.h>
int main(int argc,char *argv[])
{
mpz_t p,q,n,phi_n,sub,p1,q1,e,d,count,res,mesg,cip,ptext;
mpz_init(p);
mpz_init(q);
mpz_init(n);
mpz_init(sub);
mpz_init(p1);
mpz_init(q1);
mpz_init(phi_n);
mpz_init(count);
mpz_init(e);
mpz_init(d);
mpz_init(res);
mpz_init(mesg);
mpz_init(cip);
mpz_init(ptext);

gmp_randstate_t st;
gmp_randinit_mt(st);
//mpz_urandomb (mpz t rop , gmp randstate t state , mp bitcnt t n
mpz_urandomb(p,st,512);
mpz_urandomb(q,st,512);
mpz_nextprime(p,p);
mpz_nextprime(q,q);
gmp_printf("P:%Zd Q:%Zd\n",p,q);

/*
if(argc<3)
{
printf("Please enter 2 large primes\n");
return ;
}
*/
//mpz_set_str(p,argv[1],10);
//mpz_set_str(q,argv[2],10);
mpz_mul(n,p,q);
mpz_set_si(sub,1);
mpz_set_si(count,1);
mpz_sub(p1,p,sub);
mpz_sub(q1,q,sub);
mpz_mul(phi_n,p1,q1);
gmp_printf("P:%Zd Q:%Zd N:%Zd p1:%Zd q1:%Zd phi_n:%Zd: ",p,q,n,p1,q1,phi_n);
mpz_set_si(e,2);
while(mpz_cmp(phi_n,count)>0)
{
mpz_gcd(res,phi_n,e);
if(mpz_cmp_ui(res,1)==0)
{
break;
}
mpz_nextprime(e,e);
}
gmp_printf("e : %Zd \n",e);
mpz_invert(d,e,phi_n);
gmp_printf("d : %Zd \n",d);
printf("Enter message u want to send\n");
mpz_inp_str(mesg,stdin,10);
mpz_powm (cip,mesg,e,n);
gmp_printf("Ciphered text : %Zd \n",cip);
mpz_powm (ptext,cip,d,n);
gmp_printf("Deciphered text : %Zd \n",ptext);
}
