#include<iostream>
using namespace std;

class circular
{  private:struct listnode
         {int element;
       	listnode *next;
	     };
	listnode *header;
	public:
	void deleter();
	void insertafter();
	void insertbefore();
	circular();
	void insert();
	void display();
	void menu();
	listnode *findprev(int data)
	{
    listnode *tmp;
    tmp=header;
    int check=0;
    while((tmp->next)->element!=data && !check)
    {
	tmp=tmp->next;
	if(tmp==header)
	   check=1;
    }
    if(check)
       return NULL;
    return tmp;
}
};
circular:: circular()
{
   header=NULL;
}
void circular::insert()
{
      listnode *tmp,*prev;
      tmp=new listnode;
      cout<<"Enter the element to insert:";
      cin>>tmp->element;
      if(!header)
	 header=tmp;
      tmp->next=header;
      if(header)
      {
	 prev=header;
	 while(prev->next !=header)
	    prev=prev->next;
	 prev->next=tmp;
      }
}
void circular::insertbefore()
{
     int pre,data;
     cout<<"Enter the element to be inserted:";
     cin>>data;
     cout<<"Enter the element before which it has to be inserted:";
     cin>>pre;
     listnode *tmp,*prev;
     prev=findprev(pre);
     if(prev)
     {
	   tmp=new listnode;
	  if(prev->next==header)
	     header=tmp;
	  tmp->element=data;
	  tmp->next=prev->next;
	  prev->next=tmp;
     }
     else
	cout<<"The element is not found!";
}
void circular::insertafter()
{
     int pos,data;
     cout<<"Enter the element to be inserted:";
     cin>>data;
     cout<<"Enter the element after which it has to be inserted:";
     cin>>pos;
     listnode *tmp,*prev;
     prev=findprev(pos);
     if(prev)
     {
	  prev=prev->next;
	  tmp=new listnode;
	  tmp->element=data;
	  tmp->next=prev->next;
	  prev->next=tmp;
     }
     else
	cout<<"Element not found!";
}
void circular:: display()
{
   listnode *tmp=header;
   if(tmp!=NULL)
   {
	   do
	   {
		   cout<<"\t"<<tmp->element;
		   tmp=tmp->next;
	    }while(tmp->next!=header);
	    if(tmp!=header)
		cout<<"\t"<<tmp->element;
    }
    else
	   cout<<"List is empty!";
}
void circular::deleter()
{
    int element;
    cout<<"Enter the element to be deleted:";
    cin>>element;
    if(header)
    {
	listnode *tmp=header,*prev;
	if(tmp->element==element)
	{
	   if(header==header->next)
	     header=NULL;
	   else
	   {
	      prev=header;
	      while(prev->next !=header)
		prev=prev->next;
	      prev->next=tmp->next;
	      header=tmp->next;
	   }
	   delete tmp;
	   tmp=header;
	}
	else
	{
		prev=findprev(element);
		if(prev!=NULL)
		{
		      tmp=prev->next;
		      prev->next=tmp->next;
		      delete tmp;
		}
		else
		    cout<<"The element is not found!";
	 }
     }
     else
       cout<<"The list is empty!";
}

void circular::menu()
{
   char ch='y';
   int c;
   while(ch=='y'|| ch=='Y')
   {
	cout<<"\n1.Insert an element";
	cout<<"\n2.Display all elements";
	cout<<"\n3.Insert an element before another";
	cout<<"\n4.Insert an element after another";
	cout<<"\n5.Delete an element";
	cout<<"\n6.Exit";
	cout<<"\n\nEnter your choice:";
	cin>>c;
	switch(c)
	{
	     case 1:insert();break;
	     case 2:display();break;
	     case 3:insertbefore();break;
	     case 4:insertafter();break;
	     case 5:deleter();break;
	     case 6:break;
	     default:cout<<"wrong input!";
	}
	if(c!=6)
	{
	     cout<<"\nDo you want to continue( y or n)?";
	     cin>>ch;
	}
	else
	    ch='n';

    }
} main()
{
	circular s;
	s.menu();
}

		      
	   

