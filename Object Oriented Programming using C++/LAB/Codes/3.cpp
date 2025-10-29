//Check if number is prime or not and even or not
#include<iostream>
using namespace std ;

int main (){
int n ;
cout<<"Enter the number -"<<endl ;
cin>>n ;

if(n%2==1){
    cout<<"The Entered number is odd \n";
}else {cout<<"The Entered number is even \n";}

if(n==2){
    cout<<"The Number is prime \n";
    return 0;
}else for(int i=2;i<n;i++){
    if (n%i==0){
        cout <<"The number is not a prime number"<<endl ;
        return 0 ;
    }
}
cout<<"The number is a prime number" ;
    return 0 ;
}