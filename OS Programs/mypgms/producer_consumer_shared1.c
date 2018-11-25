// prodcons.c
//
// code using signal.h, sem.h and shm.h
//
// created:  24sep2002 by Sean Yang (web.puchu@puchu.net)
// modified: 25sep2002
//
// remember:
// when screwing around with shared memory and semaphores, these commands
// are your friends: ipcs and ipcrm
// 
// date      description
// --------  ---------------------
// 25sep2002 added shm and signal stuff
// 24sep2002 initial version, demo binary and counting semaphores

#include <stdio.h>
#include <stdlib.h> // required for exit()
#include <unistd.h> // required for fork()
#include <signal.h>
#include <errno.h> // so I can check errno, but I don't :)
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define SEM_ACC_MODE 0600 // read is 4 write is 2 {0, user, group, other} 

#define PRODUCE_MAX 38 // maximum items to produce for consuming
#define SHM_KEY 1977 

// delay in seconds to make interesting
#define PROD_DELAY 1
#define CONS_DELAY 2

/* weird, semun doesn't seem to be defined?  should be part of sem.h */
typedef union mysemun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *__buf;
} semun;

//////////////////////////////////////////////////
// FUNCTION PROTOTYPES
//////////////////////////////////////////////////

void consumer(int child, int critical_region_id, int counting_sem_id,
	char *shm_ptr);
void producer(int pid, int critical_region_id, int counting_sem_id,
	char *shm_ptr);
void signal_term(int sig);

/* functions for semaphore operations */
void down(int semid);
void up(int semid);

//////////////////////////////////////////////////
// MAIN
//////////////////////////////////////////////////

int main(void)
{
  // structure used to initialize the values of my semaphores
  semun init_value;

  // remember PID so that we can kill them later 
  pid_t child1, child2, child3, parent = getpid();

  // gets semaphore id, must remove them when everything is consumed 
  int critical_region_id = semget(IPC_PRIVATE, 1, SEM_ACC_MODE);
  int counting_sem_id = semget(IPC_PRIVATE, 1, SEM_ACC_MODE);

  // allocate shared memory
  int shared_mem_id = shmget(SHM_KEY, sizeof(char) * PRODUCE_MAX, 
    IPC_CREAT | SEM_ACC_MODE);
  char *shm_ptr = (char *) shmat(shared_mem_id, (char *)NULL, 0);

  // uninteresting variable
  int prods;

  // stuff for debugging, use these numbers to reclaim resources
  printf("shm id is: %d\n", shared_mem_id);
  printf("sem id is: %d\n", critical_region_id);
  printf("sem id is: %d\n", counting_sem_id);

  // install interrupt handler
  signal(SIGTERM, signal_term);

  // sets initial values for semaphore
  init_value.val = 1;
  if(semctl(critical_region_id, 0, SETVAL, init_value) == -1)
    printf("critical_region_id SETVAL error\n");
  init_value.val = 0;
  if(semctl(counting_sem_id, 0, SETVAL, init_value) == -1)
    printf("critical_region_id SETVAL error\n");

  // attach to shared memory

  if((child1 = fork()) < 0) printf("fork error\n");
  if(child1) {
    // children will be consumer
    if((child2 = fork()) < 0) printf("fork error\n");
    if(child2) {
      if((child3 = fork()) < 0) printf("fork error\n");
      if(child3) consumer(child3, critical_region_id, counting_sem_id, shm_ptr); 
      else consumer(child2, critical_region_id, counting_sem_id, shm_ptr);
    }
    else consumer(child1, critical_region_id, counting_sem_id, shm_ptr);
  }
  else {
    // parent will be producer
    producer(parent, critical_region_id, counting_sem_id, shm_ptr);

    // find number of products available for consumption, should be zero when
    // we clean up
    prods = 1;
    while (prods > 0) {
      if((prods = semctl(counting_sem_id, 0, GETVAL)) == -1)
      printf("counting_sem_id GETVAL error\n");
      sleep(PROD_DELAY);
    }
		
    // detach shared memory
    if ((shmdt(shm_ptr)) == -1) printf("detaching shared memory failed\n");
    if(shmctl(shared_mem_id, 0, IPC_RMID) == -1)
      printf("shared_mem_id shm RMID error\n");
    printf("producer %d: shared memory detached\n", parent);

    // removes semaphore when everything is consumed
    if(semctl(critical_region_id, 0, IPC_RMID) == -1)
      printf("critical_region_id sem RMID error\n");
    if(semctl(counting_sem_id, 0, IPC_RMID) == -1)
      printf("counting_sem_id sem RMID error\n");
    printf("producer %d: semaphores removed\n", parent);

    // signal child processes to exit
    printf("killing processes...\n");
    kill(child1, SIGTERM);
    kill(child2, SIGTERM);
    kill(child3, SIGTERM);
		
    // give some time for children to die
    sleep(2);
    raise(SIGTERM);
  }

  // just in case
  exit(EXIT_SUCCESS);
}

//////////////////////////////////////////////////
// FUNCTIONS
//////////////////////////////////////////////////

void consumer(int child, int critical_region_id, int counting_sem_id,
	char *shm_ptr)
{
  int prods;
  printf("consumer %d says hello\n", child);

  //allow time for introductions
  sleep(8);

  while(1) {
    // find number of products available for consumption
    if((prods = semctl(counting_sem_id, 0, GETVAL)) == -1)
      printf("counting_sem_id GETVAL error\n");
    while(prods < 1) {
      sleep(CONS_DELAY);
      if((prods = semctl(counting_sem_id, 0, GETVAL)) == -1)
      	printf("counting_sem_id GETVAL error\n");
    }

    // take semaphore, enter critical region
    down(critical_region_id);

    // we should reall check again and make sure that some one else did
    // not consume my item, but Sean is lazy

    printf("consumer %d: taking product %c, %d left\n", 
      child, shm_ptr[prods - 1], prods - 1);
		
    // dec number of items to be consumed, just consumed 1
    down(counting_sem_id);

    up(critical_region_id);
    sleep(CONS_DELAY);
  }
}

void producer(int pid, int critical_region_id, int counting_sem_id,
	char *shm_ptr)
{
  int i, prods;
  printf("PRODUCER %d says hi\n", pid);
	
  //allow time for introductions
  sleep(1);

  for(i = 0; i < PRODUCE_MAX; i++) {
    // take semaphore, enter critical region
    down(critical_region_id);
		
    if((prods = semctl(counting_sem_id, 0, GETVAL)) == -1)
      printf("counting_sem_id GETVAL error\n");
    shm_ptr[prods] = (char)((i % 26) + 'a');
    printf("PRODUCER %d: giving product %c (#%d)\n", pid, shm_ptr[prods], i);

    // inc number of items to be consumed
    up(counting_sem_id);
    up(critical_region_id);

    sleep(PROD_DELAY);
  }
}

void signal_term(int sig)
{
  printf("process %d says bye bye\n", getpid());
  exit(EXIT_SUCCESS);
}

void down(int semid) 
{
  struct sembuf op;
  op.sem_num = op.sem_flg = 0;
  op.sem_op = -1; // dec count by 1

  if(semop(semid, &op, 1) == -1) printf("down semop error\n");
}

void up(int semid)
{
  struct sembuf op;
  op.sem_num = op.sem_flg = 0;
  op.sem_op = 1; // inc count by 1

  if(semop(semid, &op, 1) == -1) printf("down semop error\n");
}
