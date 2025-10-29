#include <iostream>
#include <cstring>
using namespace std ;

class account {
    protected :
long int account_no ;
char *costumer_name ;
char *account_type ;
float balance ;

public :
void get_info (){
    cout << "Enter account number : " ;
    cin >> account_no ;
    cout << "Enter costumer name : " ;
    char n[20] ;
    cin.ignore() ;
    cin.getline(n , 20) ;
    costumer_name = new char[strlen(n)+1] ;
    strcpy(costumer_name , n) ;
    cout << "Enter account type : " ;
    char t[20] ;
    cin.getline(t , 20) ;
    account_type = new char[strlen(t)+1] ;
    strcpy(account_type , t) ;
    cout << "Enter balance : " ;
    cin >> balance ;
}
void display (){
    cout << "Account number : " << account_no << endl ;
    cout << "Costumer name : " << costumer_name << endl ;
    cout << "Account type : " << account_type << endl ;
    cout << "Balance : " << balance << endl ;
}
void show_balance (){
   cout << "The bank account has a balance of Rs." << balance << endl ;
    
}
};

class savings : public account {

float interest_rate = 0.05 ;
int withdraw ;
int withdraw_limit = 100000 ;
int deposit ;
float time ;
int deposit_limit = 100000 ;

public :
void showinterest_rate (){
    cout << "The interest rate is " << interest_rate << endl ;}

 void oper (){

    cout << "Enter operations to be performed : " ;
    cout<<"Deposit limit is "<<deposit_limit<<" and withdraw limit is "<<withdraw_limit<<endl;
    cout << "Enter 1 for deposit and 2 for withdraw : " ;
    int choice ;
    cin >> choice ;
    if (choice == 1) {
        cout << "Enter amount to be deposited : " ;
        cin >> deposit ;
        if (deposit > deposit_limit) {
            cout << "Deposit limit exceeded" << endl ;
        }
        else {
            balance += deposit ;
            cout << "Amount deposited successfully" << endl ;
        }
    }
    else if (choice == 2) {
        cout << "Enter amount to be withdrawn : " ;
        cin >> withdraw ;
        if (withdraw > withdraw_limit) {
            cout << "Withdraw limit exceeded" << endl ;
        }
        else {
            balance -= withdraw ;
            cout << "Amount withdrawn successfully" << endl ;
        }
    }
    else {
        cout << "Invalid choice" << endl ;
    }
if(balance < 500 ){
    balance = balance - 100 ;
}
 }
void keep_balance (){
    cout << "Enter time in years for which balance is kept : " ;
    cin >> time ;
    balance += balance * interest_rate * time ;
    cout << "Balance after " << time << " years is : " << balance << endl ;
}
void display (){
cout <<"\n\n**********Account Details**********"<<endl;
account::display() ;
    cout << "Years amount is kept : " << time << " years" << endl ;
    cout << "Interest rate : " <<(interest_rate*100) <<" percent per year"<< endl ;
 cout << "****************************************" << endl ;  
  }
};

class current : public account {
    bool checkbook ;
    int issue ;
    int withdraw ;
    int deposit ;
   public :
   void issuecheckbook (){
         cout << "Enter 1 to issue checkbook : " ;
     cin>>checkbook ;
issue = 1 ;
       cout << "Checkbook issued successfully" << endl ;
   }
void oper (){
    cout << "Enter operations to be performed : " ;
    cout << "Enter 1 for deposit and 2 for withdraw : " ;
    int choice ;
    cin >> choice ;
    if (choice == 1) {
        cout << "Enter amount to be deposited using check : " ;
        cin >> deposit ;
        balance += deposit ;
        cout << "Amount deposited successfully using check" << endl ;
    }
    else if (choice == 2) {
        cout << "Enter amount to be withdrawn using check : " ;
        cin >> withdraw ;
        balance -= withdraw ;
        cout << "Amount withdrawn successfully using check" << endl ;
    }
    else {
        cout << "Invalid choice" << endl ;
    }
    if(balance < 500 ){
    balance = balance - 100 ;
}
}
void display (){
    cout <<"\n\n**********Account Details**********"<<endl;
    account::display() ;
 if (issue==1){
     cout << "Checkbook issued : Yes" << endl ;
 }
 else {
     cout << "Checkbook issued : No" << endl ;
 }
  cout << "****************************************" << endl ; 
}
};
    


int main() {
    int num,choice ;
cout<<"**********Bank Management System***********"<<endl;
cout<<"Enter number of accounts : " ;
cin >> num ;
for(int i = 0 ; i < num ; i++) {
    cout << "Enter details for account " << i+1 << " : " << endl ;
    cout << "Enter 1 for savings and 2 for current : " ;
    cin >> choice ;
    if (choice == 1) {
        savings s ;
        s.get_info() ;
        s.oper() ;
        s.keep_balance() ;
        s.display() ;
    }
    else if (choice == 2) {
        current c ;
        c.get_info() ;
        c.issuecheckbook() ;
        c.oper() ;
        c.display() ;
    }
    else {
        cout << "Invalid choice" << endl ;
    }
} 


    return 0;
}