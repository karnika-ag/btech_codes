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
int sfd,n;
char smsg[2000],rmsg[2000];
struct sockaddr_in server;
if(argc!=2)
{
printf("give ip of server\n");
exit(0);
}
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd<0)
{
printf("socket not created\n");
exit(0);
}

memset(&server, '0', sizeof(server));
server.sin_family=AF_INET;
server.sin_port=htons(8888);
int rc=inet_pton(AF_INET,argv[1],&server.sin_addr);
if(rc<=0)
{
printf("inet pton error\n");
exit(0);
}
rc=connect(sfd,(struct sockaddr_in *)&server,sizeof(server));
if(rc<0)
{
printf("connect error\n");
exit(0);
}
       if( (n = read(sfd, rmsg, sizeof(rmsg)-1)) > 0)
       {
        rmsg[n] = 0;
        write(1,rmsg,n);
       }
       if( (n = read(sfd, rmsg, sizeof(rmsg)-1)) > 0)
       {
        rmsg[n] = 0;
        write(1,rmsg,n);
       }
       
while(1)
{
   printf("\nenter msg u wanna to send\n");
   gets(smsg);
   //scanf("%s",smsg);
   write(sfd,smsg,strlen(smsg));
       if( (n = read(sfd, rmsg, sizeof(rmsg)-1)) > 0)
       {
        rmsg[n] = 0;
        write(1,rmsg,n);
       }
    printf("             \n");    
}

return 0;
}
