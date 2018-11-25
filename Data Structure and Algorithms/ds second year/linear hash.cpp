

#include<iostream>

using namespace std;
class hashing
{
private:
	int arr[10],hashval;
public:
	hashing()
	{
		for(int i=0;i<10;i++)
		{
			arr[i]=-1;
		}
	}
	void add(int n);
	void display();
};
void hashing::add(int n)
{
	cout<<endl;
	cout<<endl;
	int x,y=1;
	x=n%10;
	if(arr[x]==-1)
	{
		arr[x]=n;
	}
	else
	{
		while(y!=0)
		{
			x++;
			if(x==10)
			{
				x=0;
			}
			if(arr[x]==-1)
			{
				arr[x]=n;
				y=0;
			}
		}
	}
}
void hashing::display()
{
	cout<<endl;
	cout<<endl;
	cout<<"THE ELEMENTS OF THE ARRAY ARE"<<endl;
	cout<<endl;
	cout<<endl;
	for(int i=0;i<10;i++)
	{
		if(arr[i]==-1)
			arr[i]=0;
		cout<<i<<" Element: "<<arr[i]<<endl;
	}
}
main()
{       
	hashing h;
	int x,y;
	cout<<endl;
	cout<<"Enter the Number of elements you want to enter: ";
	cin>>y;
	cout<<endl;
	cout<<endl;
	for(int i=0;i<y;i++)
	{
		cout<<"Enter the Value of "<<i+1<<" element: ";
		cin>>x;
		cout<<endl;
		h.add(x);
	}
	
	h.display();
	
	cout<<endl;
	system ("pause");
	
	return 0;
}

