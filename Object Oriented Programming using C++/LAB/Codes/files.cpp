#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 1000;

void writeToFile(const string& filename, int data[], int size) {
    ofstream outFile(filename);
    for (int i = 0; i < size; ++i) {
        outFile << data[i] << " ";
    }
    outFile.close();
}

int readFromFile(const string& filename, int data[]) {
    ifstream inFile(filename);
    int num, size = 0;
    while (inFile >> num && size < MAX_SIZE) {
        data[size++] = num;
    }
    inFile.close();
    return size;
}

void displayMenu() {
    cout << "Menu:\n";
    cout << "1. Write to file\n";
    cout << "2. Read from file\n";
    cout << "3. Merge files\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int file1Data[MAX_SIZE], file2Data[MAX_SIZE], mergedData[2 * MAX_SIZE];
    string filename;
    int choice, size1, size2, mergedSize;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter filename: ";
                cin >> filename;
                cout << "Enter numbers (end with -1): ";
                size1 = 0;
                int num;
                while (cin >> num && num != -1 && size1 < MAX_SIZE) {
                    file1Data[size1++] = num;
                }
                writeToFile(filename, file1Data, size1);
                break;

            case 2:
                cout << "Enter filename: ";
                cin >> filename;
                size1 = readFromFile(filename, file1Data);
                cout << "Data from " << filename << ": ";
                for (int i = 0; i < size1; ++i) {
                    cout << file1Data[i] << " ";
                }
                cout << endl;
                break;

            case 3:
                cout << "Enter first filename: ";
                cin >> filename;
                size1 = readFromFile(filename, file1Data);
                cout << "Enter second filename: ";
                cin >> filename;
                size2 = readFromFile(filename, file2Data);

                mergedSize = size1 + size2;
                copy(file1Data, file1Data + size1, mergedData);
                copy(file2Data, file2Data + size2, mergedData + size1);
                sort(mergedData, mergedData + mergedSize);

                cout << "Enter filename to save merged data: ";
                cin >> filename;
                writeToFile(filename, mergedData, mergedSize);
                break;

            case 4:
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}