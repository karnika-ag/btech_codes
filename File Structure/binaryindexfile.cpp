#include <iostream>
#include <fstream>
using namespace std;
struct index
{
    int ind;
    float cgpa1;
};
struct student
{

    char name[20];
    float cgpa;
    int rollno;
    index a;

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
for(i=0;i<4;i++)
{
    cout<<"name\n";
    cin>>s[i].name;

    cout<<"cgpa\n";
    cin>>s[i].cgpa;
    cout<<"roll no\n";
    cin>>s[i].rollno;
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

for(i=0;i<4;i++)
{

    for(g=0;g<4;g++)
    {
            if(s[g].cgpa<s[i].cgpa)
            {
                max=s[i].cgpa;
            }


    }
    out<<max<<"\t"<<i<<endl;
    cout<<max<<"\t"<<i<<endl;
    /*s[i].a.ind=i;
    s[i].a.cgpa1=max;
    cin>>s[i].a.ind;
    cin>>s[i].a.cgpa1;
    cout<<s[i].a.ind;
*/
}

return 0;

}
