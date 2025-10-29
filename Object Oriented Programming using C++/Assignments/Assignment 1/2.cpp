#include <iostream>
#include <string>
using namespace std;

struct consumer {
    string name;
    int bl;
    float bill;
};

float elecbilla(int units);
float elecbillb(int units);
float elecbillc(int units);

int main() {
    struct consumer s[3];
   
    for (int i = 0; i < 3; i++) {
        cout << "Enter the name of the user \n";
        getline(cin, s[i].name);
        cout << "Enter the units of energy consumed by the user \n";
        cin >> s[i].bl;
        
        cin.ignore(); 

        if (s[i].bl <= 100) {
            s[i].bill = elecbilla(s[i].bl);
        } else if (s[i].bl > 100 && s[i].bl <= 300) {
            s[i].bill = elecbillb(s[i].bl);
        } else if (s[i].bl > 300) {  
            s[i].bill = elecbillc(s[i].bl);
        }

        if (s[i].bill > 300) {
            s[i].bill += (0.15 * s[i].bill);
        }
    }

    for (int i = 0; i < 3; i++) {
        cout << "==============Electricity Bill========================" << endl;
        cout << "Mr " << s[i].name << endl;
        cout << "Units of Electricity consumed  " << s[i].bl << endl;
        cout << "Charge Rs. " << s[i].bill << endl;
        cout << "===========================================================" << endl;
        cout << endl;
    }
    return 0;
}

float elecbilla(int units) {
    float bill = (units * 0.60) + 50;
    return bill;
}

float elecbillb(int units) {
    int un = units - 100;
    float bill = (100*0.60) + (un * 0.80);
    return bill;
}

float elecbillc(int units) {
    int un = units - 300;
    float bill = (100 * 0.60) + (200 * 0.80) + (un * 0.90);
    return bill;
}
