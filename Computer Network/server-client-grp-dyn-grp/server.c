#include<sys/select.h>
#include<signal.h>
#include<sys/stat.h>
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/poll.h>
#include<sys/time.h>
#define MAX 9
int shmid,shmid1;
int *no;
int *grp,mgp;
int prc=0,gp=0;
int csfd[MAX][MAX];
int scfd[MAX][MAX];
char myfifo1[12]="ctos_fifo1";
char myfifo2[12]="stoc_fifo1";
int max(int a,int b)
{
if(a>b)return a;
return b;
}
void fun2()
{
   printf("entered....\n");
   gp=grp[0];
   mgp=max(mgp,gp);
   prc=no[gp];
   printf("%d %d\n",gp,prc);
   myfifo1[9]=(char)gp+'0';
   myfifo1[10]=(char)prc+'0';
   myfifo1[11]='\0';
   myfifo2[9]=(char)gp+'0';
   myfifo2[10]=(char)prc+'0';
   myfifo2[11]='\0'; 
   printf("%s\n%s\n",myfifo1,myfifo2);
   csfd[gp][prc]= open(myfifo1, O_RDWR);
   scfd[gp][prc]= open(myfifo2, O_RDWR);
   printf("pipe %d%d created\n",gp,prc);
   signal(SIGUSR1,fun2);
}

void fun1()
{
char str[500];
int i,j,k;
printf("cant reach there\n");
struct pollfd rpfds[MAX*MAX];
printf("done till here\n");
while (1) {
int sum=0,id;
j=0;
for(i=0;i<mgp;i++)
{
prc=no[i+1];
for(j=0;j<prc;j++)
{
rpfds[sum+j].fd=csfd[i+1][j+1];
rpfds[sum+j].events=POLLIN;
}
sum+=prc;
}

	int n;
	if((n =poll(rpfds,sum,500)) > 0)
	{
                sum=0;
		for(i=0;i<mgp;i++)
		{
		  prc=no[i+1];
		   for(j=0;j<prc;j++)
		   {
			if(rpfds[sum+j].revents & POLLIN)
			{
				int n = read(csfd[i+1][j+1],str,sizeof(str));
				str[n]='\0';
				printf("SERVER: %d bytes message from CLIENT %d%d : %s \n",n,i+1,j+1,str);
				for(k=0;k<prc;k++)
				{
					if(j!=k)
					{
						write(scfd[i+1][k+1],str,sizeof(str));
					}    
				}  
			}
			rpfds[sum+j].events=POLLIN;
			rpfds[sum+j].revents=0;
		  }
		  sum+=prc;
	        }
	}
   }
}


int main()
{
signal(SIGUSR1,fun2);
int i,j;
if((shmid=shmget(2276,9*sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget1 error\n");
exit(0);
}
no=(int *)shmat(shmid,NULL,0);
no[1]=0;
no[2]=0;
no[0]=getpid();
if((shmid1=shmget(2274,sizeof(int),IPC_CREAT|0666))==-1)
{
perror("shmget2 error\n");
exit(0);
}
grp=(int *)shmat(shmid1,NULL,0);
grp[0]=0;
mgp=0;
for(j=1;j<=mgp;j++)
{
   myfifo1[9]=(char)j+'0';
   myfifo2[9]=(char)j+'0';
   prc=no[j];
   for(i=1;i<=prc;i++)
   {  
   myfifo1[10]=(char)i+'0';
   myfifo1[11]='\0';
   myfifo2[10]=(char)i+'0';
   myfifo2[11]='\0';   
   mkfifo(myfifo1,0666);
   mkfifo(myfifo2,0666);
   csfd[j][i]= open(myfifo1, O_RDWR);
   scfd[j][i]= open(myfifo2, O_RDWR);
   printf("pipe%d created\n",i);
   }
}   
   printf("SERVER STARTED\n");
   fun1();
for(j=1;j<=mgp;j++)
{
prc=no[j];
 myfifo1[9]=(char)j+'0';
 myfifo2[9]=(char)j+'0';
   for(i=1;i<=prc;i++)
   {
    close(csfd[j][i]);
    close(scfd[j][i]);
    myfifo1[10]=i+'0';
    myfifo1[11]='\0';    
    myfifo2[10]=i+'0';
    myfifo2[11]='\0';
    unlink(myfifo1);
    unlink(myfifo2);
   }
} 
return 0;
}
 
 
