#include <iostream>
using namespace std;

class Resource {
private:
    int *data;
public:
    Resource(int value) {
        data = new int;
        *data = value;
        cout << "Constructor called, value: " << *data << endl;
    }
    ~Resource() {
        delete data;
        cout << "Destructor called" << endl;
    }
    void display() {
        cout << "Value: " << *data << endl;
    }};

int main() {
    int userInput;
    cout << "Enter a value: ";
    cin >> userInput;
    Resource res1(userInput);
    res1.display();
    cout << "Enter another value: ";
    cin >> userInput;
    Resource res2(userInput);  
    res2.display();

    return 0;  // Destructors for res1 and res2 called when going out of scope
}



