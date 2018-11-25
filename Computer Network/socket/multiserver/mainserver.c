#include<stdio.h>
#include<string.h>  
#include<stdlib.h>  
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>   
int main()
{
int sfd,nsfd;
struct sockaddr_in server;
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{
printf("could not create\n");
exit(0);
}
server.sin_family=AF_INET;
server.sin_addr.s.addr=INADDR_ANY;
server.sin_port=htons( 8888 );
    if( bind(sfd,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    puts("bind done");
    listen(socket_desc , 3);
    
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while( (nsfd = accept(sfd, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
        message = "Hello Client , I have received your connection. And now I will assign a handler for you\n";
        write(new_socket , message , strlen(message));
         
        new_sock = malloc(1);
        *new_sock = new_socket;
         dup2(new_socket,0);
        int pid=fork();
	
	if(pid==0)
	{
	execv("abc",0);
	}
	else if(pid>0)
	{
	}
	else
	{
	printf("error in forking\n");
	}
        puts("Handler assigned");
    }
     
    if (new_socket<0)
    {
        perror("accept failed");
        return 1;
    }
     
    return 0;
}
