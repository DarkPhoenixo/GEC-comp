#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class employee {
private :
int code ;
string name ;
float original_salary;
float incremented_salary ;

public :
void input(){
cout<<"Enter the five digit employee code\n";
cin>>code ;
 cin.ignore() ;
cout<<"Enter the name of the employee\n";
getline(cin,name) ;
cout <<"Enter the original salary of the employee\n" ;
cin>>original_salary ;
return ;
}
int perks(){
    int upd,n ;
    int sal = original_salary;
cout << "Enter number of perks \n ";
cin>>n ;
for (int i=1;i<=n;i++){
    cout <<"Perk "<<i<<"\n Enter the salary hike/decrease given by the company in Rs:";
    cin>>upd ;
sal +=upd ;  
}incremented_salary = sal ;
return 0 ;
}
int status(){
    if(incremented_salary>=50000){
        return 1 ;
    }
 return 0 ;  
}
void display(string state){
cout<<setw(6)<<code<<setw(25)<<name<<setw(17)<<original_salary <<setw(17)<< incremented_salary<<setw(10) <<state <<endl ;
}
};
int main (){
    int n ;
    string state[100] ;
employee s[100];
cout<<"Enter the number of employees\n";
cin>>n ;

for(int i=0;i<n;i++){
s[i].input() ;
s[i].perks() ;
if(s[i].status()){
state[i] = "Promoted" ;
}else {
state[i] = "Demoted" ;
}

}


cout << "\nEmployee Code   Employee Name    Original Salary   Incremented Salary   Status"<<endl ; 
for(int i=0;i<n;i++){
s[i].display(state[i]) ;
}
return 0 ;
}