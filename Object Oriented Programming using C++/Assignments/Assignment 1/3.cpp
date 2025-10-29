#include <iostream>
using namespace std ;

int main (){
int i,j,k,n,first,second,next ;
cout << "Enter the number of rows of the fibonacci pattern needed"<<endl ;
cin>>n;
cout<<"Pattern"<<endl ;

for(i=0;i<n;i++){
    next = 0;
    first=0 ;
    second =1 ;
    for(j=0;j<=i;j++){
      
            if(j==0){
                cout<<" "<<second;}
            else {
                next = first + second;
              first = second;
              second = next ;
                 cout<<" "<<next;
            
            }
            
        }
        cout<<endl ;
    }
}