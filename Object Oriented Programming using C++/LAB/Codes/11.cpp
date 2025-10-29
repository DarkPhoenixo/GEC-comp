#include <iostream>
#include <cmath>
using namespace std;

class polar ;
class Rectangular {
float x ;
float y ;
public :
Rectangular operator +(Rectangular &a){
Rectangular tmp ;
tmp.x = x+a.x ;
tmp.y=y+a.y ;
return tmp ;
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
    r = (a.x*a.x) + (a.y*a.y) ;
    r = sqrt(r) ;
    ang = a.x/a.y ;
    ang = atan(ang) ;   //atan() function is used to calculate tan inverse of a function
    b.radius = r ;
    b.angle = ang ;
}
void polrtorect (Rectangular &a,polar &b){
  a.x = (b.radius)*(cos(b.angle)) ;
  a.y = (b.radius)*(sin(b.angle)) ;
}

int main (){
polar P,Q,R;
Rectangular A,B,C ;
P.getvalue() ;
Q.getvalue() ;
polrtorect(A,P) ;
polrtorect(B,Q) ;
C = A+B ;
recttopolar(C,R) ;
R.display();
    return 0; 

}