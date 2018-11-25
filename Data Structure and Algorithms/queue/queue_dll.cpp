#include<iostream>
using namespace std;
class queue
{
 private:
         struct node
         {
                int data;
                node *right;
                node *left;
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
                   p->left=rear;
                   p->right=NULL;
                   front=rear=p;
     }
     else
     {
         node *r=new node;
         r->data=n;
         r->right=NULL;
         r->left=rear;
         rear->right=r;
         rear=r;
     }
}
int queue::del()
{
     if(rear==NULL)
     cout<<"queue is empty\n";
     else
     {
         int m;
         node *temp;
         temp=front;
         m=temp->data;

         front=front->right;
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
                       cout<<q->data<<" ";
                       q=q->right;
     cout<<"dhfj";
     }
}
int main()
{
    queue q;
    q.add(1);
    q.add(2);
    q.add(3);
    q.add(4);
    q.add(5);
    q.add(6);
    cout<<"the elements of the queue are:\n";
    q.display();
    cout<<"\nelement deleted is : "<<q.del()<<endl;
    cout<<"\nelement deleted is : "<<q.del()<<endl;
    cout<<"\nelement deleted is : "<<q.del()<<endl;
    cout<<"\nelement deleted is : "<<q.del()<<endl;
    
    cout<<"the elements of the queue are:\n";
     q.display();
    system("pause");
    return 0;
}
