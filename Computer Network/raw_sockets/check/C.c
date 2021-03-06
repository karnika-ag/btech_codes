#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define DEST "127.0.0.1"

int main(void)
{

	int rsfd[2];
	struct sockaddr_in daddr,src;
	char packet[50];
	struct iphdr *ip = (struct iphdr *)packet;  

	if ((rsfd[0] = socket(AF_INET, SOCK_RAW, 254)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}
	
	if ((rsfd[1] = socket(AF_INET, SOCK_RAW, 255)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}

	daddr.sin_family = AF_INET;
	daddr.sin_port =0; /* not needed in SOCK_RAW */
	inet_pton(AF_INET, DEST, (struct in_addr *)&daddr.sin_addr.s_addr);
	memset(daddr.sin_zero, 0, sizeof(daddr.sin_zero));
	memset(packet, 'E', sizeof(packet));   /* payload will be all As */
	inet_pton(AF_INET,"127.0.0.1", (struct in_addr *)&src.sin_addr.s_addr);

	ip->ihl = 5;
	ip->version = 4;
	ip->tos = 0;
	ip->tot_len = htons(40);	/* 16 byte value */
	ip->frag_off = 0;		/* no fragment */
	ip->ttl = 64;			/* default value */
	ip->protocol =7;	/* protocol at L4 */
	ip->check = 0;			/* not needed in iphdr */
	ip->saddr = daddr.sin_addr.s_addr;
	ip->daddr = daddr.sin_addr.s_addr;

         int i=0;
         char ch;
         int j=0,k;
         char *data=(char *)(packet+sizeof(struct iphdr));
         for(i=0;i<3;i++) {
		sleep(1);
	      ch=j+'a';
	      j++;
	      for(k=0;k<30;k++)
	      data[k]=ch;
	     
	      inet_pton(AF_INET, "127.0.0.2", (struct in_addr *)&daddr.sin_addr.s_addr);
              ip->daddr= daddr.sin_addr.s_addr;
	      ip->protocol=255;
	      printf("1:%c\n",packet[20]);
	  	if (sendto(rsfd[1], (char *)packet, sizeof(packet), 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) < 0)
		perror("packet1 send error:");
		printf("SOCKET1:msg snt\n");
               printf("1:%c\n",packet[20]);
		
		
//		ch=j+'a';
//		j++;	
//	      for(k=0;k<30;k++)
//	      data[k]=ch;
	      //packet[49]='\0';
	     
	      scanf("%s",data);
	      memset(packet, '\0', sizeof(packet));
	      	struct iphdr *ip = (struct iphdr *)packet;  
	      	ip->ihl = 5;
	ip->version = 4;
	ip->tos = 0;
	ip->tot_len = htons(40);	/* 16 byte value */
	ip->frag_off = 0;		/* no fragment */
	ip->ttl = 64;			/* default value */
	//ip->protocol =7;	/* protocol at L4 */
	ip->check = 0;			/* not needed in iphdr */

	      
              ip->protocol=255;
              inet_pton(AF_INET, "127.0.0.1", (struct in_addr *)&daddr.sin_addr.s_addr);
              ip->daddr= daddr.sin_addr.s_addr;
              ip->saddr = src.sin_addr.s_addr;
              printf("2:%c\n",packet[20]);
              	if (sendto(rsfd[0], (char *)packet, sizeof(packet), 0, 
			(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) < 0)
			perror("packet2 send error:");
			printf("SOCKET2:msg snt\n");		
			
	          printf("2:%c\n",packet[20]);		
	}
	exit(EXIT_SUCCESS);
}
