#include<iostream>
using namespace std;
struct node
{
	int data;
	node *left;
	node *right;
};
struct node *root,*temp,*prev,*t1,*t2,*t,*t3;
class tree
{
	public:
	tree()
	{
		root=NULL;
		t3=NULL;
		t1=NULL;
		t2=NULL;
		t=NULL;
	}
	void insert()
	{
		struct node *n=new node;
		int d;
		cout<<"Enter the data : ";
		cin>>d;
		n->data=d;
		n->left=NULL;
		n->right=NULL;
		if(root!=NULL)
		{
			temp=root;
			prev=NULL;
			while(temp!=NULL)
			{
				prev=temp;
				if(n->data<temp->data)
				{
					temp=temp->left;
				}
				else
				{
					temp=temp->right;
				}
			}
			if(n->data<prev->data)
			{
				prev->left=n;
			}
			else
			{
				prev->right=n;
			}
		}
		else
		{
			root=n;
		}
	}
	void preorder(node *n)
	{
		if(n==NULL)
		{
			return;
		}
		else
		{
			cout<<n->data<<"\t";
			preorder(n->left);
			preorder(n->right);
		}
	}
	void eval(int d,int flag)
	{
		if(flag!=1)
		{
			t=root;
			while(t->data!=d&&t!=NULL)
			{
				if(t2!=NULL)
				{
				t3=t2;
				}
				if(t1!=NULL)
				{
				t2=t1;
				}
				t1=t;
				if(d<t->data)
				{
					t=t->left;
				}
				else
				{
					t=t->right;
				}
			}
			if(t->data==d)
			{
				if(t2!=NULL)
				{		
					if(t2->left==t1&&t1->left==t)
					{
						t2->left=t1->right;
						t1->right=t2;
						t1->left=t->right;
						t->right=t1;
					}
					else
					{
						if(t2->right==t1&&t1->right==t)
						{
							t2->right=t1->left;
							t1->left=t2;
							t1->right=t->left;
							t->left=t1;
						}
						else
						{
							if(t2->left==t1&&t1->right==t)
							{
								t2->left=t->right;
								t1->right=t->left;
								t->left=t1;
								t->right=t2;
							}
							else
							{
								t2->right=t->left;
								t1->left=t->right;
								t->right=t1;
								t->left=t2;
							}	
						}
					}
				}
				else
				{
					if(t1->left==t)
					{
							t1->left=t->right;
							t->right=t1;
					}
					if(t1->right==t)
					{
							t1->right=t->left;
							t->left=t1;
					}
					root=t;
				}
				if(t3==NULL&&t2!=NULL)
				{
					flag=1;
					root=t;
				}
				if(t3!=NULL)
				{
					if(t->data<t3->data)
					{
						t3->left=t;
					}
					else
					{
						t3->right=t;
					}
					eval(t->data,flag);
				}
			}
			else
			{
				cout<<"NOT FOUND"<<endl;
				flag=1;
			}
		}
	}
};
int main()
{
	int ch,flag;
	class tree *t=new tree;
	do
	{
		cout<<"Press 1 to Insert"<<endl;
		cout<<"Press 2 to convert"<<endl;
		cout<<"Press 3 to Display in preorder"<<endl;
		cout<<"Press 4 to Quit"<<endl;
		cout<<"Enter your choice : ";
		cin>>ch;
		switch(ch)
		{
			case 1:
			t->insert();
			break;
			case 2:
			int d;
			flag=0;
			cout<<"Enter the data you want as root : ";
			cin>>d;
			t->eval(d,flag);
			break;
			case 3:
			t->preorder(root);
			cout<<endl;
			break;
			case 4:
			break;
			default:
			cout<<"Enter your Correct CHOICE"<<endl;
			break;
		}
	}while(ch!=4);
	return 0;
}
