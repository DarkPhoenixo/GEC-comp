 #include <iostream>
 using namespace std ;
 int main(){
int n ;
cout <<"Enter the number of elements of the array --\n";
cin>>n;
int arr[50];
cout <<"Enter the elements of the array \n";
for (int i=0;i<n;i++){
cin>>arr[i];
}
int high = arr[0];
int low = arr[0];
for(int i=0;i<n;i++){
    if(arr[i]<low){
        low = arr[i];
    }
      if(arr[i]>high){
        high = arr[i];
    }
}
cout <<"The highest element in the array is " <<high<<" and the lowest element in the array is "<<low<<endl ;


    return 0;
 }