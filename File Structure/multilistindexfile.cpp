#include <iostream>
#include <fstream>
using namespace std;
struct student
{

    char name[20];
    int rollno;
    int cour;
    int i;


};
struct course
{
    int cou;
    int marks;
    int i;

};
struct reg
{
    int rollno;
    int fp;
    int bp;
    int cor;
    int sfp;
    int sbp;
};
ostream &operator<<(ostream &fout2,student &s)
{
    fout2<<s.name<<" "<<s.cgpa<<" "<<s.rollno<<endl;
    return fout2;
}
int main()
{

int i;
ifstream fin;
ofstream fout2;
fout2.open("input.txt");
student s[10];
reg f[10];
for(i=0;i<4;i++)
{
    cout<<"name\n";
    cin>>s[i].name;

    cout<<"roll no\n";
    cin>>s[i].rollno;
    f[i].rollno=s[i].rollno;
    cout<<" course\n";
    cin>>s[i].cour;
    f[i].cou=s[i].cour;
    cout<<
}
for(i=0;i<4;i++)
{
    cout<<s[i];
  fout2<<s[i];
}
fout2.close();
ofstream out;
out.open("index.txt");
float max;
int g;

}

return 0;

}
