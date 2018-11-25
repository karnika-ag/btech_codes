#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
        int f = open("test.txt", O_CREAT|O_RDWR, 0666);
        int out=dup(1);
        //fflush(stdout);
 
        if(f==-1)
                perror("open()");
 
        dup2(f, 1);
        close(f);
        
        write(1,"hello",5);
        fprintf(1,"Hello world\n");
 
        //printf("%d\n",close(f));
        //close(1);
        dup2(out,1);
        printf("test\n");
 
        return 0;
}
