#include <iostream>
using namespace std;

// Class template for a generic vector
template <typename T>
class Vector {
    T* arr;
    int size;
public:
    // Constructor to create the vector
    Vector(int s) {
        size = s;
        arr = new T[size];
        for (int i = 0; i < size; i++) {
            arr[i] = 0; // Initialize elements to 0
        }
    }

    // Function to modify the value of a given element
    void modifyElement(int index, T value) {
        if (index >= 0 && index < size) {
            arr[index] = value;
        } else {
            cout << "Index out of bounds!" << endl;
        }
    }

    // Function to display the vector elements
    void display() {
        for (int i = 0; i < size; i++) {

        }
        cout << endl;
    }

    // Destructor to free the allocated memory
    ~Vector() {
        delete[] arr;
    }
};

int main() {
    int n;
    cout << "Enter the size of the vector: ";
    cin >> n;

    // Create a vector of integers
    Vector<int> vecInt(n);
    // Create a vector of floats
    Vector<float> vecFloat(n);

    int choice;
    do {
        // Display the menu
        cout << "\nMenu:\n";
        cout << "1. Modify an integer element\n";
        cout << "2. Display the integer vector\n";
        cout << "3. Modify a float element\n";
        cout << "4. Display the float vector\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int index;
                int value;
                cout << "Enter the index of the element to modify: ";
                cin >> index;
                cout << "Enter the new value: ";
                cin >> value;
                vecInt.modifyElement(index, value);
                break;
            }
            case 2:
                cout << "Integer vector elements: ";
                vecInt.display();
                break;
            case 3: {
                int index;
                float value;
                cout << "Enter the index of the element to modify: ";
                cin >> index;
                cout << "Enter the new value: ";
                cin >> value;
                vecFloat.modifyElement(index, value);
                break;
            }
            case 4:
                cout << "Float vector elements: ";
                vecFloat.display();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please choose again.\n";
        }
    } while (choice != 5);

    return 0;
}