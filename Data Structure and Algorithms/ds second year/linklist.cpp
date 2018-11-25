#include <iostream>
using namespace std;
class linklist
{private:struct node
          {int data;
           node *link;
           }*p;
 public:linklist();
        void append(int num);
        void addatbeg(int num);
        void addafter(int loc,int num);
        void display();
        int count();
        void del(int num);
        ~linklist();
};
linklist::linklist()
{p=NULL;
}
void linklist::append(int num)
{node *temp,*r;
 if(p==NULL)
 { temp=new node;
   temp->data=num;
   temp->link=NULL;
 }
 else
 {temp=p;
  while(temp->link!=NULL)
  temp=temp->link;
  r=new node;
  r->data=num;
  r->link=NULL;
  temp->link=r;
 }
}
void linklist::addatbeg(int num)
{node *temp;
temp=new node;
temp->data=num;
temp->link=p;
p=temp;
}
void linklist::addafter(int loc,int num)
{node *temp,*r;
temp=p;
for(int i=0;i<loc;i++)
{temp=temp->link;
 if(temp==NULL)
 {cout<<"there are less than"<<loc<<"elements in the list"<<endl;
  return;
}
}
r=new node;
r->data=num;
r->link=temp->link;
temp->link=r;
}
void linklist::display()
{node *temp=p;
 cout<<endl;
 while(temp!=NULL)
 {cout<<temp->data;
  temp=temp->link;
}
}
int linklist::count()
{node *temp=p;
int c=0;
while(temp!=NULL)
{temp=temp->link;
 c++;
}
return c;
}
void linklist::del(int num)
{node *old,*temp;
 temp=p;
 while(temp!=NULL)
 {if(temp->data==num)
  {if(temp==p)
   p=temp->link;
   else
   old->link=temp->link;
   delete temp;
   return;
}
else
{old=temp;
temp=temp->link;
}
cout<<"element not found";
}}
linklist::~linklist()
{node *q;

while(p!=NULL)
 {q=p->link;
  delete p;
  p=q;
}}



int main()
{char s='y';
 linklist a;
 while(s!='n')
  {cout<<"enter ur choice";
   cout<<"1.insertion at end  2.insertion at begining 3.inserton after 4.deletion 5.display";
   int x;
   cin>>x;
   if(x<5)
   cout<<"enter the number";
   int n;
   cin>>n;
   switch(x)
   {case 1:a.append(n);
           break;
    case 2:a.addatbeg(n);
           break;
    case 3:cout<<"enter the location";
           int r;cin>>r;a.addafter(n,r);
           break;
    case 4:a.del(n);
           break;
    default:a.display();
           break;
}
cout<<"continue(y or n)?";
 cin>>s;
}
return 0;
}
   


           
