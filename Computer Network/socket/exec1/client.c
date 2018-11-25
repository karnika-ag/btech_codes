#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    char recvBuff[1024],sendbuff[1024];
    struct sockaddr_in serv_addr; 

    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888); 

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
    
    
struct sockaddr_in host;
socklen_t addlen;
addlen = sizeof(host);
getsockname(sockfd, (struct sockaddr*)&host,&addlen);
//printf("local address: %s\n",inet_ntoa(host.sin_addr));
//printf("local port: %d\n", (int) ntohs(host.sin_port));
    char buffer[100];
    const char* p = inet_ntop(AF_INET, &host.sin_addr, buffer, 100);
    printf("local port: %d\n", (int) ntohs(host.sin_port));        
    if(p != NULL)
    {
        printf("Local ip is : %s \n" , buffer);
    }

       if( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
       {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
       }
    
    while (1)
    {
    
       if( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
       {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
       }
       
       
       //fgets(sendbuff,1000);
       scanf("%s",sendbuff);
       write(sockfd,sendbuff,strlen(sendbuff));
       
    } 

    if(n < 0)
    {
        printf("\n Read error \n");
    } 

    return 0;
}
