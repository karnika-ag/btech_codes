#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{

	int rsfd[2];
	struct sockaddr_in daddr,sin;
	char packet[50];
	
	struct iphdr *ip = (struct iphdr *)packet;  

	if ((rsfd[0] = socket(AF_INET, SOCK_RAW, 7)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}
	
	
	sin.sin_family = AF_INET;
	sin.sin_port = 0;
	inet_pton(AF_INET, "127.0.0.3", (struct in_addr *)&sin.sin_addr.s_addr);
	
		
	daddr.sin_family=AF_INET;
	daddr.sin_port=0;
	inet_pton(AF_INET, "127.0.0.1", (struct in_addr *)&daddr.sin_addr.s_addr);
	
	
	if(bind(rsfd[0],(struct sockaddr*)&sin,sizeof(sin))<0){
          perror("bind() error\n");
          exit(-1);
        }
        
	memset(daddr.sin_zero, 0, sizeof(daddr.sin_zero));
	memset(packet, 'L', sizeof(packet));   /* payload will be all As */
	
	ip->ihl = 5;
	ip->version = 4;
	ip->tos = 0;
	ip->tot_len = htons(40);	/* 16 byte value */
	ip->frag_off = 0;		/* no fragment */
	ip->ttl = 64;			/* default value */
	ip->protocol =7;	/* protocol at L4 */
	ip->check = 0;			/* not needed in iphdr */
	ip->saddr = sin.sin_addr.s_addr;
	ip->daddr = daddr.sin_addr.s_addr;

         
	int rc=connect(rsfd[0],(struct sockaddr*)&daddr,sizeof(daddr));
	perror("connect");
        
        //sleep(20);
         int i=0;
         char ch;int j=20,k;
         char *data=(char *)(packet+sizeof(struct iphdr));
	 for(i=0;i<3;i++) {
		sleep(1);
	      ip->protocol=7;
	      ch=j+'a';
	      j++;
	      for(k=0;k<30;k++)
	      data[k]=ch;
		
		/*if (sendto(rsfd[0], (char *)packet, sizeof(packet), 0, 
			(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) < 0)
			perror("packet send error:");
			printf("SOCKET1:msg snt\n");*/
			
		write(rsfd[0],(char *)packet,sizeof(packet));
		perror("write");	
		printf("E:msg snt");
			
			
			
			
	}
	exit(EXIT_SUCCESS);
}
