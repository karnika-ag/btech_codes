#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
int main()
{
int sfd=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in host,server;
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=htons(8476);
int rc=bind(sfd,(struct sockaddr *)&server,sizeof(server));
socklen_t addlen;
addlen = sizeof(host);
getsockname(sfd, (struct sockaddr*)&host,&addlen);
printf("local address: %s\n",inet_ntoa(host.sin_addr));
printf("local port: %d\n", (int) ntohs(host.sin_port));
}
