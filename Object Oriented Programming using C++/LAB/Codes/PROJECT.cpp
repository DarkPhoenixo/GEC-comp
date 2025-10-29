#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

void appendPrice(const string& filename, double price) {
    ofstream outFile(filename, ios::app);
    if (outFile) {
        outFile << price << endl;
        cout << "Price appended successfully." << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
}

void createBookRecord(const string& bookID, const string& bookName, const string& author, int bookNo) {
    ofstream outFile(bookID + ".txt");
    if (outFile) {
        outFile << "Book Name: " << bookName << endl;
        outFile << "Book Number: " << bookNo << endl;
        outFile << "Author: " << author << endl;
        cout << "Book record created successfully." << endl;
    } else {
        cout << "Unable to create book record." << endl;
    }
}

void displayBookRecord(const string& bookID) {
    ifstream inFile(bookID + ".txt");
    if (inFile) {
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
    } else {
        cout << "Unable to open book record." << endl;
    }
}

void editBookNumber(const string& bookID, int newBookNo) {
    string tempFile = bookID + "_temp.txt";
    ifstream inFile(bookID + ".txt");
    ofstream outFile(tempFile);
    if (inFile && outFile) {
        string line;
        while (getline(inFile, line)) {
            if (line.find("Book Number:") != string::npos) {
                outFile << "Book Number: " << newBookNo << endl;
            } else {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();
        remove((bookID + ".txt").c_str());
        rename(tempFile.c_str(), (bookID + ".txt").c_str());
        cout << "Book number updated successfully." << endl;
    } else {
        cout << "Unable to edit book record." << endl;
    }
}

vector<string> listTxtFiles() {
    vector<string> txtFiles;
    system("dir /b *.txt > temp.txt");
    ifstream inFile("temp.txt");
    if (inFile) {
        string filename;
        while (getline(inFile, filename)) {
            txtFiles.push_back(filename);
        }
        inFile.close();
        remove("temp.txt");
    }
    return txtFiles;
}

void displayAllBooks() {
    vector<string> txtFiles = listTxtFiles();
    for (const string& filename : txtFiles) {
        ifstream inFile(filename);
        if (inFile) {
            cout << "File: " << filename << endl;
            string line;
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            cout << endl;
        } else {
            cout << "Unable to open file: " << filename << endl;
        }
    }
}

void deleteAllFiles() {
    vector<string> txtFiles = listTxtFiles();
    for (const string& filename : txtFiles) {
        if (remove(filename.c_str()) == 0) {
            cout << "Deleted file: " << filename << endl;
        } else {
            cout << "Unable to delete file: " << filename << endl;
        }
    }
}

int main() {
    int choice;
    string bookID, bookName, author;
    int bookNo;
    double price;

    do {
        cout << "Menu:\n";
        cout << "1. Enter book details\n";
        cout << "2. Edit book number\n";
        cout << "3. Append price to book file\n";
        cout << "4. Display all books\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book ID: ";
                cin >> bookID;
                cout << "Enter book name: ";
                cin.ignore();
                getline(cin, bookName);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter book number: ";
                cin >> bookNo;
                cout << "Enter price: ";
                cin >> price;
                createBookRecord(bookID, bookName, author, bookNo);
                appendPrice(bookID + ".txt", price);
                displayBookRecord(bookID);
                break;
            case 2:
                cout << "Enter book ID: ";
                cin >> bookID;
                cout << "Enter new book number: ";
                cin >> bookNo;
                editBookNumber(bookID, bookNo);
                displayBookRecord(bookID);
                break;
            case 3:
                cout << "Enter book ID: ";
                cin >> bookID;
                cout << "Enter price: ";
                cin >> price;
                appendPrice(bookID + ".txt", price);
                displayBookRecord(bookID);
                break;
            case 4:
                displayAllBooks();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            case 6:
                deleteAllFiles();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
