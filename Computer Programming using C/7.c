#include <stdio.h>
int main () {
float n,m=1,a=0,square ;
printf ( "Enter the value of number till you want sum od squares here \n") ;
scanf ("%f",&n) ;
 a = 0 ;
 m = 1 ;


while (n>=m) {
square = m * m ;
a = a + square ;

m=m+1 ;
}
printf ("The value of square of numbers till %f is %f",n,a) ;

    return 0;
}