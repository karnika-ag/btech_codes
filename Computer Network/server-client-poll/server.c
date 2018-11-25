#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include<sys/types.h>
#include <unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/time.h>

int csfd[5];
int scfd[5];
char myfifo1[12]="ctos_fifo1";
char myfifo2[12]="stoc_fifo1";


void fun1()
{
char str[500];
int i,j,k;
struct pollfd rpfds[4];
for(i=0;i<4;i++)
{
rpfds[i].fd=csfd[i+1];
rpfds[i].events=POLLIN;
//rpfds[i].revents=POLLIN;
}

while (1) {
	int n;
	if((n =poll(rpfds,4,500)) > 0)
	{

		for(i=0;i<4;i++)
		{
			printf("%d fd readable\n",n);
			if(rpfds[i].revents & POLLIN)
			{
				//printf("rpfds[i].fd= %d reading from %d\n",rpfds[i].fd,csfd[i+1]);
				int n = read(csfd[i+1],str,sizeof(str));
				str[n]='\0';
				printf("SERVER: %d bytes message from CLIENT %d : %s \n",n,i+1,str);
				for(j=0;j<4;j++)
				{
					if(j!=i)
					{
						write(scfd[j+1],str,sizeof(str));
					}    
				}  
			}
			rpfds[i].events=POLLIN;
			rpfds[i].revents=0;
		}
	}
   }
}


int main()
{

int i;
for(i=1;i<=4;i++)
   {  
   myfifo1[9]=(char)i+'0';
   myfifo1[10]='\0';
   myfifo2[9]=(char)i+'0';
   myfifo2[10]='\0';   
   mkfifo(myfifo1,0666);
   mkfifo(myfifo2,0666);
   csfd[i]= open(myfifo1, O_RDWR);
   scfd[i]= open(myfifo2, O_RDWR);
   printf("pipe%d created\n",i);
   }
   
   printf("SERVER STARTED\n");
   fun1();

   for(i=1;i<=4;i++)
   {
    close(csfd[i]);
    close(scfd[i]);
    myfifo1[9]=i+'0';
    myfifo1[10]='\0';    
    myfifo2[9]=i+'0';
    myfifo2[10]='\0';
    unlink(myfifo1);
    unlink(myfifo2);
   }

 
 
 return 0;
 }
 
 
