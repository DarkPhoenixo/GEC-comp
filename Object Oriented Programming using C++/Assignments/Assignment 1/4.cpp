#include <iostream>
using namespace std ;

int main(){
int i,j;
cout<<"Enter the number of rows and columns in the matrix"<<endl;
cin>>i;
cin>>j;
 if (i != j) {
        cout << "Matrix must be square to interchange diagonals." << endl;
        return 1;
    }
int arr[10][10] ;
cout<<"Enter the elements of the matrix\n";
for(int a=0;a<i;a++){
    for (int b=0;b<j;b++){
        cin>>arr[a][b];
    }
}
cout << "The elements of the matrix are \n";
for(int a=0;a<i;a++){
    for (int b=0;b<j;b++){
            cout<<" "<<arr[a][b];}
    cout<<endl ;
}
   

for (int a =0;a<3;a++){
        int c = arr[a][a] ;
      arr[a][a] = arr[a][i-a-1];
      arr [a][i-a-1] = c ;
    
}
cout << "The elements of the matrix after diagonal interchanging are \n";
for(int a=0;a<i;a++){
    for (int b=0;b<j;b++){
            cout<<" "<<arr[a][b];}
    cout<<endl ;
}

    return 0;
}