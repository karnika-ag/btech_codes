#include<iostream>
using namespace std;
struct node
{
	int data;
	node *left;
	node *right;
};
struct node *root,*temp,*prev,*p;
struct node *t1,*t2,*t3;
class tree
{
	public:
	tree()
	{
		root=NULL;
	}
	void add()
	{
		int d;
		struct node *n=new node;
		cout<<"Enter the data to be inserted : ";
		cin>>d;
		n->data=d;
		n->left=NULL;
		n->right=NULL;
		if(root!=NULL)
		{
			temp=root;
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
	void inorder(node *n)
	{
		if(n==NULL)
		{
			return;
		}
		else
		{
			inorder(n->left);
			cout<<n->data<<"\t";
			inorder(n->right);
		}
	}
	void postorder(node *n)
	{
		if(n==NULL)
		{
			return;
		}
		else
		{
			postorder(n->left);
			postorder(n->right);
			int bal;
			bal=brnchlen(n->left)-brnchlen(n->right);
			cout<<n->data<<" -> "<<bal<<endl;
		}
	}
	int brnchlen(node *n)
	{
		if(n==NULL)
		{
			return 0;
		}
		else
		{
			if(n->left==NULL&&n->right==NULL)
			{
				return 1;
			}
			else
			{
				int d;
				if(brnchlen(n->left)>brnchlen(n->right))
				{
					d=1+brnchlen(n->left);
				}
				else
				{
					d=1+brnchlen(n->right);
				}
				return d;
			}
		}
	}
	void eval(node *n)
	{
		if(n==NULL)
		{
			return;
		}
		else
		{
			eval(n->left);
			eval(n->right);
			int bal;
			bal=brnchlen(n->left)-brnchlen(n->right);
			if(bal==-1||bal==0||bal==1)
			{
				return;
			}
			else
			{
				temp=root;prev=NULL;
				while(temp->data!=n->data)
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
				n=cnvrt(n);
				if(prev==NULL)
				{
					root=n;
				}
				else
				{
					if(n->data<prev->data)
					{
						prev->left=n;
					}
					else
					{
						prev->right=n;
					}
				}
				eval(root);
			}
		}
	}
	node* cnvrt(node *n)
	{
		if(n->left!=NULL&&n->left->left!=NULL)
		{
			n=ll(n);
		}
		else
		{
			if(n->right!=NULL&&n->right->right!=NULL)
			{
				n=rr(n);
			}
			else
			{
				if(n->left!=NULL&&n->left->right!=NULL)
				{
					n=lr(n);
				}
				else
				{
					n=rl(n);
				}
			}
		}
		return n;
	}
	node* ll(node *n)
	{
		t1=n;
		t2=n->left;
		t1->left=t2->right;
		t2->right=t1;
		n=t2;
		return n;
	}
	node* rr(node *n)
	{
		t1=n;
		t2=n->right;
		t1->right=t2->left;
		t2->left=t1;
		n=t2;
		return n;
	}
	node* lr(node *n)
	{
		t1=n;
		t2=t1->left;
		t3=t2->right;
		t2->right=t3->left;
		t1->left=t3->right;
		t3->right=t1;
		t3->left=t2;
		n=t3;
		return n;
	}
	node* rl(node *n)
	{
		t1=n;
		t2=t1->right;
		t3=t2->left;
		t2->right=t3->left;
		t1->left=t3->right;
		t3->right=t2;
		t3->left=t1;
		n=t3;
		return n;
	}
};
int main()
{
	int ch;
	class tree *t=new tree;
	do
	{
		cout<<"Press 1 to Insert"<<endl;
		cout<<"Press 2 to Display in postorder and inorder"<<endl;
		cout<<"Press 3 to Quit"<<endl;
		cout<<"Enter your choice : ";
		cin>>ch;
		switch(ch)
		{
			case 1:
			t->add();
			t->eval(root);
			break;
			case 2:
			cout<<"POSTORDER with its BALANCE FACTOR : "<<endl;
			t->postorder(root);
			cout<<endl;
			cout<<"INORDER : "<<endl;
			t->inorder(root);
			cout<<endl;
			break;
			case 3:
			break;
			default:
			cout<<"Enter your Correct CHOICE"<<endl;
			break;
		}
	}while(ch!=3);
	return 0;
}
