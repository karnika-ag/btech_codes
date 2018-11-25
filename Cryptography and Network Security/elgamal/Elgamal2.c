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

 struct sockaddr_in server_addr,client_addr;
 int clientLen=sizeof(client_addr); 
 int fd,nsfd;
 fd=socket(AF_INET,SOCK_STREAM,0);
 server_addr.sin_family=AF_INET;
 server_addr.sin_addr.s_addr=INADDR_ANY;
 server_addr.sin_port=htons(atoi("2000"));
 bind(fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
 listen(fd,10);
 printf("Now Listening \n");
 mpz_t P,g,y1,x2,y2,k2,M,k,session_key,C1,C2;
 mpz_init(P);
 mpz_init(g);
 mpz_init(y1);
 mpz_init(x2);
 mpz_init(y2);
 mpz_init(k);
 mpz_init(k2);
 mpz_init(M);
 mpz_init(session_key);
 mpz_init(C1);
 mpz_init(C2);

 char msg[256];
 int n,i;
 nsfd=accept(fd,(struct sockaddr *)&client_addr,&clientLen);
 gmp_printf("client connected \n");
 
 n=read(nsfd,msg,256);
 mpz_set_str(P,msg,10);
 if(n>0) gmp_printf("msg received : prime is %Zd \n",P);
 memset(msg,'\0',256);
 n=0;
 n=read(nsfd,msg,256);
 mpz_set_str(g,msg,10);
 if(n>0) gmp_printf("msg received : generator is %Zd \n",g);
 memset(msg,'\0',256);
 n=0;
 n=read(nsfd,msg,256);
 mpz_set_str(y1,msg,10);
 if(n>0) gmp_printf("msg received : y1 is %Zd \n",y1);
 memset(msg,'\0',256);

//choosing random x2 and calculating y2..
 gmp_randstate_t state;
 gmp_randinit_mt(state);
 i=1;
 mpz_sub_ui(P,P,i);
 mpz_urandomm(x2,state,P);
 mpz_add_ui(P,P,i);
 mpz_powm(y2,g,x2,P);

//sending y2.. 
 mpz_get_str(msg,10,y2);
 write(nsfd,msg,sizeof(msg));

//calculating key..
 mpz_powm(k2,y1,x2,P);
 gmp_printf("key on 2: %Zd \n",k2);

//entering message..
 gmp_printf("enter message less than %Zd \n",P);
 gmp_scanf("%Zd",M);

//select random k and calculating session key
 mpz_urandomm(k,state,P);
 mpz_powm(session_key,y1,k,P);
 gmp_printf("calculated session key is : %Zd \n",session_key);

 //calculating c1 and c2
 mpz_powm(C1,g,k,P);
 mpz_mul(C2,session_key,M);
 mpz_mod(C2,C2,P);
 gmp_printf("cipher text: %Zd %Zd \n",C1,C2);

//sending cipher text..
 memset(msg,'\0',256);
 mpz_get_str(msg,10,C1);
 write(nsfd,msg,sizeof(msg));
 memset(msg,'\0',256);
 mpz_get_str(msg,10,C2);
 write(nsfd,msg,sizeof(msg));

}
