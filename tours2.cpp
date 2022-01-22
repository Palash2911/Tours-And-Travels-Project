#include <bits/stdc++.h>
#include <fstream>
#include <string.h>
#include <unistd.h>
using namespace std;
class tours
{
    char name[40];
    char add[100];
    char em[30];
    int id = 0;
    int tid = 0;
    int cost = 0;
    int d, y, m;
    char des[100];

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
    cout << endl<< "Enter Client name       :  ";
    cin.ignore();
    cin.getline(name, 40);
    cout << "Enter Client address    :  ";
    cin.getline(add, 100);
    cout << "Enter Client email-id   :  ";
    cin >> em;
    cout << "Enter Client ID         :  ";
    cin >> id;
}
void tours::trip()
{
    int i;
    cout<<endl << "Enter Trip Destination :  ";
    cin.ignore();
    cin.getline(des, 100);
    cout << "Enter Trip date(1-30) :  ";
    cin >> d;
    cout << "Enter Trip month (in numbers) :  ";
    cin >> m;
    cout << "Enter Trip year :  ";
    cin >> y;
    cout << "Enter total cost :  ";
    cin >> cost;
}
void tours::show()
{
    cout << endl<< "Client name       : " << name << endl;
    cout << "Client address    : " << add << endl;
    cout << "Client email-id   : " << em << endl;
    cout << "Client ID         : " << id << endl;
}
void tours::show_trip()
{
    int i;
    cout << endl<<"Trip Destination :  " << des << endl;
    cout << "Trip Date        : " << d << "/ " << m << "/ " << y << endl;
    cout << "Trip cost        : " << cost << endl;
}

int tours::user_id()
{
    return id;
}
void file::add_user()
{
    int i;
    tours p[5];
    fout.open("user.dat", ios::binary | ios::app);
    if (fout)
    {
        cout << endl<<"How many clients do you want to add (max=5) ?  " ;
        cin >> i;
        for (int j = 0; j < i; j++)
        {
            cout << endl<< "Client " << j + 1 << endl;
            p[i].new_user();
            fout.write((char *)&p[i], sizeof(p[i]));
            cout << "Data added " << endl;
        }
    }
    fout.close();
}

void file::new_trip()
{
    tours c;
    int q, flag = 0;
    fout.open("trips.dat", ios::binary | ios::app);
    cout << endl<< "Enter Client Id for whom you want to add a trip :  ";
    cin >> q;
    fin.open("user.dat", ios::binary);
    if (fout)
    {
        while (fin.read((char *)&b, sizeof(b)))
        {
            if (b.user_id() == q)
            {
                b.trip();
                fout.write((char *)&b, sizeof(b));
                flag = 1;
            }
        }
    }
    if (flag == 0)
    {
        cout << "Inavlid ID !!" << endl;
    }
    else
        cout << endl<< "Trip added :) " << endl;
    fin.close();
    fout.close();
}

void file::show_users()
{
    int flag = 0;
    fin.open("user.dat", ios::binary | ios::app);
    while (fin.read((char *)&b, sizeof(b)))
    {
        b.show();
        flag = 1;
    }
    if (flag == 0)
    {
        cout << endl<<"FILE EMPTY !! " << endl;
    }
    fin.close();
}

void file::user_d()
{
    int iq, flag = 0, p = 0;
    cout << endl<< "Enter the client ID : " ;
    cin >> iq;
    fin.open("user.dat", ios::binary | ios::app);
    while (fin.read((char *)&b, sizeof(b)))
    {
        if (b.user_id() == iq)
        {
            b.show();
            flag = 1;
        }
    }
    if (flag == 0)
    {
        cout << endl<<"Client ID not found !! " << endl;
    }
    fin.close();
    fin.open("trips.dat", ios::binary | ios::app);
    while (fin.read((char *)&b, sizeof(b)))
    {
        if (b.user_id() == iq)
        {
            b.show_trip();
            p = 1;
        }
    }
    if (p == 0 && flag == 1)
    {
        cout << endl<< "The Client has no trips yet !! " << endl;
    }
    fin.close();
}

