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
char buf[2000]="Reader 2: chat1\n";
int n=0;
while(1)
{
n++;
n=n%9;
buf[14]=n+'0';
buf[17]='\0';
write(1,buf,strlen(buf));
sleep(10);
} 

}
