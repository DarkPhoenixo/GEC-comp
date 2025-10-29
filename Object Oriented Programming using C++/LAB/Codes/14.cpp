#include <iostream>
#include <string>
using namespace std ;

class Account {
protected :
string consumer_name ;
int acc_num ;
string type ;
public :
Account()
{
 consumer_name ='/0' ;
acc_num=000000000 ;
type = '0';}
Account(string s,int j,string k){
{
 consumer_name =s ;
acc_num=j ;
type = k;}
}

};

class saving_acc :public Account {
protected :int withdraw ;
saving_acc(int i):Account(i) {



}


}

int main (){






    return 0 ;
}