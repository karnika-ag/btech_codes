//finding generator in multiplicative cyclic group
//deffie hellman key exchange..

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/select.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<gmp.h>

int main(int argc,char *argv[])
{
 int n1,fd;
 char msg[256];
 fd=socket(AF_INET,SOCK_STREAM,0);
 struct sockaddr_in client_addr,server_addr;
 struct hostent * server;

 client_addr.sin_family=AF_INET;
 client_addr.sin_addr.s_addr=INADDR_ANY;
 client_addr.sin_port=htons(atoi(argv[1]));
 bind(fd,(struct sockaddr *)&client_addr,sizeof(client_addr));
  
 server=gethostbyname("localhost");
 memset((char *)&server_addr,0,sizeof(server_addr));
 server_addr.sin_family=AF_INET;
 bcopy((char *)server->h_addr,(char *)&server_addr.sin_addr.s_addr,server->h_length);
 server_addr.sin_port=htons(1234);
 n1=connect(fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
 if(n1>=0) printf("connect succesful \n");

  int i=0,j=0,n;
  scanf("%d",&n);
  mpz_t Q[n],P,k,g,l,r,a,x1,x2,y1,y2,k1;
  mpz_init(P);
  mpz_init(k);
  mpz_init(g);
  mpz_init(l);
  mpz_init(r);
  mpz_init(a);
  mpz_init(x1);
  mpz_init(x2);
  mpz_init(y1);
  mpz_init(y2);
  mpz_init(k1);

  mpz_set_ui(a,19);
  for(i=0;i<n;i++) mpz_init(Q[i]);

 gmp_randstate_t state;
 gmp_randinit_mt(state);

//step 1... 
  do{
	  for(i=0;i<n;i++)
	  {
	    mpz_urandomb(Q[i],state,8);
	    mpz_nextprime(Q[i],Q[i]);
	  }
	//  gmp_printf("sargg\n");
	 mpz_mul(P,Q[0],Q[1]);
	 for(i=2;i<n;i+=2)
	 {
	    mpz_mul(P,Q[i],Q[i+1]);
	 }
	 i=1;
		 mpz_add_ui(P,P,i);
	 	j=mpz_probab_prime_p(P,25);
   }while(j!=2);
 
  gmp_printf("prime p is: %Zd\n",P);
  mpz_get_str(msg,10,P);
  write(fd,msg,sizeof(msg));
  memset(msg,'\0',256);
//step 2..
j=1;
 do{
 mpz_urandomm(g,state,a);
 i=1;
 mpz_add_ui(g,g,i);
 j=1;
//step 3.. 
 i=1;
 mpz_sub_ui(k,P,i);
 for(i=0;i<n;i++) 
 { 
    mpz_divexact(l,k,Q[i]);
    mpz_powm(r,g,l,P);
    if(mpz_cmp_si(r,1)==0) 
      {j=0; break;}
 }
 }while(j==0 && i!=n);

 gmp_printf("generator is %Zd \n",g);
 mpz_get_str(msg,10,g);
 write(fd,msg,sizeof(msg));
 memset(msg,'\0',256);

 //choosing random x1 and sending y1..
 mpz_urandomm(x1,state,P);
 mpz_powm(y1,g,x1,P);
 mpz_get_str(msg,10,y1);
 write(fd,msg,sizeof(msg));
 memset(msg,'\0',256);

 n=read(fd,msg,256);
 mpz_set_str(y2,msg,10);
 if(n>0) gmp_printf("msg received : %Zd \n",y2);
 memset(msg,'\0',256);

 mpz_powm(k1,y2,x1,P);
 gmp_printf("key on 1: %Zd \n",k1);

}
