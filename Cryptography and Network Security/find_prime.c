#include<stdio.h>
#include<gmp.h>
int main(int argc,char *argv[])
{
  mpz_t no,stored_no;
  mpz_init(no);
  mpz_set_str(no,argv[1],10);
  mpz_init(stored_no);
  mpz_set(stored_no,no);
  int count[100];
  mpz_t base[100],n,r,q,p;
  mpz_init(p);
  mpz_init(q);
  mpz_init(r);
  mpz_init(n);
  int i,j;
  for(i=0;i<100;i++)
  {
   mpz_init(base[i]);
   count[i]=0;
  }
  mpz_set_str(n,"1",10);
  i=0;
  while(mpz_cmp_si(no,1)!=0)
  {
    mpz_nextprime(p,n);
    mpz_mod(r,no,p);
    mpz_set(n,p);
    if(mpz_cmp_si(r,0)==0)
    {
	for(j=0;j<i;j++)
	{
	 if(mpz_cmp(base[j],p)==0)
	 {
	   count[j]++;break;
	 }
	}
        if(i==j)
        {
          mpz_set(base[i],p);
          count[i]++;
          i++;
        } 
        mpz_cdiv_q(q,no,p);
	mpz_set(no,q);
     	mpz_set_str(n,"1",10);
    }
  }
   gmp_printf("No factored into powers of prime:\n");
    gmp_printf("%Zd : ",stored_no);
    for(j=0;j<i;j++)
    {
     gmp_printf(" (%Zd^",base[j]);printf("%d)" ,count[j]); 
    }
   printf("\n");
  
}
