#include <bits/stdc++.h>
#include <fstream>
#include <string.h>
using namespace std;
class tours
{
    char name[40];
    char add[100];
    char em[30];
    int id=0;
    int tid=0;
    int cost=0;
    int d,y,m;
    string s;
public:
    void trip();
    void new_user();
    void show();
    int user_id();
    void show_trip();
};
class file
{
    ifstream fin;
    ofstream fout;
    tours b;
    tours a[5];
public:
    void add_user();
    void delete_user();
    void show_users();
    void new_trip();
    void delete_trip();
    void show_trips();
    void user_d();
    void edit_user();
};

void tours::new_user()
{
    cout<<endl<<"Enter user name       :  ";
    cin.ignore();
    cin.getline(name,40);
    cout<<"Enter user address    :   ";
    cin.getline(add,100);
    cout<<"Enter user email-id   :  ";
    cin>>em;
    cout<<"Enter user ID         :  ";
    cin>>id;
}
void tours::trip()
{
    int i;
    cout<<"Enter The Destination For your Trip :  "<<endl;
    cin>>s;
    cout<<"Enter Trip date : "<<endl;
    cin>>d;
    cout<<"Enter Trip month (in numbers) : "<<endl;
    cin>>m;
    cout<<"Enter Trip year : "<<endl;
    cin>>y;
    cout<<"Enter total cost : "<<endl;
    cin>>cost;
}
void tours::show()
{
    cout<<endl<<"User name       : "<<name<<endl;
    cout<<"User address    : "<<add<<endl;
    cout<<"User email-id   : "<<em<<endl;
    cout<<"User ID         : "<<id<<endl;
}
void tours::show_trip()
{
    int i;
    cout<<"Trip Destination : "<<s<<endl;
    cout<<"Trip Date        : "<<d<<"/ "<<m<<"/ "<<y<<endl;
    cout<<"Trip cost        : "<<cost<<endl;
}

int tours::user_id()
{
    return id;
}
void file::add_user()
{
    int i;
    tours p[5];
fout.open("user.dat",ios::binary|ios::app);
if(fout)
{
    cout<<endl<<endl<<endl<<endl<<endl<<"         Welcome to FUTURISTIC Tours And Travels "<<endl<<endl<<endl;
    cout<<endl<<"How many users do you want to add (max=5) ? "<<endl;
    cin>>i;
    for(int j=0;j<i;j++)
       {
           cout<<endl<<"User "<<j+1<<endl;
         p[i].new_user();
         fout.write((char*)&p[i],sizeof(p[i]));
         cout<<"User added "<<endl;
       }
}
fout.close();
}

void file::new_trip()
{
    tours c;
int q,flag=0;
fout.open("trips.dat",ios::binary|ios::app);
cout<<endl<<"Enter user Id for whom you want to add a trip :  ";
cin>>q;
fin.open("user.dat",ios::binary);
if(fout)
{
    while(fin.read((char*)&b,sizeof(b)))
      {
            if(b.user_id()==q)
          {
            cout<<endl<<"Enter trip for user "<<endl;
            b.trip();
            fout.write((char*)&b,sizeof(b));
            flag=1;
          }
      }
}
if(flag==0)
{
    cout<<"User not found !!"<<endl;
}
else
    cout<<endl<<"Trip added :) "<<endl;
fin.close();
fout.close();
}

void file::show_users()
{
    int flag=0;
fin.open("user.dat",ios::binary|ios::app);
while(fin.read((char*)&b,sizeof(b)))
{
    b.show();
    flag=1;
}
if(flag==0)
{
    cout<<endl<<"No users in the list "<<endl<<endl;
}
fin.close();
}

void file::user_d()
{
  int iq,flag=0,p=0;
  cout<<endl<<"Enter the user ID : "<<endl;
  cin>>iq;
  fin.open("user.dat",ios::binary|ios::app);
  while(fin.read((char*)&b,sizeof(b)))
    {
   if(b.user_id()==iq)
   {
      b.show();
      flag=1;
   }
    }
    if(flag==0)
    {
        cout<<endl<<"User not found !! "<<endl;
    }
    fin.close();
    fin.open("trips.dat",ios::binary|ios::app);
    while(fin.read((char*)&b,sizeof(b)))
     {
    if(b.user_id()==iq)
      {
          b.show_trip();
          p=1;
      }
     }
     if(p==0&&flag==1)
     {
         cout<<endl<<"No current trip for user! "<<endl;
     }
fin.close();
}

void file::delete_user()
{
    int id,flag=0;
    fin.open("user.dat",ios::binary);
    fout.open("temp.dat",ios::binary);
    cout<<endl<<"Enter user's ID you want to delete :  ";
    cin>>id;

     while(fin.read((char*)&b,sizeof(b)))
    {
        if(id!=b.user_id())
        {
            fout.write((char*)&b,sizeof(b));
        }
        else
              flag=1;
    }
   if(flag==0)
    {
        cout<<endl<<"Invalid User ID " <<endl<<endl;
    }
    else
    {
        cout<<endl<<"User deleted "<<endl<<endl;
    }
    fin.close();
    fout.close();
    remove("user.dat");
    rename("temp.dat","user.dat");
}

void file::edit_user()
{
    int id,flag=0;
    fin.open("user.dat",ios::binary);
    fout.open("temp.dat",ios::binary|ios::app);
    cout<<endl<<"Enter user id whose data you want to modify "<<endl;
    cin>>id;
    while(fin.read((char*)&b,sizeof(b)))
    {
        if(id==b.user_id())
        {
            fin.seekg(-1*sizeof(b),ios::cur);
            b.new_user();
            flag=1;
        }
        fout.write((char*)&b,sizeof(b));
    }
    if(flag==0)
    {
        cout<<"Invalid user ID "<<endl;
    }
    else
        cout<<endl<<"User details modified "<<endl;
    fin.close();
    fout.close();
    remove("user.dat");
    rename("temp.dat","user.dat");
}
int main()
{
    int i;
    char ch;
  file a;
   do
   {
     cout<<"                        *HOMEPAGE*  "<<endl<<endl;
     cout<<"                ________________________________  "<<endl<<endl;
     cout<<"               |  1.     New User.              |"<<endl<<endl;
     cout<<"               |  2.     New trip.              |"<<endl<<endl;
     cout<<"               |  3.     All user information.  |"<<endl<<endl;
     cout<<"               |  4.     Edit User.             |"<<endl<<endl;
     cout<<"               |  5.     Delete User.           |"<<endl<<endl;
     cout<<"               |  6.     search  User details.  |"<<endl<<endl;
     cout<<"               |________________________________|"<<endl<<endl;
     cout<<" Enter your choice :  ";
     cin>>i;
     switch(i)
     {
         case 1: a.add_user();
         break;
         case 2: a.new_trip();
         break;
         case 3: a.show_users();
         break;
         case 4: a.edit_user();
         break;
         case 5: a.delete_user();
         break;
         case 6: a.user_d();
         break;
         default: cout<<"Invalid choice. "<<endl;
         break;
     }
     cout<<endl<<"Do you want to continue ? "<<endl;
     cin>>ch;
     cout<<endl<<endl;
   }while(ch=='y'||ch=='Y');
   cout<<endl<<"Thank You for choosing us. "<<endl;
    return 0;
}