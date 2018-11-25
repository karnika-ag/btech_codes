
#include<iostream>
using namespace std;
/*class listnode
{
   int element;
   listnode *left;
   listnode *right;
  // friend class bstree;
  
};*/
class bstree
{public:
      struct listnode
      {   int element;
          listnode *left;
          listnode *right;
          }*root;   
             
   
   public:
	bstree()
	{
	   root=NULL;
	}
	void insert(int data,listnode *(&t))
	{
	     if(t==NULL)
	     {
		t=new listnode;
		t->element=data;
	     }
	     else if(data<(t->element))
		insert(data,t->left);
	     else if(data>(t->element))
		insert(data,t->right);
	     else
		cout<<"Duplication found!Cannot be inserted!";
	}
	void preprint(listnode *t)
	{
	    if(t!=NULL)
	    {
		 cout<<"\t"<<t->element;
		 preprint(t->left);
		 preprint(t->right);
	     }
	}
	void inprint(listnode *t)
	{
	    if(t!=NULL)
	    {
		 inprint(t->left);
		 cout<<"\t"<<t->element;
		 inprint(t->right);
	     }
	}
	void postprint(listnode *t)
	{
	    if(t!=NULL)
	    {
		 postprint(t->left);
		 postprint(t->right);
		 cout<<"\t"<<t->element;
	     }
	}
	void deletex(int x,listnode *&t)
	{
	     if(t==NULL)
		cout<<"Element not found!";
	     else if(x<t->element)
		deletex(x,t->left);
	     else if(x>t->element)
		deletex(x,t->right);
	     else if(t->left!=NULL && t->right!=NULL)
	     {
		  t->element=findmin(t->right)->element;
		  deletex(t->element,t->right);
	     }
	     else
	     {
		  listnode *tmp=t;
		  t=(t->left==NULL)?t->right:t->left;
		  delete tmp;
	     }
	}
	listnode * findmin(listnode *t)
	{
	      if(t==NULL)
		 return NULL;
	      else if(t->left==NULL)
		 return t;
	      return findmin(t->left);
	}
	listnode * findmax(listnode *t)
	{
	      if(t==NULL)
		 return NULL;
	      else if(t->right==NULL)
		 return t;
	      return findmax(t->right);
	}
	listnode * find(int x,listnode *t)
	{
	      if(x<t->element)
		 return find(x,t->left);
	      else if(x>t->element)
		 return find(x,t->right);
	      else
		 return t;
	}
	void menu()
	{
	     listnode *t;
	     char ch='y';
	     int c=1;
	     int x;
	     while((ch=='y' || ch=='Y') && c!=9 )
	     {
		 cout<<"\n1.Insert an element";
		 cout<<"\n2.Print in postorder";
		 cout<<"\n3.Print in preorder";
		 cout<<"\n4.Print in inorder";
		 cout<<"\n5.Delete an element";
		 cout<<"\n6.Print minimum";
		 cout<<"\n7.Print maximum";
		 cout<<"\n8.Find an element";
		 cout<<"\n9.Exit";
		 cout<<endl<<"\nEnter  your choice:";
		 cin>>c;
		 switch(c)
		 {
		    case 1:cout<<"Enter the element to be inserted:";
			   cin>>x;
			   insert(x,root);
			   break;
		    case 2:cout<<"Post order =";postprint(root);break;
		    case 3:cout<<"Pre order =";preprint(root);break;
		    case 4:cout<<"In order =";inprint(root);break;
		    case 5:cout<<"Enter the element to be deleted:";
			   cin>>x;
			   deletex(x,root);break;
		    case 6:t=findmin(root);
			   if(t)
			       cout<<"\nMinimum ="<<t->element;
				else
					 cout<<"Tree is empty!";
			   break;
		    case 7:t=findmax(root);
			   if(t)
			       cout<<"\nMaximum ="<<t->element;
			   else
			       cout<<"Tree is empty!";
			   break;
		    case 8:cout<<"Enter the element to be searched:";
			   cin>>x;
			   if(find(x,root))
			      cout<<"Element found!";
			   else
			      cout<<"Element not found!";
			   break;
		    case 9:break;
		    default:cout<<"Wrong input!";
		 }
		 if(c!=9)
		 {
		    cout<<"\nDo you want to continue(y/n)?";
		    cin>>ch;
		 }
	     }

	}

};
 main()
{
     bstree t;
     t.menu();
}
