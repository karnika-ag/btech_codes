#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <string.h>
#include "ipudp.h"
#include "csum.h"
#define SERVER_PORT 5027
 
   
 
int main(int argc, char* argv[])
{

int sfd;
//int  new_sfd;
char buffer[PCKT_LEN];
char hbuf[NI_MAXHOST],sbuf[NI_MAXSERV];
//struct ipheader *ip=(struct ipheader*)buffer;//Rename to iph
//struct udpheader *udp=(struct udpheader*)(buffer + sizeof(struct ipheader));//Rename to udph
struct sockaddr_in sin, din;//DOES NOT HAVE TO BE SIN AND DIN!!!
//int one=1;
//**Unused Variable const int *val=&one;
struct sockaddr_storage inc_packet;
socklen_t inc_packetl;
int bytes_read;
memset(buffer,0,PCKT_LEN);
     


sin.sin_family=AF_INET;
sin.sin_port=htons(SERVER_PORT);
if(inet_pton(AF_INET,"127.0.0.2",&sin.sin_addr)<0){
perror("inet_pton() error\n");
}
else{
printf("inet_pton() doing ok\n");
}
perror("inet");


din.sin_family=AF_INET;


sfd=socket(AF_INET,SOCK_DGRAM,0);

perror("sfd");
if(sfd<0){
perror("socket() error\n");
exit(-1);
}
else{
printf("Socket was created\n");
}
if(bind(sfd,(struct sockaddr*)&sin,sizeof(sin))<0){
perror("bind() error\n");
exit(-1);
}
else{
printf("bind() is doing ok\n");
}
perror("bind");


int x =0;
inc_packetl=sizeof(struct sockaddr_storage);
while(x!=10){

printf("Waiting after bind\n");
bytes_read=recvfrom(sfd,buffer,PCKT_LEN,0,(struct sockaddr*)&inc_packet,&inc_packetl); 
printf("somthng hapnd\n");

if(bytes_read==0){
printf("Message Read\n");
}

printf("Printing Buffer Stuff %s\n",buffer);

if(getnameinfo((struct sockaddr*)&inc_packet,inc_packetl,hbuf,sizeof(hbuf),sbuf,sizeof(sbuf),0)<0){
perror("getnameinfo() error\n");
}
else{
printf("Host name found\n");
}
printf("Host:%s,  Serv:%s\n",hbuf,sbuf);

x++;
}
close(sfd);
return 0;
}
