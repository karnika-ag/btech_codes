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
FILE *logfile;
    /******Server Program*****/
struct sockaddr_in source,dest;
void fun(unsigned char* Buffer, int Size)
{
    printf("aya\n");
    unsigned short iphdrlen;
         
    struct iphdr *iph = (struct iphdr *)Buffer;
    iphdrlen =iph->ihl*4;
     
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;
     
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
     
    fprintf(logfile,"\n");
    fprintf(logfile,"IP Header\n");
    fprintf(logfile,"   |-IP Version        : %d\n",(unsigned int)iph->version);
    fprintf(logfile,"   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
    fprintf(logfile,"   |-Type Of Service   : %d\n",(unsigned int)iph->tos);
    fprintf(logfile,"   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
    fprintf(logfile,"   |-Identification    : %d\n",ntohs(iph->id));
    //fprintf(logfile,"   |-Reserved ZERO Field   : %d\n",(unsigned int)iphdr->ip_reserved_zero);
    //fprintf(logfile,"   |-Dont Fragment Field   : %d\n",(unsigned int)iphdr->ip_dont_fragment);
    //fprintf(logfile,"   |-More Fragment Field   : %d\n",(unsigned int)iphdr->ip_more_fragment);
    fprintf(logfile,"   |-TTL      : %d\n",(unsigned int)iph->ttl);
    fprintf(logfile,"   |-Protocol : %d\n",(unsigned int)iph->protocol);
    fprintf(logfile,"   |-Checksum : %d\n",ntohs(iph->check));
    printf("   |-Source IP        : %s\n",inet_ntoa(source.sin_addr));
    fprintf(logfile,"   |-Destination IP   : %s\n",inet_ntoa(dest.sin_addr));
}
int main(int argc, char* argv[])
{
    logfile=fopen("log.txt","w");
   
    int sfd;
    char buffer[PCKT_LEN];
    char hbuf[NI_MAXHOST],sbuf[NI_MAXSERV];

    struct sockaddr_in sin, din;
    struct sockaddr_storage inc_packet;
    socklen_t inc_packetl;
    int bytes_read;
    memset(buffer,0,PCKT_LEN);
         
    //Address Family
    sin.sin_family=AF_INET;
    din.sin_family=AF_INET;
    //Port Numbers
    sin.sin_port=htons(SERVER_PORT);
    //din.sin_port=client port argument.
    //IP Addresses

//172.30.124.236
    if(inet_pton(AF_INET,"172.30.128.144",&sin.sin_addr)<0){
    perror("inet_pton() error\n");
    }
    else{
    printf("inet_pton() doing ok\n");
    }
    perror("inet");

    sfd=socket(PF_INET,SOCK_RAW,17);

    perror("sfd");
    if(sfd<0){
    perror("socket() error\n");
    exit(-1);
    }
    else{
    printf("Socket was created\n");
    }

    bind(sfd,(struct sockaddr*)&sin,sizeof(sin));
    perror("bind() error\n");
    int x =0;

    while(x!=20)
    {
        printf("Waiting after bind\n");
        bytes_read=recvfrom(sfd,buffer,PCKT_LEN,0,(struct sockaddr*)&inc_packet,&inc_packetl); 
        perror("read");
        fun(buffer,bytes_read);
       
    }
    
    close(sfd);
    return 0;
}
