#include <iostream>
#include <cstring>
using namespace std ;

class worker {
    protected :
    long int worker_id ;
    char *name ;
    char *address ;
    float salary ;
    char *supervisor_id ;
    char *department_id ;

    public :
    worker (){
        worker_id = 0 ;
        name = new char[20] ;
        address = new char[20] ;
        salary = 0 ;
        supervisor_id = new char[20] ;
        department_id = new char[20] ;
    }
    void get_info (){
        cout << "Enter worker id : " ;
       cin >> worker_id ;
        cout << "Enter name : " ;
        char n[50] ;
        cin.ignore() ;
        cin.getline(n , 50) ;
        name = new char[strlen(n)+1] ;
        strcpy(name , n) ;
        cout << "Enter address : " ;
        char a[50] ;
        cin.getline(a , 50) ;
        address = new char[strlen(a)+1] ;
        strcpy(address , a) ;
        cout << "Enter salary : " ;
        cin >> salary ;
        cout << "Enter supervisor id : " ;
        char s[50] ;
        cin.ignore() ;
        cin.getline(s , 50) ;
        supervisor_id = new char[strlen(s)+1] ;
        strcpy(supervisor_id , s) ;
        cout << "Enter department id : " ;
        char d[50] ;
        cin.getline(d , 50) ;
        department_id = new char[strlen(d)+1] ;
        strcpy(department_id , d) ;
}
virtual void display (){
    cout <<"\n\n-------WORKER DETAILS-------------\n" ;
    cout << "Worker id : " << worker_id << endl ;
    cout << "Name : " << name << endl ;
    cout << "Supervisor id : " << supervisor_id << endl ;
    cout<<"----------------------------------\n\n";
}

};

class supervisor :public worker {
public :
void display (){
    cout <<"\n\n-------SUPERVISOR DETAILS-------------\n" ;
    cout << "Name : "<< name <<endl ;
    cout << "Department ID "<<department_id << endl ;
    cout<<"----------------------------------\n\n";
}
};

int main(){
    worker *bptr ;
    int choice;
   
    cout << "Enter the position of the person" 
   <<" (1 for supervisor and 2 for worker)"<<endl ;
cin>>choice ;
if (choice==1){
    supervisor s ;
    bptr =&s ;
    bptr->get_info ();
    bptr->display() ;
}
else if (choice ==2){
    worker w ;
    bptr = &w ;
    bptr->get_info();
    bptr->display() ;
}
else {
    cout<<"Enter valid choice value\n";
}
return 0 ;
}