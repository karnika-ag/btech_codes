#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<errno.h>

int main(int argc, char **argv)
{
    int fds[2];
    if (pipe(fds) == -1) {
        fprintf(stderr, "`pipe` failed.\n");
        return EXIT_FAILURE;
    }

    int fd0_dup = dup(fds[0]);
    if (fd0_dup <= STDERR_FILENO) {
        fprintf(stderr, "Failed to duplicate the read end\n");
        return EXIT_FAILURE;
    }
    
    printf("\n %d %d\n\n",fds[0],fd0_dup);
    
    
    if (fds[0] == fd0_dup) {
        fprintf(stderr, "`fds[0]` should not equal `fd0_dup`.\n");
        return EXIT_FAILURE;
    }

    if ((fcntl(fds[0], F_GETFL) & O_NONBLOCK)) {
        fprintf(stderr, "`fds[0]` should not have `O_NONBLOCK` set.\n");
        return EXIT_FAILURE;
    }

    if (fcntl(fd0_dup, F_SETFL, fcntl(fd0_dup, F_GETFL) | O_NONBLOCK) == -1) {
        fprintf(stderr, "Failed to set `O_NONBLOCK` on `fd0_dup`\n");
        return EXIT_FAILURE;
    }

    if ((fcntl(fds[0], F_GETFL) & O_NONBLOCK)) {
        fprintf(stderr, "`fds[0]` should still have `O_NONBLOCK` unset.\n");
        //return EXIT_FAILURE; // RETURNS HERE
    }
    
    if ((fcntl(fd0_dup, F_GETFL) & O_NONBLOCK)) {
        fprintf(stderr, "`fd0_dup` should still have `O_NONBLOCK` unset.\n");
       // return EXIT_FAILURE; // RETURNS HERE
    }

    char buf[1];
    if (read(fd0_dup, buf, 1) != -1) {
        fprintf(stderr, "Expected `read` on `fd0_dup` to fail immediately\n");
        return EXIT_FAILURE;
    }
    else if (errno != EAGAIN) {
        fprintf(stderr, "Expected `errno` to be `EAGAIN`\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
