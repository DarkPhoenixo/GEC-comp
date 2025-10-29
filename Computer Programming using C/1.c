
// Swapping of numbers using temperary variables 


#include <stdio.h> 

int main () {

int a,b,c ;
printf ( " Enter the value of a and b here : \n") ;
scanf ("%d %d",&a,&b) ;
printf ( "The value of a is %d \n",a) ;
printf ( " The value of b is :%d \n",b) ;

c=a;
a=b;
b=c ;

printf ( " a = %d \n  b = %d \n",a,b) ;




    return 0 ;
}