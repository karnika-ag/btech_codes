#include<gmp.h>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<sys/time.h>
#include<strings.h>
#include<netinet/in.h>

int main()
{

  mpz_t p,q,phi_n,p1,q1,n,M,C,gcd,bits_512,random,e,d;
  mpz_inits(p,q,phi_n,p1,q1,n,M,C,gcd,bits_512,random,e,d,NULL);
  char *buffer;
  buffer= malloc(10000);

  mpz_ui_pow_ui(bits_512,2,512);

  gmp_randstate_t st;
  gmp_randinit_default(st);

  struct timeval t;
  gettimeofday(&t,NULL);
  int seed = t.tv_usec;

  gmp_randseed_ui(st,seed);

  mpz_urandomb(random,st,512);
  mpz_add(p,random,bits_512);
  mpz_nextprime(p,p);

  mpz_urandomb(random,st,512);
  mpz_add(q,random,bits_512);
  mpz_nextprime(q,q);

  mpz_sub_ui(p1,p,1);
  mpz_sub_ui(q1,q,1);

  mpz_mul(n,p,q);
  mpz_mul(phi_n,p1,q1);

  mpz_urandomb(random,st,512);
  mpz_add(e,random,bits_512);
  mpz_gcd(gcd,e,phi_n);

 while(mpz_cmp_ui(gcd,1)!=0)
 {
  mpz_urandomb(random,st,512);
  mpz_add(e,random,bits_512);
  mpz_gcd(gcd,e,phi_n);
 }

 mpz_invert(d,e,phi_n);
 
 int sfd=socket(AF_INET,SOCK_STREAM,0);
 if(sfd<0)
 {
   printf("error in creating socket\n");
   return 0;
 }

 struct sockaddr_in addr;
 bzero((char *)&addr,sizeof(addr));

 addr.sin_family = AF_INET;
 addr.sin_addr.s_addr = INADDR_ANY ;
 addr.sin_port = htons(2000);

 if(bind(sfd,(struct sockaddr *)&addr,sizeof(addr))<0)
 {
   printf("error in binding\n");
   return 0;
 } 

 listen(sfd,7);
 
  socklen_t len = sizeof(struct sockaddr_in);
  int nsfd= accept(sfd,(struct sockaddr *)&addr,&len);
  if(nsfd<0)
  {
   printf("error in accept\n");
   return 0;
  }
  else
  {
    printf("succesfully accept\n");

  }

  gmp_printf("n - %Zd\n",n);
  mpz_get_str(buffer,62,n);
  write(nsfd,buffer,10000);
  
  gmp_printf("e - %Zd\n",e);
  mpz_get_str(buffer,62,e);
  write(nsfd,buffer,10000);

  read(nsfd,buffer,10000);
  mpz_set_str(C,buffer,62);
  gmp_printf("C - %Zd\n",C);
  
  mpz_powm(M,C,d,n);
  gmp_printf("M - %Zd\n",M);
  mpz_get_str(buffer,62,M);
  printf("\nMessage is %s\n",buffer);


}
