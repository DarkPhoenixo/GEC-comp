#include <iostream>
#include <cmath>
using namespace std;

class polar ;
class Rectangular {
float x ;
float y ;
public :
void getvalue(){
cout << "Enter the x coordinates of the point \n" ;
cin >> x ;
cout << "Enter the y coordinates of the point \n" ;  
cin >> y ; 
}
void display(){
    cout << "The x coordinates of the point is : " << x << " units " <<
     "and the  y coordinates of the point is : " << y << " units " <<  endl;
}
void friend polrtorect (Rectangular &a,polar &b);
void friend recttopolar (Rectangular &a,polar &b);
};

class polar {
    float radius ;
    float angle ;
    public :
 void getvalue (){
cout <<"Enter the  radius the point makes from origin  \n" ;
cin>>radius ;
cout <<"Enter angle it is inclined from the origin \n" ;
cin>>angle;
}  
void display (){
    cout<<"The radius the point makes from origin is "<<radius<<" Units"<<" and it is inclined by "<<angle<<" radians"<<endl;
} 
void friend polrtorect (Rectangular &a,polar &b);
void friend recttopolar (Rectangular &a,polar &b);
};
void recttopolar (Rectangular &a,polar &b){
    float r,ang ;
    r = sqrt((a.x)*(a.x) + (a.y)*(a.y)) ;
    ang = atan(a.x/a.y) ;   //atan() function is used to calculate tan inverse of a function
    b.radius = r ;
    b.angle = ang ;
}
void polrtorect (Rectangular &a,polar &b){
  a.x = (b.radius)*(cos(b.angle)) ;
  a.y = (b.radius)*(sin(b.angle)) ;
}

int main (){
polar P,Q;
Rectangular A,B ;
P.getvalue() ;
cout <<"Converting polar to rectangular coordinates we get \n" ; 
polrtorect(A,P) ;
A.display();
B.getvalue() ;
cout <<"Converting rectangular to polar coordinates we get \n" ;
recttopolar(B,Q) ;
Q.display();
    return 0;
}