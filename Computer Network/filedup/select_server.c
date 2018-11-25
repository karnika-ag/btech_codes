#include<sys/select.h>
#include<sys/stat.h>
#include<stdio.h>
int csfd[5];
int scfd[5];
char myfifo1[12]="ctos_fifo1";
char myfifo2[12]="stoc_fifo1";

void fun1()
{

char str[500];
int i,j,k,n=0;
fd_set rfds;
struct timeval tv;
int retval;
for(i=1;i<=2;i++)
{
FD_SET(csfd[i],&rfds);
n=max(n,csfd[i]);
}
while(1)
{
retval = select (n + 1, &rd, NULL, NULL, NULL);
if (r < 0) 
   {
            perror ("select()");
            exit (1);
   }
for(i=1;i<=2;i++)
{
  if(FD_ISSET(csfd[i],&rfds)
  {
      int n = read(csfd[i],str,sizeof(str));
				for(j=1;j<=2;j++)
				{
					if(j!=i)
					{
						write(scfd[j],str,sizeof(str));
					}    
				}   
  }
}
}

}


int main()
{

int i;
for(i=1;i<=2;i++)
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

   for(i=1;i<=2;i++)
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
 
 
