#include <iostream>
using namespace std;

class Grandparents {
protected:
    
public:int property;
    void getval() {
        cout << "Enter the property grandparents had in Rs: ";
        cin >> property;
    }

    void display() {
        cout << "Grandparents have a property of Rs. " << property << endl;
    }

    int getProperty() {
        return property;
    }
};

class Parents : public Grandparents {
protected:
    
public:int property2;
    void inheritProperty() {
        property2 = property/2 ;
    }

    void display() {
        cout << "Parents have inherited a property of Rs. " << property2 << " from grandparents." << endl;
        return property2;
    }
};

class Child : public Parents {
protected:
   
public: int property3;
    void inheritProperty() {
        property3 = property2 ;
    }

    void display() {
        cout << "The child will inherit a property of Rs. " << property3 << " from parents." << endl;
    }
};

int main() {
    Grandparents Gi;
    Gi.getval();

    Parents Pi;
    Pi.inheritProperty();

    Child Ci;
    Ci.inheritProperty();
    Gi.display();
    Pi.display();
    Ci.display();

    return 0;
}

