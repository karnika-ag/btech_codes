#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<errno.h>
#include<string.h>
struct flock lock;
int main()
{
 char buff[200]="didididid kaha gaye the";
int fd,flags;
            FILE *file = fopen("f1.txt", "w+");

            if (file == NULL)
                printf("File cannot be opened");


            fd = fileno(file);

            printf("\nThis is the file descriptor : %d\n", fd);

            if(file == NULL)
            printf("File cannot be opened");

            printf("\nLocking!!!!");

            //initliazing the flock structure
            if(memset(&lock, 0, sizeof(lock))== NULL) //setting 0 as a value
            {
                perror("Memset Error : Should return a pointer to memory area");
            }
            lock.l_type = F_WRLCK;  //F_RDLCK, F_WRLCK, F_UNLCK
            lock.l_whence = SEEK_SET;  //SEEK_SET, SEEK_CUR, SEEK_END
            lock.l_start = 0;   //offset from l_whence
            lock.l_len = 0;   //length, 0 = to EOF
            lock.l_pid = getpid(); //the processes's PID


            //placing a write lock on the file
            if((flags = fcntl(fd, F_SETLKW, &lock)) < 0)
            {
                perror("fnctl: ");
            }
            printf("\nFlag : %d \n", flags);

            printf("\nLocked-------");

            if(fwrite(buff + 1, 1, strlen(buff) - 1, file) == 0)
            {
                perror("Error or EOF reached while fwrite");
            }

            //lock_realease(&l);
            printf("\nHit enter to unlock the file !");
            getchar();

            printf("\nFinished writing so we can unlock file !");

            //Releasing lock
            lock.l_type = F_UNLCK;  //unlocks the region of the file
            if((flags = fcntl(fd, F_SETLKW,&lock)) < 0)
            {
                perror("fnctl: ");
            }

            printf("\nFlag : %d \n", flags);

            fclose(file); //some say it is better to close the file and let it implicitly be unlocked when it is actually closed.
                          //Otherwise the lock can be release while unbuffered data is still unwritten
            printf("\nFile unlocked!");

            }
