#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#define MAXLINE 1000

struct mymesg
{
    long mtype;
    int a[5];
};

void Merge(int a[],int mer[],int ct)
{
    if(ct==0)
    {
        ct+=4;
        for(int i=1;i<=ct;i++)
            mer[i]=a[i];
    }
    else
    {
        for(int i=1;i<=4;i++)
        {
            int j=1;
            while(a[i]>mer[j]&&j<=ct)j++;
            if(j>ct)
                mer[j]=a[i];
            else
            {
                for(int k=ct;k>=j;k--)
                    mer[k+1]=mer[k];
                mer[j]=a[i];
            }
            ct++;
        }
    }
}

int main()
{
    int n,pid,mpid,sum,b[17],mer[17],num=16;
    mpid=msgget(12,0666|IPC_CREAT);
    system("clear");
    printf("\nElements are...");
    for(int i=1;i<=num;i++)
    {
        b[i]=rand()%150;
        printf("%d ",b[i]);
    }
    printf(" \n");
    int i,ct=1,gmax;
    static int f=0;
    n=4;sum=0;gmax=4;
    for(i=1;i<=n;i++)
    {
        struct mymesg ptr;
        ptr.mtype=2;
        pid=fork();
        printf("\n");
        if (pid>0)
        {
            int k=0;
           
            printf("\nGroup %d: ",i);
            ptr.a[0]=i;
            for(int j=ct;j<=ct+gmax-1;j++)
            {
                ptr.a[++k]=b[j];
                printf("%d ",ptr.a[k]);
            }

            printf(" \n");
            msgsnd(mpid,&ptr,MAXLINE,IPC_NOWAIT);
            waitpid(pid,NULL,0);
            //sleep(5);
            msgrcv(mpid,&ptr,MAXLINE,-1,0);
             //sleep(5);
            printf("\nSorted Sub-Group %d: ",i);
            for(int j=1;j<=gmax;j++)
                printf("%d ",ptr.a[j]);
            printf(" \n");

            Merge(ptr.a,mer,ct-1);

            if(ct==num+1-gmax)
                break;
            ct+=gmax;
            continue;
        }
        else
        {
            printf("hello hw r u \n");
            msgrcv(mpid,&ptr,MAXLINE,2,IPC_NOWAIT);
              f++;
            for(int j=1;j<=gmax;j++)
            {
                for(int k=1;k<=gmax-j;k++)
                {
                    if(ptr.a[k]>ptr.a[k+1])
                    {
                        int t=ptr.a[k+1];
                        ptr.a[k+1]=ptr.a[k];
                        ptr.a[k]=t;
                    }
                }
            }
             printf("\nChild Sorted Sub-Group %d: ",ptr.a[0]);
            for(int j=1;j<=gmax;j++)
                printf("%d ",ptr.a[j]);
            printf(" \n");           
            ptr.mtype=1;
            msgsnd(mpid,&ptr,MAXLINE,IPC_NOWAIT);
            exit(0);
        }
    }
    printf("\nMerged Sorted Group....");
    for(int i=1;i<=num;i++)
        printf("%d ",mer[i]);
    printf(" ");
    return 0;
}
