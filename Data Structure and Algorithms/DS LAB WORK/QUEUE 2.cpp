#include<iostream>
using namespace std;
class queue
{
 private:
         struct node
         {
                int data;
                node *link;
         }*rear,*front;
 public:
        queue();
        void add(int n);
        int del();
        void display();
};
queue::queue()
{
              front=rear=NULL;
}
void queue::add(int n)
{
     if(rear==NULL)
     {
                   node *p=new node;
                   p->data=n;
                   p->link=rear;
                   front=rear=p;
     }
     else
     {
         node *r=new node;
         r->data=n;
         r->link=NULL;
         rear->link=r;
         rear=r;
     }
}
int queue::del()
{
     if(rear==NULL)
     {
     cout<<"queue is empty\n";
     return -1;
     }
     else
     {
         int m;
         node *temp;
         temp=front;
         m=temp->data;
         front=front->link;
         delete temp;
         return m;
     }
}
void queue::display()
{
     node *q;
     q=front;
     while(q!=NULL)
     {
                       cout<<q->data<<"\n ";
                       q=q->link;
     }
}
int main()
{
    int x,n;
        queue q;
    do
    {
        cout<<"enter 1 to add,2 to delete ,3todisplay,4 for end";
        cin>>x;
        switch(x)
        {
                 case 1:
                      cout<<"enter the elment";
                      cin>>n;
                      q.add(n);
                      break;
                 case 2:
                      cout<<"\nelement deleted is : "<<q.del()<<endl;
                      cout<<"\nelement deleted is : "<<q.del()<<endl;
                      break;
                 case 3:
           
                      cout<<"the elements of the queue are:\n";
                      q.display();
                      break;
               case 4:
                    break;
        }
        }while(x!=4);

    system("pause");
    return 0;
}
