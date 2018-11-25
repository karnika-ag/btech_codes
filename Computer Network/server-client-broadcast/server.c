#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include<sys/types.h>
#include <unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include <string.h>
int csfd[5];
int scfd[5];
char myfifo1[12]="ctos_fifo1";
char myfifo2[12]="stoc_fifo1";


void fun(void *arg)
{
int id=*(int *)arg;
char buf[BUFSIZ];
while(1)
{
int rc;
//     while((rc=read(csfd[id],buf,BUFSIZ))<=0) ;
     read(csfd[id],buf,BUFSIZ);
      if (strcmp("exit",buf)==0)
      {
         printf("Server client %d is closed\n",id);
         break;
      }

      else if (strcmp("",buf)!=0)
      {
      
         printf("SERVER :- Received from client %d : %s\n",id,buf);
         int i;
         for(i=1;i<=4 ;i++)
         {
         if(i!=id)
         {
         write(scfd[i],buf,BUFSIZ);
         printf("SERVER :- Sending to client %d \n",i);
         }
         }
      }

      memset(buf, 0, sizeof(buf));
     
}
exit(0);
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
   printf("%s \n %s \n",myfifo1,myfifo2);
  
   mkfifo(myfifo1,0666);
   mkfifo(myfifo2,0666);
  
   printf("hoya\n");
  
   csfd[i]= open(myfifo1, O_RDONLY);
   printf("%d\n",csfd[i]);
 
   scfd[i]= open(myfifo2, O_WRONLY);
   printf("%d\n",scfd[i]);
  
   printf("done\n");
   }
   
   printf("Server started\n");
   pthread_t thr[5];
   int rc;
   int arr[5];
   for(i=1;i<=4;i++)
   {
     arr[i]=i;
     if((rc=pthread_create(&thr[i],NULL,(void *)&fun,(void *)&arr[i]))==-1)
     {
     perror("pthread error \n");
     exit(0);
     }
   }
   
	   
	for(i=1;i<=4;i++)
	{
	pthread_join(thr[i],NULL);
	}

   
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
