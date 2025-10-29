#include <iostream>
#include <fstream>
#include <string>
#include <limits>  // For numeric_limits

using namespace std;

class Student {
public:
    string name;
    int rollNo;
    string address;
    string branch;

    void getData() {
        cout << "Enter name: ";
        cin.ignore();  // Ignore buffer before getline after using cin
        getline(cin, name);
        cout << "Enter roll number: ";
        cin >> rollNo;
        cin.ignore();  // Ignore buffer before getline
        cout << "Enter address: ";
        getline(cin, address);
        cout << "Enter branch: ";
        getline(cin, branch);
    }

    void displayData() {
        cout << "Name: " << name << endl;
        cout << "Roll Number: " << rollNo << endl;
        cout << "Address: " << address << endl;
        cout << "Branch: " << branch << endl;
    }

    string getFileName() {
        return to_string(rollNo) + ".txt";  // File now named based on roll number
    }

    void saveToFile() {
        ofstream file(getFileName());
        if (file) {
            file << name << endl;
            file << rollNo << endl;
            file << address << endl;
            file << branch << endl;
            file.close();
            cout << "Student data saved successfully.\n\n" << endl;
        } else {
            cout << "Error saving student data!" << endl;
        }
    }

    void loadFromFile(string fileName) {
        ifstream file(fileName);
        if (file.is_open()) {
            getline(file, name);
            string rollNoStr;
            getline(file, rollNoStr);
            rollNo = stoi(rollNoStr);
            getline(file, address);
            getline(file, branch);
            file.close();
        } else {
            cout << "File not found!" << endl;
        }
    }
};

void updateStudentDetails(int rollNo) {
    string fileName = to_string(rollNo) + ".txt";

    Student student;
    student.loadFromFile(fileName);

    if (student.rollNo == rollNo) {
        cout << "Current details:" << endl;
        student.displayData();
        cout << "Enter new details:" << endl;
        student.getData();
        student.saveToFile();
        cout << "Details updated successfully." << endl;
    } else {
        cout << "Roll number does not match!" << endl;
    }
}

void searchStudentDetails(int rollNo) {
    string fileName = to_string(rollNo) + ".txt";

    Student student;
    student.loadFromFile(fileName);

    if (student.rollNo == rollNo) {
        student.displayData();
    } else {
        cout << "Roll number does not match!" << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "1. Add Student" << endl;
        cout << "2. Search Student" << endl;
        cout << "3. Update Student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Student student;
                student.getData();
                student.saveToFile();
                break;
            }
            case 2: {
                int rollNo;
                cout << "Enter roll number to search: ";
                cin >> rollNo;
                searchStudentDetails(rollNo);
                break;
            }
            case 3: {
                int rollNo;
                cout << "Enter roll number to update: ";
                cin >> rollNo;
                updateStudentDetails(rollNo);
                break;
            }
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 4);

    return 0;
}
