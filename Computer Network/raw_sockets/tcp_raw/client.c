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
 
int main(int argc, char *argv[])
{
printf("Beginning Raw Socket Programming\n");

int sfd;
int one=1;
const int *val=&one;
char buffer[PCKT_LEN];
struct ipheader *ip=(struct ipheader*) buffer;//Rename to iph
struct udpheader *udp=(struct udpheader*)(buffer +sizeof(struct ipheader));
struct sockaddr_in sin, din;


memset(buffer,'a',PCKT_LEN);
 

if(argc!=5){
printf("Invalid Parameters\n");
    }
 


sfd=socket(AF_INET,SOCK_RAW,IPPROTO_RAW);
if(sfd<0){
perror("socket() error\n");
exit(-1);
}
else{
perror("socket");
}

sin.sin_family=AF_INET;
sin.sin_port=htons(atoi(argv[2]));
if(inet_pton(AF_INET,argv[1],&sin.sin_addr)<0){
perror("inet_pton() error\n");
}


din.sin_family=AF_INET;
din.sin_port=htons(atoi(argv[4]));
if(inet_pton(AF_INET,argv[3],&din.sin_addr)<0){
perror("inet_pton() error\n");
}


ip->iph_ihl=5;
ip->iph_ver=4;
ip->iph_tos=16;
ip->iph_len=sizeof(struct ipheader)+sizeof(struct udpheader);
ip->iph_ident=htons(54321);
ip->iph_ttl=64;
ip->iph_protocol=17;

if(inet_pton(AF_INET,argv[1],&ip->iph_sourceip)<0){
perror("inet_pton() error\n");
}
if(inet_pton(AF_INET,argv[3],&ip->iph_destip)<0){
perror("inet_pton() error\n");
}


udp->udph_srcport=htons(atoi(argv[2]));
udp->udph_destport=htons(atoi(argv[4]));
udp->udph_len=htons(sizeof(struct udpheader));
ip->iph_chksum=csum((unsigned short*)buffer,sizeof(struct ipheader) + sizeof(struct udpheader));


if(setsockopt(sfd,IPPROTO_IP,IP_HDRINCL,val,sizeof(one))<0){
perror("setsockopt() error\n");
exit(-1);
}
else{
printf("setsockopt() is doing ok\n");
}

 
printf("Source IP: %s port: %u, Target IP: %s port: %u.\n", argv[1], atoi(argv[2]), argv[3], atoi(argv[4]));


int count;
for(count = 0; count < 10; count++)
{

if(sendto(sfd,buffer,ip->iph_len,0,(struct sockaddr*)&sin,sizeof(sin))<0){
perror("sendto() error\n");
}
else{
printf("Count #%u - sendto() is OK\n", count);
sleep(2);
}

}
close(sfd);
return 0;
}
