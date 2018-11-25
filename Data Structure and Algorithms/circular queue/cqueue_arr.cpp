#include<iostream>
using namespace std;
class cqueue
{
      private:
              int a[10];
              int rear,front;
      public:
             cqueue();
             void add(int);
             int del();
             void display();
};
cqueue::cqueue()
{
                rear=-1;
                front=-1;
                for(int i=0;i<10;i++)
                a[i]=0;
}
void cqueue::add(int n)
{
     if((front==-1&&rear==9)||(front==rear+1))
      cout<<"\nqueue is full\n";
     else
     {
         if(rear==9)
         rear=0;
         else
         rear++;
         a[rear]=n;
         if(front==-1)
         front =0;
     }
}
int cqueue::del()
{
     if(front==-1)
       {
       cout<<"queue is empty\n";     
        return (-1);
       }
        int t=a[front];
         a[front]=0;
         if(front==rear)
         {
                        front=-1;
                        rear=-1;
         }
         else
         {
             if(front==9)
             front =0;
             else
             front++;
         }
         return t;
}
void cqueue::display()
{
     for(int i=0;i<10;i++)
     cout<<a[i]<<" ";
}

int main()
{
    cqueue q;
    int y,n;
do
{
    cout<<"press 1 to add..\n 2 to show\n..3 to delete\n..4 to terminate the program\n";
    cin>>y;
    switch(y)
    {
      case 1: cout<<"enter the no. to be inserted\n";
        cin>>n;
        q.add(n);
        break;
      case 3:
           cout<<"\nelelment deleted :"<<q.del();
           break;
      case 2:
           q.display();
           break;
      case 4:
           break;
    }
}while(y!=4);
system("pause");
return 0;
}
