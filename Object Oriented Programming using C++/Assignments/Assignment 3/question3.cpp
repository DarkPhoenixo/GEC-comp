#include <iostream>
#include <cstring>
using namespace std ;

class student {
char *name ;
int roll_no ;
public :
student (){
name = new char[1] ;
name[0] = '\0' ;
roll_no = 0 ;
}
student (char *n , int r) {
name = new char[strlen(n)+1] ;
strcpy(name , n) ;
roll_no = r ;
}
void display (){
    cout << "Name : " << name << endl ;
    cout << "Roll No : " << roll_no << endl ;
}
~student (){
    delete[] name ; 
}};

class test : public student {
int sub1_marks , sub2_marks ;
int sub1_max , sub2_max ;
public :
test () : student() {
sub1_marks = 0 ;
sub2_marks = 0 ;
sub1_max = 100 ;
sub2_max = 100 ;
} 
test (char *n , int r , int s1 , int s2, int max1, int max2) : student(n , r) {
sub1_marks = s1 ;
sub2_marks = s2 ;
sub1_max = max1 ;
sub2_max = max2 ;
}
void display (){
    student::display() ;
    cout << "Subject 1 Marks : " << sub1_marks <<"/"<<sub1_max<< endl ;
    cout << "Subject 2 Marks : " << sub2_marks <<"/"<<sub2_max << endl ;
}
~test (){
}
};

class result : public test {
int total ;
int max ;
float percentage ;
public :
result () : test() {
    total = 0 ;
    max = 200 ;
    percentage = 0 ;
}
result (char *n , int r , int s1 , int s2 , int max1 ,int max2 ) : test(n , r , s1 , s2, max1, max2) {
    total = s1 + s2 ;
    max = max1 + max2 ;
    percentage = (total*100)/max ;
}
void display (){
    cout << "\n\n***************RESULT***************" << endl ;
    test::display() ;
    cout << "Total Marks : " << total<<"/"<<max<< endl ;
    cout << "Percentage : " << percentage << "%" << endl ;
    cout << "***********************************" << endl ;
}
~result (){
}
};

int main() {
    cout <<"\n\nEnter number of students : " ;
    int num ;
    cin >> num ;
    for (int i = 0 ; i < num ; i++) {
        cout << "\nEnter details for student " << i+1 << " : " << endl ;
        char n[20] ;
        int r , s1 , s2, max1 , max2 ;
        cout << "Enter name of student : " ;
        cin.ignore() ;
        cin.getline(n , 20) ;
        cout << "Enter roll number of student : " ;
        cin >> r ;
        cout << "Enter marks of subject 1 : " ;
        cin >> s1 ;
        cout << "Enter maximum marks of subject 1 : " ;
        cin >> max1 ;
        cout << "Enter marks of subject 2 : " ;
        cin >> s2 ;
        cout << "Enter maximum marks of subject 2 : " ;
        cin >> max2 ;
        result r1(n , r , s1 , s2 ,max1 , max2) ;
        r1.display() ;
    }
    return 0;
}