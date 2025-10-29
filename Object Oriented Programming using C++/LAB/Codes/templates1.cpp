#include <iostream>
using namespace std;

// Function template to swap two elements
template <typename T>
void swapElements(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 5, y = 10;
    cout << "Before swapping: x = " << x << ", y = " << y << endl;
    swapElements(x, y);
    cout << "After swapping: x = " << x << ", y = " << y << endl;

    double p = 5.5, q = 10.1;
    cout << "Before swapping: p = " << p << ", q = " << q << endl;
    swapElements(p, q);
    cout << "After swapping: p = " << p << ", q = " << q << endl;

    return 0;
}
