#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

// Base class for media types (Books in this case)
class media {
protected:
    string title;
public:
    virtual void display() = 0;  // pure virtual function for displaying media
};

// Book class that stores and manages book records
class Book : public media {
    string bno;        // book number (unique identifier)
    int pages;
    string author;
public:
    void createbook();  // function to create a book
    void editnumber(string);  // function to edit the book number
    void appendprice();  // function to append price
    void display();  // function to display the book details
    string getBookNumber() const {
        return bno; 
    }
    string getTitle() const {
        return title; 
    }
    // Friend function declaration
    friend void displaySensitiveInfo(const Book &b);  // Friend function to access private members
};

// Function to create a new book record and store in a file
void Book::createbook() {
    cout << "Enter book name: ";
    getline(cin, title);
    cout << "Enter book number or code: ";
    cin >> bno;
    cout << "Enter the number of pages: ";
    cin >> pages;
    cout << "Enter author name: ";
    cin.ignore();
    getline(cin, author);

    ofstream fout;
    string filename = bno + ".txt";  // file with book number as name
    fout.open(filename);    // Open a file in writing mode
    if (fout.is_open()) {
        fout << "Book name: " << title << endl;
        fout << "Book number: " << bno << endl;
        fout << "Number of pages: " << pages << endl;
        fout << "Author name: " << author << endl;
        cout << "Book file created successfully.\n";
        fout.close();
    } else {
        cout << "Error opening the file." << endl;
    }
}

// Function to edit the book number
void Book::editnumber(string new_no) {
    fstream file(bno + ".txt", ios::in | ios::out);
    string old = bno;
    bno = new_no;

    if (file.is_open()) {
        int s = title.size();
        file.seekp(s + sizeof("Book number: ") + sizeof("Book name: "));
        file << bno;
    }
    file.close();

    // Create a new file with updated book number
    fstream file2;
    file2.open(bno + ".txt", ios::out);
    file2 << "Book name: " << title << endl;
    file2 << "Book number: " << bno << endl;
    file2 << "Number of pages: " << pages << endl;
    file2 << "Author name: " << author << endl;
    file2.close();
    
    // Remove the old file
    string filename = old + ".txt";
    remove(filename.c_str());
}

// Function to append price to the book file
void Book::appendprice() {
    double price;
    cout << "Enter price of book: ";
    cin >> price;

    ofstream fout;
    string filename = bno + ".txt";
    fout.open(filename, ios::app);  // Open file in append mode
    if (fout.is_open()) {
        fout << "Price : Rs. " << price << endl;
        cout << "Price appended successfully." << endl;
        fout.close();
    } else {
        cout << "Error opening the file." << endl;
    }
}

// Function to display the contents of the book file
void Book::display() {
    ifstream fin;
    string filename = bno + ".txt";
    fin.open(filename);
    if (fin.is_open()) {
        string line;
        cout << "Details of book (" << bno << "):" << endl;
        while (getline(fin, line)) {
            cout << line << endl;
        }
        cout << "-------------------------------" << endl;
        fin.close();
    } else {
        cout << "Error opening file " << filename << endl;
    }
}

// Friend function to display sensitive information
void displaySensitiveInfo(const Book &b) {
    cout << "\n--- Accessing Private Info ---" << endl;
    cout << "Book Number (Private): " << b.bno << endl;
    cout << "Title: " << b.title << endl;
    cout << "Author: " << b.author << endl;
    cout << "-------------------------------" << endl;
}

// Authentication function for login
bool authentication() {
    string username, password;
    const string correctusername = "GEC";
    const string correctpass = "12345";
    const int MaxAttempts = 3;

    cout << "==============================\n";
    cout << "   Welcome to the Library\n";
    cout << "==============================\n";

    for (int attempts = 0; attempts < MaxAttempts; attempts++) {
        cout << "\nEnter your credentials:\n";
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        if (username == correctusername && password == correctpass) {
            cout << "Login successful! Welcome!\n";
            return true;
        } else {
            cout << "Incorrect username or password. Please try again.\n";
        }
    }
    cout << "Maximum attempts reached. Exiting the program.\n";
    return false;
}

int main() {
    if (!authentication()) {
        return 1; // Exit if authentication fails
    }

    int choice, n, p;
    string str;

    cout << "Enter the number of books: ";
    cin >> n;
    cin.ignore();

    Book books[n];

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Enter book details\n";
        cout << "2. Edit book number\n";
        cout << "3. Append price to a book\n";
        cout << "4. Display book details\n";
        cout << "5. Access Sensitive Info (Friend Function)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            for (int i = 0; i < n; i++) {
                books[i].createbook();
            }
            break;

        case 2:
            cout << "Enter serial number of book to edit (1 to " << n << "): ";
            cin >> p;
            cin.ignore();
            cout << "Enter new book number: ";
            getline(cin, str);
            books[p - 1].editnumber(str);
            break;

        case 3:
            for (int i = 0; i < n; i++) {
                books[i].appendprice();
            }
            break;

        case 4:
            for (int i = 0; i < n; i++) {
                books[i].display();
            }
            break;

        case 5:
            cout << "Enter serial number of book to access private info (1 to " << n << "): ";
            cin >> p;
            displaySensitiveInfo(books[p - 1]);
            break;

        case 6:
            cout << "Exiting the program.\n";
            return 0;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}
