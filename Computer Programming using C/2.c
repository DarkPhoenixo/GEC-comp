// Swap twonumbers without using any temperary variables 

#include <stdio.h> 

int main () {

int a,b ;

printf ( " Enter the value of a and b here : \n") ;
scanf ("%d %d",&a,&b);
printf("the value of a is : %d\n",a) ;
printf ("The value of b is : %d \n",b) ;

a=a+b ;
b=a-b ;
a=a-b ;

printf ( " The value of a after swapping is :%d \n",a) ;
printf (" the value of b after reswapping is %d \n",b) ;




    return 0 ;
}