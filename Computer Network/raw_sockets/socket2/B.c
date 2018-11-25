/*** IPPROTO_RAW receiver ***/
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
	struct sockaddr_in saddr;
	char packet[50];

	if ((rsfd[0] = socket(AF_INET, SOCK_RAW, 7)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}
	
	if ((rsfd[1] = socket(AF_INET, SOCK_RAW, 255)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}

	memset(packet, 0, sizeof(packet));
	socklen_t *len = (socklen_t *)sizeof(saddr);
	int fromlen = sizeof(saddr);
        int i,j;
       	for(i=0;i<3;i++)    
	{
	        printf("\n1:\n");
		if (recvfrom(rsfd[0], (char *)&packet, sizeof(packet), 0,
			(struct sockaddr *)&saddr, &fromlen) < 0)
			perror("packet receive error:");

		j = sizeof(struct iphdr);	/* print the payload */
		while (j < sizeof(packet)) {
			fprintf(stderr, "%c", packet[j]);
			j++;
		}
		printf("\n");
	        printf("2:\n");		
		
		if (recvfrom(rsfd[1], (char *)&packet, sizeof(packet), 0,
			(struct sockaddr *)&saddr, &fromlen) < 0)
			perror("packet receive error:");

		 j = sizeof(struct iphdr);	/* print the payload */
		while (j < sizeof(packet)) {
			fprintf(stderr, "%c", packet[j]);
			j++;
		}
		printf("\n");
	}
	exit(EXIT_SUCCESS);
}



