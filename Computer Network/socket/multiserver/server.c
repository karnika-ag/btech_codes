#include<stdio.h>
#include<string.h>  
#include<stdlib.h>  
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>   
#include<pthread.h>
int main()
{
int sfd,nsfd,size,cur_in;
char *buf;
cur_in=dup(0);
struct sockaddr_in server,client;
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{
printf("could not create socket\n");
exit(0);
}
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=htons(8888);
if(bind(sfd,(struct sockaddr_in *)&server,sizeof(server))<0)
{
printf("bind failed\n");
exit(0);
}
listen(sfd,3);
printf("SOCKET CREATED-waiting for connections\n");
while(nsfd=accept(sfd,(struct sockaddr_in *)&client,&size))
{
printf("connection accepted\n");
buf="request accepted..assigning to someone else\n";
write(nsfd,buf,strlen(buf));
int pid=fork();
if(pid==0)
{
dup2(nsfd,0);
execv("abc",0);
}
printf("handler assigned\n");
}
}

