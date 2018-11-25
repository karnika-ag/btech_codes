#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void do_child(int data_pipe[]) {
    int c;
    int rc;
    close(data_pipe[1]);

    dup2(data_pipe[0], 0); /* This string provides the desired interface of the program */

    char* cmd[] = { "bash", (char *)0 };
    execvp("bash", cmd);

    while ((rc = read(data_pipe[0], &c, 1)) > 0) 
    {
        putchar(c);
    }
    exit(0);
}

void do_parent(int data_pipe[])
{
    int c;
    int rc;
    FILE *in;

    close(data_pipe[0]);

    while (1)
    {
        in = fopen("input.txt", "r");
        while ((c = fgetc(in)) > 0) 
        {
            rc = write(data_pipe[1], &c, 1);
            if (rc == -1) 
            {
                perror("Parent: write");
                close(data_pipe[1]);
                exit(1);
            }
        }
        fclose(in);
    }
    close(data_pipe[1]);
    exit(0);
}

int main(int argc, char* argv[])
{
    int data_pipe[2];
    int pid;
    int rc;

    umask(0);
    mknod("input.txt", S_IFIFO|0666, 0);

    rc = pipe(data_pipe);
    if (rc == -1) 
    {
        perror("pipe");
        exit(1);
    }
    pid = fork();
    switch (pid) 
    {
    case -1:
        perror("fork");
        exit(1);
    case 0:
        do_child(data_pipe);
    default:
        do_parent(data_pipe);
    }
    return 0;
}
