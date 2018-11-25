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
char buffer[PCKT_LEN];
struct iphdr *ip=(struct iphdr*) buffer;
struct udphdr *udp=(struct udphdr*)(buffer +sizeof(struct ipheader));
struct sockaddr_in sin, din;
int one=1;
const int *val=&one;
memset(buffer,'a',PCKT_LEN);
 

if(argc!=5){
printf("Invalid Parameters\n");
    }
 
 
sfd=socket(PF_INET,SOCK_RAW,IPPROTO_UDP);
perror("socket() create");

setsockopt(sfd,IPPROTO_IP,IP_HDRINCL,&one,sizeof(one));
perror("setsockopt");

//The Address Familys for my sockadd_in structs.
sin.sin_family=AF_INET;
din.sin_family=AF_INET;

//Port Numbers--This will go in my argument checker.
sin.sin_port=htons(atoi(argv[2]));
//din.sin_port=htons(atoi(argv[4]));
din.sin_port=0;
sin.sin_addr.s_addr=inet_addr (argv[1]);
din.sin_addr.s_addr=inet_addr (argv[3]);


//creating own ip header
    ip->ihl = 5;
    ip->version = 4;
    ip->tos = 0;
    ip->tot_len=sizeof(struct ipheader)+sizeof(struct udpheader);
    ip->id = htonl (54321); //Id of this packet
    ip->frag_off = 0;
    ip->ttl = 255;
    ip->protocol = IPPROTO_UDP;
    ip->check = 0;
    ip->saddr = inet_addr(argv[1]);    //Spoof the source ip address
    ip->daddr = inet_addr(argv[3]);

//Creating UDP Header
udp->source=htons(atoi(argv[2]));
udp->dest=htons(atoi(argv[4]));
udp->len=htons(sizeof(struct udpheader));
udp->check = 0;

//Calculating Checksum for my packet
ip->check=csum((unsigned short*)buffer,sizeof(struct ipheader) + sizeof(struct udpheader));
//Informing the kernel not to fill the packet. We will do that.


 
printf("Using:::::Source IP: %s port: %u, Target IP: %s port: %u.\n", argv[1], atoi(argv[2]), argv[3], atoi(argv[4]));
int count;
for(count = 0; count < 40; count++)
{
    if(sendto(sfd,buffer,ip->tot_len,0,(struct sockaddr*)&sin,sizeof(sin))<0){
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
