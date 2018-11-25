
#include<iostream>

using namespace std;
const int tablesize=10;
class hashing
{
private:
	int arr[tablesize],x;
public:
	hashing()
	{
		for(int i=0;i<tablesize;i++)
		{
			arr[i]=-1;
		}
	}
	void add(int n);
	int prime();
	void display();
};
void hashing::add(int n)
{
	int s,y,z;
	cout<<endl;
	x=n%tablesize;
	s=prime();
	if(arr[x]==-1)
		arr[x]=n;
	else
	{
		z=n%s;
		y=s-z;
		y--;
		arr[y]=n;
	}
}
int hashing::prime()
{
	int r;
	r=0;
		for(int i=tablesize-1;i>0;i--)
		{
			for(int j=2;j<i;j++)
			{
				if(i%j==0)
				{
					r=1;
					break;
				}
			}
			if(r==0)
			{
				return i ;
			}
			r=0;
		}
		return 0;
}
void hashing::display()
{
	
	cout<<endl;
	cout<<"THE VALUE OF THE ARRAY AFTER DOUBLE HASHING"<<endl;
	cout<<endl;
	for(int i=0;i<tablesize;i++)
	{
		if(arr[i]==-1)
			arr[i]=0;
		cout<<i<<" Element: "<<arr[i]<<endl;
	}
	cout<<endl;
}
 main()
{
	hashing h;
	cout<<endl;
	int x,y;
	cout<<"Enter the Number of elements you want to enter: ";
	cin>>x;
	cout<<endl;
	for(int i=0;i<x;i++)
	{
		cout<<"Enter the Value of "<<i+1<<" element: ";
		cin>>y;
		cout<<endl;
		h.add(y);
	}
	cout<<endl;
	h.display();
	cout<<endl;
	cout<<endl;
system ("pause");
return 0;
}
