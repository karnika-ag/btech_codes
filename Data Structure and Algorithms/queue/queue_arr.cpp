#include<iostream>
using namespace std;
class queue
{
      private:
              int a[10];
              int rear,front;
      public:
             queue();
             void add(int);
             void del();
};
queue::queue()
{
              rear=front=0;
}
void queue::add(int n)
{
     if(rear==10)
     cout<<"\nqueue is full\n";
     else
     a[rear++]=n;
}
void queue::del()
{
    if(rear==0||rear==front)
    cout<<"\nqueue is empty\n";
    else
    cout<<"element deleted is :"<<a[front++];
}
int main()
{
    queue q;
    int y,n;
do
{
    cout<<"\npress 1 to add 2 to delete 3 to terminate\n";
    cout<<"enter ur choice\n";
    cin>>y;
    switch(y)
    {
      case 1: cout<<"enter the no. to be inserted\n";
        cin>>n;
        q.add(n);
        break;
      case 2:
           q.del();
           cout<<endl;
           break;
      case 3:
           break;
    }
}while(y!=3);
system("pause");
return 0;
}
