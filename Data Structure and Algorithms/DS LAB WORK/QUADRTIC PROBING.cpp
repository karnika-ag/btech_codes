#include<iostream>
using namespace std;
void quadratic(int a[])
{
	int d;
	cout<<"Enter the number : ";
	cin>>d;
	int i=d%10;
	int c=0;
	int j=i;
	while(a[j]!=0&&c!=6)
	{
		c=c+1;
		j=i+(c*c);
		j=j%10;
	}
	if(a[j]==0)
	{
		a[j]=d;
	}
	else
	{
		cout<<"NOT POSSIBLE"<<endl;
	}
}
void display(int a[])
{
	for(int i=0;i<10;i++)
	{
		if(a[i]==0)
		{
			cout<<"EMPTY"<<endl;
		}
		else
		{
			cout<<i<<" -> "<<a[i]<<endl;
		}
	}
}
void search(int a[])
{
	int d;
	cout<<"Enter the element to be searched : ";
	cin>>d;
	int i=d%10;
	int c=0;
	int j=i;
	while(a[j]!=d&&c!=6)
	{
		c=c+1;
		j=i+(c*c);
		j=j%10;
	}
	if(a[j]==d)
	{
		cout<<"Your data is in "<<j<<" -> position"<<endl;
	}
	else
	{
		cout<<"NOT FOUND"<<endl;
	}
}	
int main()
{
	int a[10],ch;
	for(int i=0;i<10;i++)
	{
		a[i]=0;
	}
	do
	{
		cout<<"Press 1 to INSERT"<<endl;
		cout<<"Press 2 to DISPLAY"<<endl;
		cout<<"Press 3 to SEARCH"<<endl;
		cout<<"Press 4 to QUIT"<<endl;
		cout<<"Enter your choice : ";
		cin>>ch;
		switch(ch)
		{
			case 1:
			quadratic(a);
			break;
			case 2:
			display(a);
			break;
			case 3:
			search(a);
			break;
			case 4:
			break;
			default:
			cout<<"Enter correct choice"<<endl;
			break;
		}
	}while(ch!=4);
	return 0;
}
