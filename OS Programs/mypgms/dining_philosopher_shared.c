struct shared_data {
  sem_t spoon;
  sem_t phil[N];
  int state[N];
};

struct shared_data *shared;

void initialize_shared(); /* at program start */
void finalize_shared();   /* at program end */
void initialize_shared()
{
  int i;
  int prot=(PROT_READ|PROT_WRITE);
  int flags=(MAP_SHARED|MAP_ANONYMOUS);
  shared=mmap(0,sizeof(*shared),prot,flags,-1,0);
  memset(shared,'\0',sizeof(*shared));
  sem_init(&shared->spoon,1,1);
  for(i=0;i<N;++i) sem_init(&shared->phil[i],1,1);
}

void finalize_shared()
{
  int i;
  for(i=0;i<N;++i) 
   sem_destroy(&shared->phil[i]);
  munmap(shared, sizeof(*shared));
}


void philosopher(int i)
{
  while(1)
  {
    sleep(1);
    take_spoon(i);
    sleep(2);
    put_spoon(i);
    sleep(1);
  }
}

void take_spoon(int i)
{
  sem_wait(&spoon);
  state[i] = HUNGRY;
  printf("philosopher %d is hungry\n",i+1);
  test(i);
  sem_post(&spoon);
  sem_wait(&phil[i]);
}

void put_spoon(int i)
{
  sem_wait(&spoon);
  state[i] = THINKING;
  printf("philosopher %d puts down spoon %d and %d hin\n",i+1,LEFT+1,i+1);
  printf("philosopher %d thinks\n",i+1);
  test(LEFT);
  test(RIGHT);
  sem_post(&spoon);
}

void test(int i)
{
  if( state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
  {
    state[i] = EATING;
    printf("philosopher %d takes spoon %d and %d\n",i+1,LEFT+1,i+1);
    printf("philosopher  %d eats\n",i+1);
    sem_post(&phil[i]);
  }
}


int main(void)
{
  int i;
  pid_t pid, pids[N]; // process ids
  initialize_shared();
  for(i=0;i<N;++i)
  {
    pid = fork();
    if(pid==0)
    {
      // child
      philosopher(i);
      _exit(0);
    }
    else if(pid>0)
    {
      // parent
      pids[i] = pid;
      printf("pids[%d]=%d\n",i,pids[i]);
    }
    else
    {
      perror("fork");
      _exit(0);
    }
  }
  // wait for child processes to end
  for(i=0;i<N;++i) waitpid(pids[i],NULL,0);

  finalize_shared();
  return 0;
}
