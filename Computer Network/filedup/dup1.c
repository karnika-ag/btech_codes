#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{

 int file;
 int current_out,tag1=0,in;  
         if(argc>=2)
          {

               current_out = dup(1);
               fflush(stdout);
               file = open(argv[argc-1], O_RDWR, 0777);
               if(dup2(file, 1) < 0) 
               {
                  fprintf(stderr, "couldn't redirect output\n");
                  exit(1);
               }
              tag1=1;
              
              char str[30];
              scanf("%[^\n]%*c",str);
              write(1,str,strlen(str));
              printf("%s\n",str);
              close(file);
              printf("hello\n------------------------------------\n");
              in=dup(0);
              
              fflush(stdin);
              file = open(argv[argc-1], O_RDWR, 0777);
              dup2(file,0);
              char st[50];
              read(0,st,sizeof(st));
              printf("%s\n",st);
               write(1,st,strlen(st));
          }  	
		
          
          if(tag1==1)
          {
               if(dup2(current_out,1) < 0) 
               {
                    fprintf(stderr, "couldn't reset output\n");
                     exit(1);
               }
                if(dup2(in,0) < 0) 
               {
                    fprintf(stderr, "couldn't reset output\n");
                     exit(1);
               }
          }  
}   
