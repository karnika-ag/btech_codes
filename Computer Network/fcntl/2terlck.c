#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {

struct flock fl,fl2;
int fd;

fl.l_type   = F_WRLCK;  /* read/write lock */
fl.l_whence = SEEK_SET; /* beginning of file */
fl.l_start  = 0;        /* offset from l_whence */
fl.l_len    = 0;        /* length, 0 = to EOF */
fl.l_pid    = getpid(); /* PID */

fd = open("f1.txt", O_RDWR | O_EXCL | O_CREAT);
fcntl(fd, F_GETLK, &fl2);
if(fl2.l_type!=F_UNLCK)
{
printf("locked");
}
else
{
fcntl(fd, F_SETLKW, &fl); /* set lock */
write(fd,"hello",5);
usleep(10000000);
}
printf("\n release lock \n");

fl.l_type   = F_UNLCK;
fcntl(fd, F_GETLK, &fl); /* unset lock */

while(1);

}
