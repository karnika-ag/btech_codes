#include <iostream>
#include <fstream>
using namespace std;
class student
{
    public:
    char name[20];
    int rollno;
    int index;
};
class course
{
    public:
    int courseno;
    char details[2];
};
ofstream & operator<<(ofstream & fout,student & s)
{
    fout<<s.rollno<<" ";
    fout<<s.index<<" ";
    fout<<s.name<<endl;;
    return (fout);
}
ofstream &operator<<(ofstream &fout1,course &c)
{
    fout1<<c.courseno<<" ";
    fout1<<c.details<<endl;
    return (fout1);
}

int main()
{
    ofstream fout;
    ifstream fin;
    ofstream fout1;
    fout1.open("course.txt");
    fout.open("student.txt");
    student s[2];
    course c[2];
    int i,j,k;
    for(i=0;i<2;i++)
    {
        cout<<"name\n";
        cin>>s[i].name;
        cout<<"rollno\n";
        cin>>s[i].rollno;
        cout<<"index\n";
        cin>>s[i].index;

        fout<<s[i];

    }
    for(i=0;i<2;i++)
    {
        cout<<"course no\n";
        cin>>c[i].courseno;
        cout<<"course name\n";
        cin>>c[i].details;
        fout1<<c[i];
    }
    ofstream fout2;
    fout2.open("regn.txt");
    for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
        {
            if(s[i].index==c[j].courseno)
            {
                fout2<<s[i].rollno<<" "<<s[i].name<<" "<<c[j].details<<" "<<c[j].courseno<<endl;
            }
        }
    }
    return 0;


}
