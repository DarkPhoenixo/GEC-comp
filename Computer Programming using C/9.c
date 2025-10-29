#include<stdio.h> 

int main () {

int mk,n,countnumber ;

printf ("Enter your mk kid : \n") ;
scanf ("%d",&mk) ;


if (mk>80) {
    printf ( "Wow!  You have earned a 'A' grade,you are the future of this countnumberry" ) ;
} else if (mk>60 ) {
     printf ( "Tough luck ,You have earned a 'B' grade,next time aim for A" ) ;
} else if (mk>40 )  {
     printf ( "decent ! You have earned a 'C' grade,Certianly it can get better than this" ) ;
}else if (mk < 40) {
     printf ( " You have failed your exams you fucking moron,deposit $15000 in my bank accountnumber asap to remain in this college" ) ;
}



    return 0 ;
}