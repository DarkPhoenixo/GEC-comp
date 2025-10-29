#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

void sinfunc() {
    int n;
    float sinx = 0, x;

    cout << "Enter the number of terms you want in the series\n";
    cin >> n;
    cout << "Enter the value of x\n";
    cin >> x;

    for (int i = 0; i < n; i++) {
        float term = pow(x, 2 * i + 1);
        float fact = 1;
        for (int j = 1; j <= 2 * i + 1; j++) {
            fact *= j;
        }
        if (i % 2 == 0) {
            sinx += term / fact;
        } else {
            sinx -= term / fact;
        }
    }

    cout << "The value of sin x = x - (x^3/3!) + (x^5/5!) - (x^7/7!) + ... till "
         << n << " terms is " << fixed << setprecision(4) << sinx << endl;
    return;
}

void sum() {
    int n;
    float sum = 0;

    cout << "Enter the number of terms you want in the series\n";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        float term = pow(1.0 / i, i);
        sum += term;
    }

    cout << "The value of SUM = 1 + (1/2)^2 + (1/3)^3 + (1/4)^4 + ... till "
         << n << " terms is " << fixed << setprecision(4) << sum << endl;
    return;
}

int main() {
    int choice;
    do {
        cout << "\n\nEnter the operation you want to perform\n";
        cout << "1. sin x = x - (x^3/3!) + (x^5/5!) - (x^7/7!) + ...\n";
        cout << "2. SUM = 1 + (1/2)^2 + (1/3)^3 + (1/4)^4 + ...\n";
        cout << "3. Quit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                sinfunc();
                break;
            case 2:
                sum();
                break;
            case 3:
                break;
            default:
                cout << "Enter a valid option\n";
                break;
        }
    } while (choice != 3);
    return 0;
}
