#include<iostream>
#include<cmath>
using namespace std;
const int d=-100;
 struct cbtnode
 {
 	cbtnode *lchild;
 	cbtnode *rchild;
 	int data;
 };
 int height(cbtnode *T)
{
	int h1,h2;
	if(T==NULL)
	return -1;
	else
	{
		h1=height(T->lchild);
		h2=height(T->rchild);
		return h1>h2?h1+1:h2+1;
	}
}
cbtnode* create_cbtree(cbtnode *T,int height_of_tree)
 {
	if(T==NULL && height_of_tree>0){
		T=new cbtnode;
		T->data=d;
		T->lchild=NULL;
		T->rchild=NULL;
	}
	else if(T!=NULL && height_of_tree>0)
	{
		T->lchild=create_cbtree(T->lchild,height_of_tree-1);
		T->rchild=create_cbtree(T->rchild,height_of_tree-1);
	}
	return T;
 }
 void inorder(cbtnode *T){
	if(T!=NULL){
		inorder(T->lchild);
		cout<<T->data<<" ";
		inorder(T->rchild);
	}
}
 void put_data(cbtnode *&T,int a[],int count)
 {
 	static int i=0;
 	if( T&&T->lchild==NULL && T->rchild==NULL&&i<count )
	 {
 		T->data=a[i];
 		i++;
 	}
 	else if(T!=NULL)
	 {
 		put_data(T->lchild,a,count);
 		put_data(T->rchild,a,count);
 	 }
 }
 int max(int a,int b)
 {
 	if(a>b){
 		return a;
 	}
 	else{
 		return b;
 	}
 }
 int compare(cbtnode *T)
 {
 	if(T->lchild!=NULL)
	 {
 		int a=compare(T->lchild);
 		int b=compare(T->rchild);
 		return(max(a,b));
 	 }
 	else{
 		return (T->data);
 	}
 }
 void search(cbtnode* &T,int k)
{
	if(T)
	{
		if(T->data==k)
		T->data=-100;
		search(T->lchild,k);
		search(T->rchild,k);
	}
}
int main()
{
	cbtnode *T=NULL;
	int count=0,a[30],n=0;
	cout<<"Enter the input below:\n";
	cout<<"and enter -1 to terminate the input\n";
	cin>>n;
	for(int i=0;n!=-1;i++){
		a[i]=n;
		count++;
		cout<<"Enter next value\n";
		cin>>n;
	}
	int i=0;
	while( count>pow(2,i) ){   // even if the no, of the inputs is equal to the number of nodes then also i will give me the correct height...
		i++;
	}
	int height_of_tree=i;    // now the tree should be of the height i
	for(int i=0;i<count;i++)
		T=create_cbtree(T,height_of_tree+1);
		cout<<"\n";
		put_data(T,a,count);
		for(int i=0;i<count;i++)
		{
			int s=compare(T);
			cout<<s<<" ";
			search(T,s);
		}
	return 0;
}
