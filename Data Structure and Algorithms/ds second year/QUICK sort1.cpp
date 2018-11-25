#include<iostream>
using namespace std;
const int MAX=50;
class qcksort
{
       int a[MAX];
       int count;
    public:
       void accept();
       void display();
       void qsort(int,int);
       void insort(int,int);
       int median(int,int);
       qcksort();
       void sort();
       void swap(int &,int &);
};
qcksort::qcksort()
{
   count=0;
}
void qcksort::accept()
{
    cout<<"\nPress any charcter to terminate.....";
    cout<<"\nEnter The numbers:";
    while((cin>>a[count++])>0);
    count--; 
}
void qcksort::insort(int left ,int right)
{
    int tmp;
    for(int i=left+1;i<=right;i++)
    
    {int j;
	 tmp=a[i];
	 for( j=i; j>left && tmp<a[j-1] ;j--)
	      a[j]=a[j-1];
	 a[j]=tmp;
    }
}
void qcksort::swap(int &a,int &b)
{
     int tmp=a;
     a=b;
     b=tmp;
}
int qcksort::median(int l,int r)
{
     int cen=(l+r)/2;
     if(a[l]>a[cen])
	  swap(a[l],a[cen]);
     if(a[l]>a[r])
	  swap(a[r],a[l]);
     if(a[r]<a[cen])
	  swap(a[r],a[cen]);
     swap(a[cen],a[l]);
     return a[l];
}
void qcksort::qsort(int l,int r)
{
     if(l+10<=r)
     {
	    int pivot=median(l,r);
	    int i=l+1;
	    int j=r;
	    while(1)
	    {
		 while(a[i]<pivot) i++;
		 while(a[j]>=pivot)j--;
		 if(i<j)
		    swap(a[i],a[j]);
		 else
		    break;
	    }
	    swap(a[j],a[l]);

	    qsort(l,j-1);
	    qsort(j+1,r);
     }
     else
     {
	  insort(l,r);
     }

}
void qcksort::sort()
{
    qsort(0,count-1);
}
void qcksort::display()
{
    for(int i=0;i<count;i++)
       cout<<a[i]<<"\t";
}
 main()
{
    qcksort x;
    x.accept();
    cout<<"\nThe elements before sorting are:\n";
    x.display();
    x.sort();
    cout<<"\nThe elements after sorting are:\n";
    x.display();
    system("pause ");
}
