#include<iostream.h>
class Shortest
{
	private:
		struct Node
		{
			char vertex[5];
			int length;
			Node *next;
			Node()
			{
				vertex[0]='\0',
				length=0,
				next=NULL;
			}
		};
		struct stack 
		{
			char vertex[5];
			stack *next;
			stack()
			{
				vertex[0]='\0';
				next=NULL;
			}
		};
		int i;
		Node *a[100];
		int known[100];
		stack *head,Current_Pos;
	public:
		Shortest()
		{
			cout<<"\nEnter the no.of vertices:";
			cin>>i;
			//Node *a[i];
			for(int j=0;j<i;j++)
			{
				a[j]=new Node();
				known[j]=0;
			}
			head=new stack();
		}
		void takeinput()
		{
			char v[5];
			int d;
			for(int j=0;j<i;j++)
			{
				Node *t=a[j];
				cout<<"Enter the name of the "<<j+1<<" vertex";
				cin>>a[j]->vertex;
				int ch;
				cout<<"1-add adjascent vertex,0-end\n";
				cin>>ch;
				while(ch)
				{
					cout<<"Enter the adj vertex:";
					cin>>v;
					Node *n=new Node();
					for(int y=0;y<5;y++)
						n->vertex[y]=v[y];
					t->next=n;
					t=n;
					cout<<"1-add,0-end:";
					cin>>ch;
				}
			}
		}
		void print()
		{
			int p;
			for(p=0;p<i;p++)
			{
				cout<<"\nVERTEX "<<p+1<<" and adj vertices:";
				Node *t=a[p];
				while(t!=NULL)
				{
					cout<<t->vertex<<"  "<<t->length<<"  \t";
					t=t->next;
				}
			}
		}
		int check()
		{
			if(head->next==NULL)
				return 0;
			return 1;
		}
		int check1()
		{
			for(int l=0;l<i;l++)
				if(known[l]==0)
					return 1;
			return 0;
		}
		int get(char ch[])
		{
			for(int k=0;k<i;k++)
			{
				if(strcmp(a[k]->vertex,ch)==0)
					return k;
			}	
		}
		void push(char ch[])
		{
			stack *t=new stack();
			for(int y=0;y<5;y++)
				t->vertex[y]=ch[y];
			t->next=head->next;
			head->next=t;
		}
		void top1(char ch[])
		{
			stack *t=head;
			if(t->next!=NULL)
			{
				while(t->next!=NULL)
					t=t->next;
				for(int y=0;y<5;y++)
					ch[y]=t->vertex[y];
				//cout<<ch<<"kl";
			}
			else
			{
				cout<<"NOT";
				exit(1);
			}
		}
		void top(char ch[])
		{
			stack *t=head;
			if(head->next!=NULL)
				while(t->next->next!=NULL)
					t=t->next;
			else
			{
				cout<<"top not possible\n";
				exit(1);
			}
			for(int h=0;h<5;h++)
				ch[h]=t->next->vertex[h];
			t->next=NULL;	
		}
		int findunincludedin(char ch[])
		{
			int index=get(ch);
			Node *t=a[index]->next;
			while(t!=NULL)
			{
				for(int u=0;u<5;u++)
					ch[u]=t->vertex[u];
				int i=get(ch);
				if(known[i]==0)
					return 1;
				t=t->next;
			}
			return 0;
		}
		void dft()
		{
			char ch[5];
			int index;
			cout<<"Enter from vertex:";
			cin>>ch;
			push(ch);
			int pp=get(ch);
			known[pp]=1;
			cout<<"\n\nOutput:  "<<ch<<"  ";
			fflush(stdout);
			int jj;
			while(check1())
			{
				if(head->next==NULL)
					break;
				top(ch);
				jj=get(ch);
				Node *t=a[jj]->next;
				while(t!=NULL)
				{
					for(int g=0;g<5;g++)
						ch[g]=t->vertex[g];
					if(known[get(ch)]==0)
					{
						push(ch);
						cout<<"\n  "<<ch<<"  ";
						pp=get(ch);
						known[pp]=1;
					}
					t=t->next;
				}
			}
			if(head->next==NULL)
			{
				cout<<"\nNot possible with vertex given.\n";
				exit(1);
			}
		}
				
};
int main()
{
	Shortest s;
	system("clear");
	s.takeinput();
	cout<<"\nList is:";
	s.print();
	s.dft();
	cout<<"\n";
	return 0;
}
