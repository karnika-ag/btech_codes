#include <iostream>
using namespace std;
class cqueue
{
	private :
		struct node
		{
			int data ;
			node * link ;
		} *front, *rear ;

	public :

		cqueue( ) ;
		void add ( int item ) ;
		int del( ) ;
		void display( ) ;
} ;

cqueue::cqueue( )
{
	front = rear = NULL ;
}

void cqueue:: add( int item )
{
	node *q ;
	q = new node ;
	q -> data = item ;

	if ( front == NULL )
		front = q ;
	else
		rear -> link = q ;

	rear = q ;
	rear -> link = front ;
}

int cqueue:: del( )
{
	node *q ;
	int item ;

	if ( front == NULL )
		cout << "\nqueue is empty" ;
	else
	{
		if ( front == rear )
		{
			item = front -> data ;
			delete front ;
			front = NULL ;
			rear = NULL ;
		}
		else
		{
			q = front ;
			item = q -> data ;
			front = front -> link ;
			rear -> link = front ;
			delete q ;
		}
		return ( item ) ;
	}
	}

void cqueue::display( )
{
	node *q, *p ;
	q = front ;
	p = NULL ;

	cout << endl ;
	
	while ( q != p )
	{
		cout << q -> data << "  "  ;
		q = q -> link ;
		p = front ;
	}
}


int main( )
{
    cqueue q;
    int y,n;
do
{
     cout<<"press 1 to add..\n 2 to show\n..3 to delete\n..4 to terminate the program\n";
    cout<<"enter ur choice\n";
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
