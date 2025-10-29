#include <iostream>
using namespace std ;

class test {
    private:
    int f ;
    public:
    test(){
        f=0 ;
    }
    test(int p){
        f=p ;
    }
void operator++(){              //Unary postfix increment
    f = f+1;
}
void operator++(int){          //Unary prefix increment
    f = f+1;
}
void operator--(){             //Unary postfix  decrement
    f= f-1;
}
void operator--(int){         //Unary postfix increment
    f = f-1;
}

void display(){
    cout << " "<<f<<endl;
}

friend test operator +(int i,test &d) ;
friend test operator -(int i,test &d) ;
};

 test operator +(int i,test &d) {
    test temp;
    temp.a = d.a+i;
    return temp ;

}

 test operator -(int i,test &d) {
    test temp;
    temp.a = d.a+i;
    return temp ;

}

int main (){
test t1(10) ;
test t2(30);


    return 0 ;
}