#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/timex.h>
#include <time.h>
 
void randomGap () {
    struct timespec interval;
    interval.tv_sec = rand() % 3;
    interval.tv_nsec = (rand() % 100) * 10000000;
    nanosleep(&interval,NULL);
}
 
typedef struct {
    sem_t *data;
    sem_t *reader;
} SemPair;
 

void reader (SemPair *locks, int id) {
    int i;
    for (i = 0; i < 10; i++) {
        sem_wait(locks->reader);
        sem_wait(locks->data);
        fprintf(stderr,"\tReader %d - %d\n", id, i);
        sem_post(locks->data);
    }
    exit(0);
}
 

void writer (SemPair *locks, int id) {
    int i;
    for (i = 0; i < 10; i++) {
        sem_wait(locks->data);
        fprintf(stderr,"Writer %d - %d\n", id, i);
        sem_post(locks->data);
        sem_post(locks->reader);
        randomGap(); // simulate activity
    }
}
 
 
int main(int argc, const char *argv[]) {
    SemPair sem;
    sem_unlink("/test1");
    sem_unlink("/test2");
    sem.data = sem_open("/test1", O_CREAT, S_IRUSR | S_IWUSR, 0);
    sem.reader = sem_open("/test2", O_CREAT, S_IRUSR | S_IWUSR, 0);
    sem_post(sem.data); // initially open
 
    srand(time(NULL));
 
    pid_t pid = fork();
    if (!pid) reader(&sem, 1);
    else {
        pid = fork();
        if (!pid) writer(&sem, 1);
        else {
            pid = fork();
            if (!pid) reader(&sem, 2);
            else writer(&sem, 2);
            sleep(10);
            sem_close(sem.data);
            sem_close(sem.reader);
        }
    }
 
    return 0;
}
