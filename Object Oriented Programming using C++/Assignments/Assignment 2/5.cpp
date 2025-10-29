#include <iostream>
using namespace std ;

void matrix (){
int c,r,t;
cout<<"Enter the number of rows and columns\n" ;
cin>>r ;
cin>>c ;
int **p = new int*[r] ;
for(int i=0;i<r;i++){
    p[i]=new int[c];
}
cout <<"Enter the matrix elements\n";
for(int i=0;i<r;i++){
for(int j=0;j<c;j++){
cin>>t ;
p[i][j]=t ;
}
}

cout <<"The matrix is: \n";
for(int i=0;i<r;i++){
    cout<<"|" ;
for(int j=0;j<c;j++){
cout<<" "<<p[i][j];
}
cout<<" |" ;
cout<<endl ;
}
}

int main (){
matrix ();

    return 0 ;
}