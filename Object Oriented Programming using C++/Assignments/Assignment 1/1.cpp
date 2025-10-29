#include <iostream>
#include <string>
using namespace std ;

struct employee {
    string ename;
    int eid ;
    string eaddress ;
};

int main (){
   int n;
    cout << "Enter the number of employees ";
    cin>>n;
     cin.ignore();
    struct employee e[100];
for (int i=0;i<n;i++){
   
    cout << "Enter the  name of the employee"<<endl ;
    getline(cin,e[i].ename);
    
    cout << "Enter the ID number of the employee"<<endl ;
    cin>>e[i].eid ;
    cin.ignore();
    cout << "Enter the address of the employee"<<endl ;
    getline(cin,e[i].eaddress);
    
}cout<<endl ;

for (int i=0;i<n;i++){
cout<<"-----------------EMPLOYEE RECORD----------------------------------------"<<endl ;
cout<<"Employee name -> "<<e[i].ename<<endl ;
cout<<"Employee ID -> "<<e[i].eid <<endl ;
cout<< "Employee Address --> "<<e[i].eaddress<<endl ;
cout << endl ;
}
    int searchId;
    string searchAddress;
    cout << "Enter the ID of the employee you want to search: ";
    cin >> searchId;
    cin.ignore();
    cout << "Enter the address of the employee you want to search: ";
    getline(cin, searchAddress);

    bool found = false;
    for (int i = 0; i < n; i++) {
        if (e[i].eid == searchId && e[i].eaddress == searchAddress) {
            cout << "-----------------EMPLOYEE RECORD FOUND----------------------------------------" << endl;
            cout << "Employee name -> " << e[i].ename << endl;
            cout << "Employee ID -> " << e[i].eid << endl;
            cout << "Employee Address --> " << e[i].eaddress << endl;
            cout << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No employee record found with the given ID and address." << endl;
    }

    return 0;
}
    