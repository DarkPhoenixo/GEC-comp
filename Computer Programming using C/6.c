//Calculate volume of cylinder 

#include <stdio.h>

int main () {
float radius ,height,volume ;
printf (" Enter the radius and height of the cylinder : \n") ;

scanf ("%f %f",&radius,&height) ;

printf (" The radius of the cylinder is %f units \n",radius) ;
printf (" The height of the cylinder is %f units \n",height) ;

volume = 3.14*radius*radius*height ;

printf (" The volume of the cylinder is %f cubic units \n",volume) ;

    return 0 ;
}