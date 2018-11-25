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
	int s;
	struct sockaddr_in saddr;
	char packet[50];

	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_IP)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}

	memset(packet, 0, sizeof(packet));
	socklen_t *len = (socklen_t *)sizeof(saddr);
	int fromlen = sizeof(saddr);
int i;
	for(i=0;i<3;i++) {
		if (recvfrom(s, (char *)&packet, sizeof(packet), 0,
			(struct sockaddr *)&saddr, &fromlen) < 0)
			perror("packet receive error:");

		int i = sizeof(struct iphdr);	/* print the payload */
		while (i < sizeof(packet)) {
			fprintf(stderr, "%c", packet[i]);
			i++;
		}
		printf("\n");
	}
	exit(EXIT_SUCCESS);
}



