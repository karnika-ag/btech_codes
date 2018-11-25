/*
File: Consumer.c

Unix concepts:  shared memory, fork(), exec(), semaphores,
  producer / consumer problem. 

Files:  ~renzo/cs322/producerConsumer/consumer.c
        ~renzo/cs322/producerConsumer/producer.c 

This is an example of using shared memory for IPC - interprocess communication.

A child process is forked and program producer (producer.c) is execed.  

Process producer generates messages (ints) and places them in the FIFO buffer 
implemented in shared memory.

The consumer (parent) reads the ints.

mike barnes
...

*/

# include <stdio.h>
# include <sys/types.h>
# include <sys/fcntl.h>
# include <sys/ipc.h>
# include <sys/sem.h>
# include <sys/shm.h>
/* my simple unix semaphor include */
# include "../myIncludes/semaphore.h"
# include "../myIncludes/sharedMemory.h"

int pid, segId;
struct FIFO * myShm;  /* FIFO defined in sharedMemory.h */

/*
The consuming actions of the parent are performed by the following
function.  The parent receives messages from shared memory FIFO buffer.
*/

void consumer()
  {
  int i;
  char mesg[80], tChar[10];
  printf("CONSUMER: ready to consume\n");
  for (i = 0; i < N_MSGS; i++) 
    {
    P(myShm->semaphore, FULL);
    P(myShm->semaphore, MUTEX);
    strcpy(mesg, "CONSUMER gets:  ");
    sprintf(tChar, "%d", myShm->store[myShm->front]);
    strcat(mesg, tChar);
    myShm->front = (myShm->front + 1) % BUF_SIZE;
    printf("CONSUMER %d:  %s\n", i, mesg);
    V(myShm->semaphore, MUTEX);
    V(myShm->semaphore, EMPTY);
    if(i > 5) sleep(1);  /* make consumer lag producer */
    }
 }
 

/*  
The main function gets and attaches shared memory,
disables and enables signals and forks the child process.
*/

main()
  {
  int segID;
  int semValues[3] = {1, BUF_SIZE, 0};   // mutex, empty, full sem values
  char segChar[40], nChar[40];

  /* create shared memory */
  if((segID = shmget(IPC_PRIVATE, sizeof(struct FIFO), SHM_R | SHM_W))
    == -1)  perror("Shmget failed"); 
  
  sprintf(segChar, "%d", segID);
  sprintf(nChar, "%d", N_MSGS);
  printf("segChar is %s nChar is %s\n", segChar, nChar);

  if((myShm =  (struct FIFO *)  shmat(segID, 0, SHM_R | SHM_W)) == 
     (struct FIFO *) -1) perror("Shmat failed");

  printf("myShm references address  %u segID is %d\n",  myShm, segID);
    
  /* initialize the buffer and semaphors */
  myShm->rear = myShm->front = 0;

  myShm->semaphore = semInit(3, semValues);

  printf("\nIPCS report after acquiring shared memory\n\n");
  system("ipcs");

   printf("CONSUMER: ready.  myShm = %u\n",  myShm);
   printf("FIFO: front = %d, rear = %d\n", myShm->front, myShm->rear);
   printf("Semaphors: mutex = %d, empty = %d, full = %d\n",
	  getSemValue(myShm->semaphore, MUTEX),
	  getSemValue(myShm->semaphore, EMPTY),
	  getSemValue(myShm->semaphore, FULL));

  switch (pid = fork()) 
    {
    case -1: /* error in fork, print mesg return */
             printf("Error in fork pid == -1 \n\n");
             exit(-1);
             break;
    case 0:  /* child branch, enable signals, exec */
             printf("MAIN: inside child after the fork\n");
             execl("producer", segChar, nChar, 0);
             perror("child fork failed"); exit(1);
    default: /* consumer branch */
             printf("MAIN: inside consumer after the fork\n");
             consumer(); 
    }
  wait(NULL); /* don't care how child terminates */

  /* release semaphors */

  semRel(myShm->semaphore);

  /*  detach shared memory and release it */
  shmdt((char *) myShm);
  if (shmctl(segID, IPC_RMID, 0)  == -1) perror("Shmctl failed ");

  system("ipcs");
  printf("MAIN terminates\n");
  }
