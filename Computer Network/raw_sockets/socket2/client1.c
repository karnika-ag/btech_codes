#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <string.h>
int pgm,rc,sfd;
void housy(void *arg)
{
int store[20];
int thrno=*(int *)arg;
char buffer[30];
printf("THREAD %d CREATED\n",thrno);
int i=0;
for(i=0;i<4;i++)
{
int n=read(sfd,buffer,sizeof(buffer));
perror("read");
buffer[n]='\0';
printf("\nlen %d : %s\n",n,buffer);
store[i]=atoi(buffer);
printf("Client%d : thrd %d received %d\n",pgm,thrno,store[i]);
sleep(1);
}

        int lcount=4;
        int rsfd,j;
        char packet[50];
        struct sockaddr_in dest,src;
        int fromlen = sizeof(dest);
        char path[10]="127.0.0.1";
        path[8]=pgm+1+'0';
        path[9]='\0';
        printf("addr CLIENT %s \n",path);
        
	src.sin_family = AF_INET;
	src.sin_port =0;
	inet_pton(AF_INET,path, (struct in_addr *)&src.sin_addr.s_addr);

	if ((rsfd = socket(AF_INET, SOCK_RAW, 7)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}
	perror("socket");
	if(bind(rsfd,(struct sockaddr*)&src,sizeof(src))<0){
          perror("bind() error\n");
          exit(-1);
        }
        perror("bind");
        char *ffd;
        for(i=0;i<16;i++)    
	{
	memset(packet, '\0', sizeof(packet)); 
	        
		if (recvfrom(rsfd, (char *)&packet, sizeof(packet), 0,
			(struct sockaddr *)&dest, &fromlen) < 0)
			perror("packet receive error:");

		j = sizeof(struct iphdr);	/* print the payload */
		ffd=(char *)(packet+j);
		printf("printing ffd: %s\n",ffd);
		while (packet[j]!='\0') {
			fprintf(stderr, "%c", packet[j]);
			j++;
		}
		int ncom=atoi(ffd);
		printf("printing ncom: %d \n",ncom);
	       int u;
	       for(u=0;u<4;u++)
	       {
	       if(store[u]==ncom)
	       {
	       store[u]=-1;
	       lcount--;
	       break;
	       }
	       }   
	       if(lcount==0)
	       {
	       printf("CLIENT %d COUPON NO %d WON\n",pgm,thrno);
	       }
		printf("\n");
		
	  
         }    
        
}
int main(int argc,char *argv[])
{
struct sockaddr_in src,dest;
pgm=atoi(argv[1]);
int i;
sfd=socket(AF_INET,SOCK_STREAM,0);
perror("sfd");
dest.sin_family=AF_INET;
dest.sin_port=htons(atoi(argv[2]));
inet_pton(AF_INET,"127.0.0.1",(struct in_addr *)&dest.sin_addr);
rc=connect(sfd,(struct sockaddr *)&dest,sizeof(struct sockaddr_in));
perror("connect");
pthread_t thr[2];
int arr[5];
for(i=0;i<2;i++)
{
arr[i]=i+1;
rc=pthread_create(&thr[i],NULL,(void *)&housy,(void *)&arr[i]);
perror("thread create");
}
for(i=0;i<2;i++)
{
pthread_join(thr[i],NULL);
}
}
