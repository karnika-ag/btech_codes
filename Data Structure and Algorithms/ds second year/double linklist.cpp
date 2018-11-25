#include<iostream>
//#include<stdlib.h>
using namespace std;

class dlist
 {
      struct listnode
      {int data;
       listnode *next;
       listnode *prev;
       };
	listnode *header,*footer;
  public:
	dlist()
	 {
		header=NULL;
		footer=NULL;
	 }
	int isempty();
	listnode* find(int x)
	
 {
	listnode *temp=header;
	while(temp!=NULL && temp->data!=x)
		temp=temp->next;
	return temp;
 }
void dlist::insert()
 {
	int e;
	cout<<"Enter element to be inserted :";
	cin>>e;
	if(isempty())
	 {
		listnode *temp=new listnode;
		temp->data=e;
		temp->next=temp->prev=NULL;
		header=footer=temp;
	 }
	else
	 {
		listnode *curr=header;
		while(curr->next!=NULL)
			curr=curr->next;
		listnode *temp=new listnode;
		temp->data=e;
		temp->next=NULL;
		temp->prev=curr;
		footer=curr->next=temp;
	 }
	cout<<"Element inserted."<<endl;
 }
	void del();
	void insert_before(int);
	void insert_after(int);
	void reverse();
	void print();
 };
int dlist::isempty()
 {
	return header==NULL;
 }

void dlist::del()
 {
	int e;
	cout<<"Enter element to be deleted:";
	cin>>e;
	if(header->data==e)
	 {
		listnode *temp=header;
		header=header->next;
		delete temp;
		header->prev=NULL;
		cout<<"Element deleted."<<endl;
	 }
	else
	 {
		if(footer->data==e)
		 {
			listnode *temp=footer;
			footer=footer->prev;
			delete temp;
			footer->next=NULL;
			cout<<"Element deleted."<<endl;
		 }
		else
		 {
			listnode *curr=find(e);
			if(curr!=NULL)
			 {
				curr->prev->next=curr->next;
				curr->next->prev=curr->prev;
				delete curr;
				cout<<"Element deleted."<<endl;
			 }
			else
				cout<<"Element not found."<<endl;
		 }
	 }
 }
void dlist::insert_before(int x)
 {
	if(isempty())
	 {
		cout<<"List empty. Inserting into list.."<<endl;
		insert();
		return;
	 }
	listnode *curr=find(x);
	if(curr!=NULL)
	 {
		int e;
		cout<<"Enter element to be inserted:";
		cin>>e;
		listnode *temp=new listnode;
		temp->data=e;
		temp->next=curr;
		temp->prev=curr->prev;
		curr->prev=temp;
		if(header->data==x)
			header=temp;
		cout<<"Element inserted.";
	 }
	else
		cout<<"Element not found.";
 }
void dlist::insert_after(int x)
 {
	if(isempty())
	 {
		cout<<"List empty. Inserting into list.."<<endl;
		insert();
		return;
	 }
	listnode *curr=find(x);
	if(curr!=NULL)
	 {
		int e;
		cout<<"Enter element to be inserted:";
		cin>>e;
		listnode *temp=new listnode;
		temp->data=e;
		temp->next=curr->next;
		temp->prev=curr;
		curr->next=temp;
		if(footer->data==x)
			footer=temp;
		cout<<"Element inserted.";
	 }
	else
		cout<<"Element not found.";
 }
void dlist::reverse()
 {
	listnode *curr=header;
	listnode *temp=NULL;
	while(curr!=NULL)
	 {
		temp=curr->next;
		curr->next=curr->prev;
		curr->prev=temp;
		curr=curr->prev;
	 }
	temp=header;
	header=footer;
	footer=temp;
	cout<<"List reversed. ";
	print();
 }
void dlist::print()
 {
	if(!isempty())
	 {
		listnode *curr=header;
		cout<<"The list is :"<<endl;
		while(curr!=NULL)
		 {
			cout<<curr->data<<endl;
			curr=curr->next;
		 }
	 }
	else
		cout<<"List empty.";
 }
main()
 {
	dlist l;
	int x;
	while(1)
	 {
		system("clear");
		cout<<endl<<"1.insert";
		cout<<endl<<"2.delete";
		cout<<endl<<"3.insertbefore";
		cout<<endl<<"4.insertafter";
		cout<<endl<<"5.reverse";
		cout<<endl<<"6.print";
		cout<<endl<<endl<<"Enter choice :";
		char ch;
		cin>>ch;
		int k;
		switch(ch)
		 {
			case '1':l.insert();
				 break;
			case '2':l.del();
				 break;
			case '3':cout<<"Enter before which element to insert :";
				 cin>>k;
				 l.insert_before(k);
				 break;
			case '4':cout<<"Enter after which element to insert :";
				 cin>>k;
				 l.insert_after(k);
				 break;
			case '5':l.reverse();
				 break;
			case '6':l.print();
				 break;
			default :exit(0);
		 }
		 cout<<"press 1 to continue.....";
		 cin>>x;
	
	 }
 }
