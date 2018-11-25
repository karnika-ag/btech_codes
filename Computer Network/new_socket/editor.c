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

int main()
{
char buf[2000];
int n=0;
FILE *fd=popen("./1","r");
int fd1=fileno(fd);
while(1)
{
read(fd1,buf,sizeof(buf));
write(1,buf,strlen(buf));
} 

}
