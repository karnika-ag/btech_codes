#include<stdio.h>
#include<pthread.h>
#define MAXCHAIRS 4

int nextcustomerno=1;
int first=0,last=0;
int waitingcustomercount=0;
pthread_mutex_t lck;
pthread_cond_t custcond[MAXCHAIRS];
int custnos[MAXCHAIRS];
pthread_cond_t brbrcond;

int main(void)
{
Initialize();
pthread_t brbr,cust[MAXCHAIRS+1];
pthread_create(&brbr,NULL,Barber,0);
for(i=0;i<MAXCHAIRS+1;i++)
pthread_create(&cust[i],NULL,customer,NULL);
pthread_join(cust[0],NULL);
return 0;
}

void *Barber(void)
{
while(1)
{
checkAndsleep();
servicecustomers();
}
}

void *customer(void)
{
int custno;
while(1)
{
custno=checkvacancyAndwait();
if(custno!=0)
{
printf("customer %d getting serviced....\n",custno);
sleep(3);
}
else
{
printf("no chair is vacant and customer leaving...\n");
sleep((time(NULL)%5)+1);
}
}
}

int checkcustomerAndsleep(void)
{
pthread_mutex_lock(&lck);
if(waitingcustomercount==0)
pthread_cond_wait(&brbrcond,&lck);

}


void servicecustomer()
{
int custno,chair;
chair=first;
first=(first+1)%MAXCHARS;
custno=custnos[chair];
waitingcustomercount--;
pthread_cond_signal(&custcond[chair]);
pthread_mutex_unlock(&lck);
printf("barber servicing %d customer \n",custno);
sleep(3);

}


void checkvacancyAndwait(void)
{
int chair,custno;
pthread_mutex_lock(&lck);
if(waitingcustomercount==MAXCHARS)
{
pthread_mutex_unlock(&lck);
return 0;
}
else
{
chair=last;
custno=custnos[chair]=nextcustomerno++;
last=(chair+1)%MAXCHAIRS;
waitingcustomercount++;

if(waitingcustomercount==1)
wakeupBarber();
customerwait(chair);
pthread_mutex_unlock(&lck);
return custno;


}
}


void wakeupBarber()
{
pthread_cond_signal(&brbrcond);
}


void customerwait(int chair)
{
pthread_cond_wait((&custcond[chair]),&lck);
}












































