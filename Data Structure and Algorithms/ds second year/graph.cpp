#include<iostream.h>
#include<conio.h>

void create(); 
void dfs();  
void bfs();  

struct node  
{
   int data,status;
   struct node *next;
   struct link *adj;
};

struct link  
{
   struct node *next;
   struct link *adj;
};

struct node *start,*p,*q;
struct link *l,*k;

int main()
{
   int ch;
   create();
   do
   {
	  cout<<"\n1.DFS"<<endl;
      cout<<"2.BSF"<<endl;
      cout<<"3.Exit"<<endl;
	  cin>>ch;
	  switch(ch)
	  {
	 case 1:
		dfs();
		break;
	 case 2:
		bfs();
		break;
	 default:
		ch=0;
	  }
   }while(ch);
   return 0;
}

void create()
{
   int dat,flag=0;
   start=NULL;
   cout<<"Enter the nodes in the graph(0 to end): ";
   while(1)
   {
	  cin>>dat;
	  if(dat==0)
	 break;
	  p=new node;
	  p->data=dat;
	  p->status=0;
	  p->next=NULL;
	  p->adj=NULL;
	  if(flag==0)
	  {
	 start=p;
	 q=p;
	 flag++;
	  }
	  else
	  {
	 q->next=p;
	 q=p;
	  }
   }
   p=start;
   while(p!=NULL)
   {
	  cout<<"Enter the links to "<<p->data<<" (0 to end) : ";
	  flag=0;
	  while(1)
	  {
	 cin>>dat;
	 if(dat==0)
		break;
	 k=new link;
	 k->adj=NULL;
	 if(flag==0)
	 {
		p->adj=k;
		l=k;
		flag++;
	 }
	 else
	 {
		l->adj=k;
		l=k;
	 }
	 q=start;
	 while(q!=NULL)
	 {
		if(q->data==dat)
		   k->next=q;
		q=q->next;
	 }
	  }
	  p=p->next;
   }

   return;
}



void bfs()
{
   int qu[20],i=1,j=0;
   p=start;
   while(p!=NULL)
   {
	  p->status=0;
	  p=p->next;
   }
   p=start;
   qu[0]=p->data;
   p->status=1;
   while(1)
   {
	  if(qu[j]==0)
	 break;
	  p=start;
	  while(p!=NULL)
	  {
	 if(p->data==qu[j])
		 break;
	 p=p->next;
	  }
	  k=p->adj;
	  while(k!=NULL)
	  {
	 q=k->next;
	 if(q->status==0)
	 {
		qu[i]=q->data;
		q->status=1;
		qu[i+1]=0;
		i++;
	 }
	 k=k->adj;
	  }
	  j++;
   }
   j=0;
   cout<<"Breadth First Search Results";

   while(qu[j]!=0)
   {
	  cout<<qu[j]<<"  ";
	  j++;
   }
   getch();
   return;
}



void dfs()
{
   int stack[25],top=1;
   cout<<"Depth First Search Results";
   p=start;
   while(p!=NULL)
   {
	  p->status=0;
	  p=p->next;
   }
   p=start;
   stack[0]=0;
   stack[top]=p->data;
   p->status=1;
   while(1)
   {
	  if(stack[top]==0)
	 break;
	  p=start;
	  while(p!=NULL)
	  {
	 if(p->data==stack[top])
		break;
	 p=p->next;
	  }
	  cout<<stack[top]<<"  ";
	  top--;
	  k=p->adj;
	  while(k!=NULL)
	  {
	 q=k->next;
	 if(q->status==0)
	 {
		top++;
		stack[top]=q->data;
		q->status=1;
	 }
	 k=k->adj;
	  }
   }
   getch();
   return;
}
