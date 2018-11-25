#include<stdio.h>
#include<gmp.h>
void find_gcd(mpz_t r1,const mpz_t x,const mpz_t y)
{
 mpz_t a,b,q;
 mpz_t x1,x2,x3,y1,y2,y3;
 mpz_init(a); mpz_init(b); mpz_init(q);
 mpz_init(x1); mpz_init(x2); mpz_init(x3); mpz_init(y1); mpz_init(y2); mpz_init(y3);
 mpz_set(a,x); mpz_set(b,y);
 mpz_set_ui(x1,1);
 mpz_set_ui(x2,0);
 mpz_set_ui(y1,0);
 mpz_set_ui(y2,1);

 while(mpz_cmp_si(b,0)!=0)
 {
   mpz_mod(r1,a,b);
   mpz_fdiv_q(q,a,b);
   mpz_set(x3,x1);
   mpz_submul(x3,q,x2);
   mpz_set(y3,y1);
   mpz_submul(y3,q,y2);
   mpz_set(a,b);
   mpz_set(b,r1);
   mpz_set(x1,x2);
   mpz_set(x2,x3);
   mpz_set(y1,y2);
   mpz_set(y2,y3);
 }
 gmp_printf("gcd using function call x = %Zd y = %Zd \n",x1,y1);
 mpz_set(r1,a); 


}
int main(int argc, char *argv[])
{
 mpz_t x,y,r,r1;
  if(argc>=2)
  { 
   mpz_init(x);
   mpz_init(y);
   mpz_init(r);
   mpz_init(r1);
   mpz_set_str(x,argv[1],10);
   mpz_set_str(y,argv[2],10);
   gmp_printf("x=%Zd y=%Zd are inputs \n",x,y);
   mpz_gcd(r,x,y);
   find_gcd(r1,x,y);
   gmp_printf("GCD by function is %Zd,user function %Zd\n",r,r1);
   mpz_clear(x);
   mpz_clear(y);
   mpz_clear(r);
  }
}
