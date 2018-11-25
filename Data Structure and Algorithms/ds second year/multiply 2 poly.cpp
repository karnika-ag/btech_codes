

#include <iostream>
using namespace std;
const int MAX = 10 ;

class poly
{
	private :

		struct term
		{
			int coeff ;
			int exp ;
		} t[MAX] ;
		int noofterms ;

	public :

		poly( ) ;
		void polyappend ( int c, int e ) ;
		void polyadd ( poly &p1, poly &p2 ) ;
		void polymul ( poly &p1, poly &p2 ) ;
		void display( ) ;
} ;


poly :: poly( )
{
	noofterms = 0 ;
	for ( int i = 0 ; i < MAX ; i++ )
	{
		t[i].coeff = 0 ;
		t[i].exp = 0 ;
	}
}


void poly :: polyappend ( int c, int e )
{
	t[noofterms].coeff = c ;
	t[noofterms].exp =  e ;
	noofterms++ ;
}

void poly :: display( )
{
	int flag = 0 ;
	for ( int i = 0 ; i < noofterms ; i++ )
	{
		if ( t[i].exp != 0 )
			cout << t[i].coeff << "x^" << t[i].exp  << " + " ;
		else
		{
			cout << t[i].coeff ;
			flag = 1 ;
		}
	}
	if ( !flag )
		cout << "\b\b  " ;
}


void poly :: polyadd ( poly &p1, poly &p2 )
{
	int coeff, exp ;
    poly p ;

	int c = p1.noofterms ;
	int d = p2.noofterms ;

	for ( int i = 0, j = 0 ; i <= c || j <= d ; )
	{
		if ( p1.t[i].coeff == 0 && p2.t[j].coeff == 0 )
			break ;
		if ( p1.t[i].exp >= p2.t[j].exp )
		{
			if ( p1.t[i].exp == p2.t[j].exp )
			{
				coeff = p1.t[i].coeff + p2.t[j].coeff ;
				exp = p1.t[i].exp ;
				i++ ;
				j++ ;
			}
			else
			{
				coeff = p1.t[i].coeff ;
				exp = p1.t[i].exp ;
				i++ ;
			}
		}
		else
		{
			coeff = p2.t[j].coeff ;
			exp = p2.t[j].exp ;
			j++ ;
		}
		p.polyappend ( coeff, exp ) ;
	}
	*this = p ;
}


void poly :: polymul ( poly &p1, poly &p2 )
{
	int coeff, exp ;
	poly t1, t2 ;

	if ( p1.noofterms != 0 && p2.noofterms != 0 )
	{
		for ( int i = 0 ; i < p1.noofterms ; i++ )
		{
            poly p ;
			for ( int j = 0 ; j < p2.noofterms ; j++ )
			{
				coeff = p1.t[ i ].coeff * p2.t[ j ].coeff ;
				exp = p1.t[ i ].exp + p2.t[ j ].exp ;
				p.polyappend ( coeff, exp ) ;
			}

			if ( i != 0 )
			{
				t2.polyadd ( t1, p ) ;
				t1 = t2  ;
			}
			else
				t1 = p ;
		}

		*this = t2 ;
	}
}

 main( )
{int n,n1,c,c1,e,e1,i;
	poly p1 ;
cout<<"enter the no of elements in the 1st polynomial\n";
cin>>n;
for(i=0;i<n;i++)
{cout<<"enter the coeff\n";
cin>>c;
cout<<"enter the exp\n";
cin>>e;
	p1.polyappend ( e,c ) ;
}
	poly p2 ;
cout<<"enter the no of elements in the 2nd polynomial\n";
cin>>n1;
for(i=0;i<n1;i++)
{cout<<"enter the coeff\n";
cin>>c1;
cout<<"enter the exp\n";
cin>>e1;
	p2.polyappend ( e1,c1 ) ;
}
	poly p3 ;
	p3.polymul( p1, p2 ) ;

	cout << endl << "First polynomial: " << endl  ;
	p1.display( ) ;

	cout << endl << "Second polynomial: " << endl ;
	p2.display( ) ;

	cout << endl << "Resultant polynomial: " << endl ;
	p3.display( ) ;
	system ("pause");
	return 0;
}
