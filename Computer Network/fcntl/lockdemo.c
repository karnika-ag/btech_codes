#include <stdio.h>
#include <stdlib.h>
#include <errno.h>     //itrishansh
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
                        /* l_type   l_whence  l_start  l_len  l_pid   */
        struct flock fl = {F_WRLCK, SEEK_SET,   0,      0,     0 };
        struct flock fl2= {F_RDLCK, SEEK_SET,   0,      0,     0 };
        int fd;
        fl.l_pid = getpid();
        if (argc > 1) 
            fl.l_type = F_RDLCK;

        if ((fd = open("lockdemo.c", O_RDWR)) == -1) 
        {
            perror("open");
            exit(1);
        }

        printf("Press <RETURN> to try to get lock: ");
        getchar();
        printf("Trying to get lock...");

        if (fcntl(fd, F_SETLKW, &fl) == -1) 
        {
            perror("fcntl");
            exit(1);
        }

        printf("got lock\n");
        
        


/*
        printf("Press <RETURN> to release lock: ");
        getchar();

        fl.l_type = F_UNLCK;  // set to unlock same region //

        if (fcntl(fd, F_SETLK, &fl) == -1) {
            perror("fcntl");
            exit(1);
        }

        printf("Unlocked.\n");
*/      
   	fl2.l_pid=getpid();
        printf("Press <RETURN> to check lock: ");
        getchar();

        if( fcntl(fd, F_GETLK, &fl2) < 0 ) {
            printf("Error occured!\n");
        }
        else{
            if(fl2.l_type == F_UNLCK) {
                printf("no lock\n");
            }
            else{
                printf("file is locked\n");
                printf("Errno: %d\n", errno);
            }
        }
        close(fd);

        return 0;
}
