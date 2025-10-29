#include <stdio.h>
#include<math.h>

int main () {

int a=1,product=1,j=0;
 printf ( " Enter the number of which you want to find the product \n") ;



while (100>=a){
if(a%2==1) { 
j = j +1 ;
printf ("There are %d odd numbers \n",j) ;
 product = product * a ;
 printf (" The product for first %d th odd numbers is %d \n",j,product) ; 
} else {}
    a++ ;
}




    return 0 ;
}