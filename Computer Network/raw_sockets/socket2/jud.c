#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int store[16]={2,7,11,5,3,10,8,13,15,9,4,14,1,12,6,16};

int main()
{
        printf("judge started\n");
        
	int rsfd[2];
	struct sockaddr_in src,dest;
	char packet[50];
	
	struct iphdr *ip = (struct iphdr *)packet;  

	if ((rsfd[0] = socket(AF_INET, SOCK_RAW, 7)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}
	perror("socket");
	src.sin_family = AF_INET;
	src.sin_port =0;
	inet_pton(AF_INET,"127.0.0.1", (struct in_addr *)&src.sin_addr.s_addr);

	dest.sin_family = AF_INET;
	dest.sin_port =0;
	memset(dest.sin_zero, 0, sizeof(dest.sin_zero));
	
	ip->ihl = 5;
	ip->version = 4;
	ip->tos = 0;
	ip->tot_len = htons(40);	/* 16 byte value */
	ip->frag_off = 0;		/* no fragment */
	ip->ttl = 64;			/* default value */
	ip->protocol =7;	/* protocol at L4 */
	ip->check = 0;			/* not needed in iphdr */
	ip->saddr = src.sin_addr.s_addr;
//	ip->daddr = dest.sin_addr.s_addr;

        int i=0;
        char ch;int j=8,k;
        char *data=(char *)(packet+sizeof(struct iphdr));
        printf("NOW GENERATE RANDOM NUMBERS\n");
	for(i=0;i<16;i++) {
	      
	      
	      sleep(1);
	      int num=store[i];
              sprintf(data,"%d",num);
              printf("%s sent \n",data);
	      //memset(data,'a'+i,sizeof(data));
	      inet_pton(AF_INET, "127.0.0.2", (struct in_addr *)&dest.sin_addr.s_addr);
              ip->daddr=dest.sin_addr.s_addr;
	      ip->protocol=7;
             
             
              	     
              if (sendto(rsfd[0], (char *)packet, sizeof(packet), 0, 
			(struct sockaddr *)&dest, (socklen_t)sizeof(dest)) < 0)
			perror("packet send error:");
			printf("SERVER: CLIENT1:msg snt\n");
			
			
             
              ip->protocol=7;
              inet_pton(AF_INET, "127.0.0.3", (struct in_addr *)&dest.sin_addr.s_addr);
              ip->daddr=dest.sin_addr.s_addr;
              
              if (sendto(rsfd[0], (char *)packet, sizeof(packet), 0, 
			(struct sockaddr *)&dest, (socklen_t)sizeof(dest)) < 0)
			perror("packet send error:");
			printf("SERVER: CLIENT2:msg snt\n");		
			
			
	}
	exit(EXIT_SUCCESS);
}
