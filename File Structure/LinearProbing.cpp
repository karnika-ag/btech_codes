#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
using namespace std;
char garb;
int n;
class student
{
	public:
	int rno;
	char name[11];
	float cgpa;
	student()
	{
		rno=0;
		strcpy(name,"EMPTY");
		cgpa=0.00;
	}
	void getdata();
	void putdata();
};
void student::getdata()
{
	cout<<"Enter R No: ";
	cin>>rno;
	cin.get(garb);
	cout<<"Enter Name: ";
	cin.getline(name,11);
	for(int i=0;i<strlen(name);i++)
	{
		if(name[i]==' ')
			name[i]='.';
	}
	cout<<"Enter CGPA: ";
	cin>>cgpa;
	cin.get(garb);
}
void student::putdata()
{
	for(int i=0;i<strlen(name);i++)
	{
		if(name[i]=='.')
			name[i]=' ';
	}
	cout<<"R No: "<<rno<<endl;
	cout<<"Name: "<<name<<endl;
	cout<<"CGPA: "<<cgpa<<endl;
}
fstream & operator >> (fstream &in, student &s)
{
	in>>s.rno>>s.name>>s.cgpa;
	return in;
}
fstream & operator << (fstream &out, student &s)
{
	out<<setw(7)<<s.rno;
	out<<setw(10)<<s.name;
	out<<setw(5)<<s.cgpa<<endl;
	return out;
}
void writefile()
{
	student s,s1;
	fstream fout("linear_probing.txt",ios::out);
	int i,pos,count;
	char p;
	cout<<"Enter the size of your file.\n";
	cin>>n;
	for(i=0;i<n;i++)
		fout<<s;
	fout.close();
	for(int i=0;i<n;i++)
	{
		cout<<"Enter details of student "<<i+1<<endl;
		s.getdata();
		fstream fout("linear_probing.txt",ios::ate|ios::in|ios::out);
		pos=s.rno%n;
		fout.seekg(24*pos,ios::beg);
		fout.seekp(24*pos,ios::beg);
		fout>>s1;
		fout.seekg(24*pos,ios::beg);
		fout.seekp(24*pos,ios::beg);
		if(s1.rno==0)
			fout<<s;
		else
		{
			count=0;
			while(s1.rno!=0 && count<n)
			{
				pos=(pos+1)%n;
				fout.seekg(24*pos,ios::beg);
				fout.seekp(24*pos,ios::beg);
				fout>>s1;
				count++;
			}	
			if(count<n)
			{
				fout.seekg(24*pos,ios::beg);
				fout.seekp(24*pos,ios::beg);
				fout<<s;
			}
		}
		cout<<"Want to enter more details.? Y/y for yes.\n";
		cin>>p;
		if(p!='y' && p!='y')
			break;
	}
	fout.close();
}
void search()
{
	student s;
	fstream fin("linear_probing.txt",ios::in);
	int rno,count=0;
	cout<<"Enter the R No you want to search.\n";
	cin>>rno;
	int pos=rno%10;
	fin.seekg(24*pos,ios::beg);
	fin>>s;
	if(s.rno==rno)
		s.putdata();
	else
	{
		while(s.rno!=rno && count<n)
		{
			pos=(pos+1)%n;
			fin.seekg(24*pos,ios::beg);
			fin>>s;
			count++;
		}
		if(count<n) s.putdata();
		else cout<<"Not Found.\n";
	}
	fin.close();
}
int main()
{
	writefile();
	char p='y';
	while(p=='y' || p=='y')
	{
		search();
		cout<<"Want to search more.? \n";
		cin>>p;
	}
	return 0;
}
