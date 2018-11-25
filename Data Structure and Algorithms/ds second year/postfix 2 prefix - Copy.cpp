


#include <iostream>
#include <string>
using namespace std;
const int MAX = 50 ;

class postfix
{
	private :

		char stack[MAX][MAX], target[MAX] ;
		char temp1[2], temp2[2] ;
		char str1[MAX], str2[MAX], str3[MAX] ;
		int i, top ;

	public :

		postfix( ) ;
		void setexpr ( char *c ) ;
		void push ( char *str ) ;
		void pop ( char *a ) ;
		void convert( ) ;
		void show( ) ;
} ;


postfix :: postfix( )
{
	i = 0 ;
	top = -1 ;
	strcpy ( target, "" ) ;
}


void postfix :: setexpr ( char *c )
{
	strcpy ( target, c ) ;
}


void postfix :: push ( char *str )
{
	if ( top == MAX - 1 )
		cout << endl << "Stack is full" ;
	else
	{
		top++ ;
		strcpy ( stack[top], str ) ;
	}
}


void postfix :: pop ( char *a )
{
	if ( top == -1 )
		cout << endl << "Stack  is empty" ;
	else
	{
		strcpy ( a, stack[top] ) ;
		top-- ;
	}
}


void postfix :: convert( )
{
	while ( target[i] != '\0' )
	{
		
		if ( target[i] == ' ')
			i++ ;
		if( target[i] == '%' || target[i] == '*' ||
			target[i] == '-' || target[i] == '+' ||
			target[i] == '/' || target[i] == '$' )
		{
			pop ( str2 ) ;
			pop ( str3 ) ;
			temp1[0] = target[i] ;
			temp1[1] = '\0' ;
			strcpy ( str1, temp1 ) ;
			strcat ( str1, str3 ) ;
			strcat ( str1, str2 ) ;
			push ( str1 ) ;
		}
		else
		{
			temp1[0] = target[i] ;
			temp1[1] = '\0' ;
			strcpy ( temp2, temp1 ) ;
			push ( temp2 ) ;
		}
			i++ ;
	}
}


void postfix :: show( )
{
	char *temp = stack[0] ;
	while ( *temp )
	{
		cout << *temp << " " ;
		temp++ ;
	}
}

 main( )
{
	char expr[MAX] ;

	cout << "\nEnter an expression in postfix form: " ;
	cin.getline ( expr, MAX ) ;

	postfix q ;
	q.setexpr ( expr ) ;
	q.convert( ) ;

	cout << "\nThe Prefix expression is: " ;
	q.show( ) ;
	system("pause");
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
