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
 
                        /******Client Program*****/
 
 
int main(int argc, char *argv[])
{
printf("Beginning Raw Socket Programming\n");
//Variable Declarations
int sfd;
char buffer[PCKT_LEN];
struct ipheader *ip=(struct ipheader*) buffer;//Rename to iph
struct udpheader *udp=(struct udpheader*)(buffer +sizeof(struct ipheader));//Rename to udph
struct sockaddr_in sin, din;//DOES NOT HAVE TO BE SIN AND DIN!!!
int one=1;
const int *val=&one;//Curious to the purpose of this? Test later with just constant integer.
memset(buffer,'a',PCKT_LEN);//Memset to ensure no packet corruption?
 
//Baby Argument Checker
if(argc!=5){
printf("Invalid Parameters\n");
    }
 
/*Argument Checking*******This is the servers. The letters need to be changed back to the clients.
int argcounter;
printf("Number of arguments %d\n", argc);
for(argcounter=1;argcounter<14;argcounter++)
    {
    printf("Before switch argcounter is %d\n",argcounter);
     switch(argv[argcounter][1])
        {
        case 'p':
        argcounter++;
        printf("Heck Yeah Made it to %s\n",argv[argcounter]);
        break;
        case 'r':      
        argcounter++;
        printf("Heck Yeah Made it to %s\n",argv[argcounter]);
        break;
        case 'q':
        argcounter++;
        printf("Heck Yeah Made it to %s\n",argv[argcounter]);
        break;
        case 'l':
        argcounter++;
        printf("Heck Yeah Made it to %s\n",argv[argcounter]);
        break;
        case 'f':
        argcounter++;
        printf("Heck Yeah Made it to %s\n",argv[argcounter]);
        break;
        case 'h':
        argcounter++;
        printf("Heck Yeah Made it to %s\n",argv[argcounter]);
        break;
        case 't':
        argcounter++;
        printf("Heck Yeah Made it to %s\n",argv[argcounter]);
        break;
        default:
        printf("Incorrect Argument Use\n");
        break;
        }*/
 
 
//Creating a raw socket using the UDP protocol.
sfd=socket(PF_INET,SOCK_RAW,IPPROTO_UDP);
if(sfd<0){
perror("socket() error\n");
exit(-1);
}
else{
printf("Socket was created\n");
}
//The Address Familys for my sockadd_in structs.
sin.sin_family=AF_INET;
din.sin_family=AF_INET;
//Port Numbers--This will go in my argument checker.
sin.sin_port=htons(atoi(argv[2]));
//din.sin_port=htons(atoi(argv[4]));
din.sin_port=0;
//IP Addresses--This will go in my argument checker--Used old way in internet example.(E.g "inet_address()")
if(inet_pton(AF_INET,argv[1],&sin.sin_addr)<0){
perror("inet_pton() error\n");
}
if(inet_pton(AF_INET,argv[3],&din.sin_addr)<0){
perror("inet_pton() error\n");
}
//Creating my own IP Header
ip->iph_ihl=4;
ip->iph_ver=4;
ip->iph_tos=16;
ip->iph_len=sizeof(struct ipheader)+sizeof(struct udpheader);
ip->iph_ident=htons(54321);
ip->iph_ttl=64;
ip->iph_protocol=17;
//Source IP Address
if(inet_pton(AF_INET,argv[1],&ip->iph_sourceip)<0){
perror("inet_pton() error\n");
}
if(inet_pton(AF_INET,argv[3],&ip->iph_destip)<0){
perror("inet_pton() error\n");
}
//Creating UDP Header
udp->udph_srcport=htons(atoi(argv[2]));
udp->udph_destport=htons(atoi(argv[4]));
udp->udph_len=htons(sizeof(struct udpheader));
//Calculating Checksum for my packet
ip->iph_chksum=csum((unsigned short*)buffer,sizeof(struct ipheader) + sizeof(struct udpheader));
//Informing the kernel not to fill the packet. We will do that.
if(setsockopt(sfd,IPPROTO_IP,IP_HDRINCL,val,sizeof(one))<0){
perror("setsockopt() error\n");
exit(-1);
}
else{
printf("setsockopt() is doing ok\n");
}
 
printf("Using:::::Source IP: %s port: %u, Target IP: %s port: %u.\n", argv[1], atoi(argv[2]), argv[3], atoi(argv[4]));
int count;
for(count = 0; count < 40; count++)
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
