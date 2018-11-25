#include<iostream>
using namespace std;
class List
{
	public:
		struct Node
		{
			int elem;
			Node *next;
			Node(int e=0,Node *n=NULL):
			elem(e),next(n){}
		};
		Node *current1;
		Node *head;
		Node *current2;
		Node *current3;
	public:
		void insert();
		void display(List &l3);
		void merge(List &l1,List &l2,List &l3);
		List();
};
List::List()
{
	head=new Node(0,NULL);
	current1=NULL;
	current2=NULL;
	current3=NULL;
}
void List::insert()
{
	int x;
	Node *current_pos=head;
	char choice='y';
	while(choice!='n')
	{
		cout<<"Enter the element into the list "<<endl;
		cin>>x;
		Node *temp=new Node(x,NULL);
		current_pos->next=temp;
		current_pos=temp;
		cout<<"Want to enter more (y/n):"<<endl;
		cin>>choice;
	}
}
void List::merge(List &l1,List &l2,List &l3)
{
	current1=l1.head->next;
	current2=l2.head->next;
	current3=l3.head;
	while((current1!=NULL)&&(current2!=NULL))
	{
			if(current1->elem<current2->elem)
			{
				Node *temp=new Node(current1->elem,NULL);
				current3->next=temp;
				current3=temp;
				current1=current1->next;
			}
			else if(current1->elem>current2->elem)
			{
				Node *temp=new Node(current2->elem,NULL);
				current3->next=temp;
				current3=temp;
				current2=current2->next;
			}
			else
			{
				Node *temp=new Node(current1->elem,NULL);
				current3->next=temp;
				current3=temp;
				current1=current1->next;
				current2=current2->next;
			}
	}
	while(current1!=NULL)
	{
		Node *temp=new Node(current1->elem,NULL);
		current3->next=temp;
		current3=temp;
		current1=current1->next;
	}
	while(current2!=NULL)
	{
		Node *temp=new Node(current2->elem,NULL);
		current3->next=temp;
		current3=temp;
		current2=current2->next;
	}
}
void List::display(List &l)
{
	Node *current=l.head;
	current=current->next;
	while(current!=NULL)
	{
		cout<<current->elem<<"   ";
		current=current->next;
	}
	cout<<endl;
}
int main()
{
	List l1,l2,l3;
	cout<<"Enter the first sorted list "<<endl;
	l1.insert();
	cout<<"Enter the second sorted list "<<endl;
	l2.insert();
	cout<<"The first list is "<<endl;
	l1.display(l1);
	cout<<"The second list is "<<endl;
	l2.display(l2);
	cout<<"The two lists after merging is "<<endl;
	l3.merge(l1,l2,l3);
	l3.display(l3);
	system("pause");
	return 0;
}





