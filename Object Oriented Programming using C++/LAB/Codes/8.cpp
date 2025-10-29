#include <iostream>
#include <cstring>  
using namespace std;

class String {
private:
    char *p;
    int length;

public:
    // Default constructor
    String() {
        p = new char[1];
        p[0] = '\0';  // Initialize with an empty string
        length = 0;
    }
    // Parameterized constructor
    String(const char *str) { 
        length = strlen(str);
        p = new char[length + 1];  // Allocate memory for the string
        strcpy(p, str);  // Copy the string
    }
    // Concatenation of two String objects
    void join(const String &s1, const String &s2) {
        length = s1.length + s2.length;
        p = new char[length + 1];  // Allocate memory for the concatenated string
        strcpy(p, s1.p);  // Copy the first string
        strcat(p, s2.p);  // Concatenate the second string
    }
    // Displaying the string
    void display()  {
        cout << "The desired string is: " << p << endl;
    }
    // Destructor to free allocated memory
    ~String() {
        delete[] p;
    }
};

int main() {
    String s1;

    char s[50];
    cout << "Enter a desired string: ";
    cin.getline(s, 50);
    String s2(s);

    cout << "Enter a desired string: ";
    cin.getline(s, 50);
    String s3(s);
    String s4 ;
    s4.join(s2, s3);
    s4.display();
    // Destructors will be called automatically here when objects go out of scope
    return 0;
}

