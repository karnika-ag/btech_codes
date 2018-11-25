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
#define SERVER_PORT 5025
 
    /******Server Program*****/
 
int main(int argc, char* argv[])
{
//Variable Declarations
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
     
/*
//Argument Checking
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
        }
    }
*/
//Address Family
sin.sin_family=AF_INET;
din.sin_family=AF_INET;
//Port Numbers
sin.sin_port=htons(SERVER_PORT);
//din.sin_port=client port argument.
//IP Addresses
if(inet_pton(AF_INET,"127.0.0.1",&sin.sin_addr)<0){
perror("inet_pton() error\n");
}
else{
printf("inet_pton() doing ok\n");
}
perror("inet");
//Include IP Address for Client
 
//Creating a raw socket using the UDP protocol.
sfd=socket(PF_INET,SOCK_RAW,17);

perror("sfd");
if(sfd<0){
perror("socket() error\n");
exit(-1);
}
else{
printf("Socket was created\n");
}
//Binding our socket to our servers port.
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
while(x!=20){
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
