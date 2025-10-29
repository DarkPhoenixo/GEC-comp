//Using Friend functions to calculate distance between two points


#include <iostream>
#include <math.h>
using namespace std ;



class Point2 ; 
class Point1 {  
private :
int x ;
int y ;

public :
void input(){
cout << "Enter the x coordinates of the first point\n" ;
cin>>x ;
cout << "Enter the y coordinates of the first point\n" ;
cin>>y ;
return ;
}

friend float distance(Point1,Point2) ;   
};
class Point2 { 
private :
int x ;
int y ;   

public :
void input(){  
cout << "Enter the x coordinates of the second point\n" ;
cin>>x ;
cout << "Enter the y coordinates of the second point\n" ;
cin>>y ;
return ;
}
friend float distance(Point1,Point2) ;   
};

float distance (Point1 p1,Point2 p2){     
int i=p1.x;              
int j =p1.y ;        
int k =p2.x;
int l =p2.y;
int xm = i-k ;
 xm = xm*xm ;
int ym = j-l ;
ym = ym*ym ;
 float distance = xm + ym ;
distance = sqrt(distance) ;
return distance ;
}
int main (){
Point1 p1 ;
Point2 p2 ;
p1.input() ;
p2.input() ;
cout <<"The distance between two points is "<<distance(p1,p2) <<" Units"<<endl ;
    return 0 ;
}