void file::delete_user()
{
    int id, flag = 0;
    char ch;
    fin.open("user.dat", ios::binary);
    fout.open("temp.dat", ios::binary);
    cout << endl<< "Client user's ID you want to delete :  ";
    cin >> id;
    cout<<"ARE YOU SURE YOU WANT TO DELETE CLIENT INFO (y/n)?? ";
    cin>>ch;
    if(ch=='y')
    {
        cout<<endl<<"REQUEST ACCEPTED !! "<<endl<<endl;
        while (fin.read((char *)&b, sizeof(b)))
        {
            if (id != b.user_id())
            {
                fout.write((char *)&b, sizeof(b));
            }
            else
                flag = 1;
        }
        if (flag == 0)
        {
            cout << endl<< "Invalid Client ID " << endl<< endl;
        }
        else
        {
            cout << endl<< "Client INFO deleted :(" << endl<< endl;
        }
        fin.close();
        fout.close();
        remove("user.dat");
        rename("temp.dat", "user.dat");
    }
    else
    {
        cout<<endl<<"REQUEST ACCEPTED !! "<<endl<<endl;
    }
}

void file::edit_user()
{
    int id, flag = 0;
    fin.open("user.dat", ios::binary);
    fout.open("temp.dat", ios::binary | ios::app);
    cout << endl<< "Enter Client id whose data you want to modify " << endl;
    cin >> id;
    while (fin.read((char *)&b, sizeof(b)))
    {
        if (id == b.user_id())
        {
            fin.seekg(-1 * sizeof(b), ios::cur);
            b.new_user();
            flag = 1;
        }
        fout.write((char *)&b, sizeof(b));
    }
    if (flag == 0)
    {
        cout << "Invalid Client ID " << endl;
    }
    else
        cout << endl
             << "Client details modified " << endl;
    fin.close();
    fout.close();
    remove("user.dat");
    rename("temp.dat", "user.dat");
}
int main()
{
    int i, j, k;
    string ch, vr;
    file a;
    cout << endl<< endl<< "           Welcome to FUTURISTIC Tours And Travels " << endl<< endl<< endl;
    cout << "                ________________________________  " << endl<< endl;
    cout << "               |  1.     Physical Tour.         |" << endl<< endl;
    cout << "               |  2.     Virtual Tour.          |" << endl<< endl;
    cout << "               |________________________________|" << endl<< endl;
    cout << "Your Choice :  ";
    cin >> j;
    if (j == 2)
    {
        cout << "A Virtual Headset :   Rs. 4000 " << endl;
        cout << "Do you want to Order ?  ";
        cin >> vr;
        if (vr == "Yes" || vr == "yes")
        {
            cout << "How many Headset do you want to Order :  ";
            cin >> k;
            cout << "Your Total Amount is  " << k * 4000 << endl;
            cout << "Your Order Will be with you soon :)  " << endl;
        }
    }
    do
    {
        sleep(1);
        cout << endl<< "                       *HOMEPAGE*  " << endl<< endl;
        cout << "                ________________________________  " << endl<< endl;
        cout << "               |  1.     New User.              |" << endl<< endl;
        cout << "               |  2.     New trip.              |" << endl<< endl;
        cout << "               |  3.     All user information.  |" << endl<< endl;
        cout << "               |  4.     Edit User.             |" << endl<< endl;
        cout << "               |  5.     Delete User.           |" << endl<< endl;
        cout << "               |  6.     Search  User details.  |" << endl<< endl;
        cout << "               |  7.     EXIT                   |" << endl<< endl;
        cout << "               |________________________________|" << endl<< endl;
        cout << " Enter your choice :  ";
        cin >> i;
        switch (i)
        {
        case 1:
            a.add_user();
            break;
        case 2:
            a.new_trip();
            break;
        case 3:
            a.show_users();
            break;
        case 4:
            a.edit_user();
            break;
        case 5:
            a.delete_user();
            break;
        case 6:
            a.user_d();
            break;
        case 7:
            break;
        default:
            cout << "Invalid choice. " << endl;
            break;
        }
        cout << endl
             << endl;
    } while (i != 7);
    cout << endl<< "Thank You for choosing us :))) " << endl<< endl;
    return 0;
}
