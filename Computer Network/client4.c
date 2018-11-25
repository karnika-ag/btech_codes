#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
   int csfd;
   char *myfifo1 = "ctos_fifo4";
   int scfd;
   char *myfifo2 = "stoc_fifo4";
   char str[BUFSIZ];
   csfd = open(myfifo1, O_WRONLY);
   scfd = open(myfifo2, O_RDONLY);
   while(1)
   {
 
   printf("CLIENT 4: enter msg \n");
   scanf("%s", str);
   write(csfd, str, sizeof(str));
   perror("Write:");
   read(scfd,str,sizeof(str));
   perror("Read:"); 
   printf("CLIENT 4: received from server:- %s\n",str);
   
   }

   close(csfd);
   close(scfd);


   return 0;
}
