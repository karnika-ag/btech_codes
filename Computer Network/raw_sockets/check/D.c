/*** IPPROTO_RAW receiver ***/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SERVER_PORT 5000
int main(void)
{
	int rsfd[3];
	int rc;
	struct sockaddr_in sin,sin1,sin2,dest,saddr;
	
	sin.sin_family=AF_INET;
	sin.sin_port=0;
	inet_pton(AF_INET,"127.0.0.2",(struct in_addr *)&sin.sin_addr);
	perror("inet_1");
	
	sin2.sin_family=AF_INET;
	sin2.sin_port=0;
	inet_pton(AF_INET, "127.0.0.1", (struct in_addr *)&sin2.sin_addr.s_addr);
	perror("inet_2");
	
        dest.sin_family=AF_INET;
	dest.sin_port=0;
	inet_pton(AF_INET, "127.0.0.3", (struct in_addr *)&dest.sin_addr.s_addr);
	perror("inet_3");
	
	char packet[50];

	if ((rsfd[0] = socket(AF_INET, SOCK_RAW, 255)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}
	
	
	if ((rsfd[1] = socket(AF_INET, SOCK_RAW, 255)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}
	
	if(bind(rsfd[1],(struct sockaddr*)&sin,sizeof(sin))<0){
          perror("bind() error\n");
          exit(-1);
        }


       if ((rsfd[2] = socket(AF_INET, SOCK_RAW, 7)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}
	
	if(bind(rsfd[2],(struct sockaddr*)&sin2,sizeof(sin2))<0){
          perror("bind() error\n");
          exit(-1);
        }
        
	rc=connect(rsfd[2],(struct sockaddr*)&dest,sizeof(dest));
	perror("connect");
	
	
	memset(packet, 0, sizeof(packet));
	socklen_t *len = (socklen_t *)sizeof(saddr);
	int fromlen = sizeof(saddr);
        int i,j;
        
       	for(i=0;i<3;i++)    
	{
	        memset(packet, '\0', sizeof(packet));
	        
	        printf("\n1:\n");
		if (recvfrom(rsfd[1], (char *)&packet, sizeof(packet), 0,
			(struct sockaddr *)&saddr, &fromlen) < 0)
			perror("packet receive error:");

		j = sizeof(struct iphdr);	/* print the payload */
		printf("starting len %d\n",j);
		printf("1:%c\n",packet[20]);
		while (j < sizeof(packet)) {
			fprintf(stderr, "%c", packet[j]);
			j++;
		}
		printf("\n");
		
		
		memset(packet, '\0', sizeof(packet));
		
	        printf("2:\n");		
		
		if (recvfrom(rsfd[0], (char *)&packet, sizeof(packet), 0,
			(struct sockaddr *)&saddr, &fromlen) < 0)
			perror("packet receive error:");

		 j = sizeof(struct iphdr);	/* print the payload */
		 printf("starting len %d\n",j);
		 printf("2:%c\n",packet[20]);
		while (j < sizeof(packet)) {
			fprintf(stderr, "%c", packet[j]);
			j++;
		}
		printf("\n");
		
		memset(packet, 0, sizeof(packet));
		
		printf("\n3:\n");
		int n=read(rsfd[2],(char *)&packet,sizeof(packet));
		perror("read");
		printf("3:packet len: %d \n",n);
		j = sizeof(struct iphdr);	
		while (j < sizeof(packet)) {
			fprintf(stderr, "%c", packet[j]);
			j++;
		
	        }
	 }
	exit(EXIT_SUCCESS);
}


