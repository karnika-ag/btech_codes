#include<stdio.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<errno.h>

int main(int argc, char* argv[])
{
    int fd;
    char *filename = "f1.txt";
    char data[1];
    int curval;                         //current flag value
    int newval;                         //new flag value



fd = open(filename, O_RDONLY);

while(read(fd, data, 1)>0)
{
    write(STDOUT_FILENO, data, 1);
}

lseek(fd, 0, SEEK_SET);

if((curval = fcntl(fd, F_GETFL, 0))<0)              
{
    perror("file flag get failed");
}



printf("%d\n", curval); 

newval = curval | O_APPEND; 

printf("%d\n", newval);


    if(fcntl(fd, F_SETFL, newval)<0)
{
    perror("file flag set failed");
}

if(write(fd, argv[1], strlen(argv[1]))<0)   //appending more data to the file
{
    perror("write failed");
    }

lseek(fd, 0, SEEK_SET);

while(read(fd, data, 1)>0)
{
    write(STDOUT_FILENO, data, 1);
}
close (fd);
return 0;
}
