#include <iostream>
#include <iomanip>
#include <string>
#include <ctime> // For date, time
#include <sstream> // For converting numbers to strings
using namespace std;

struct Item {
    int quantity;
    string description;
    double rate;

    double getAmount() {
        return quantity * rate;
    }
};

// Function to get the current date as a string
string getCurrentDate() {
    time_t now = time(0);
    tm* localtm = localtime(&now);
    char buf[80];
    strftime(buf, sizeof(buf), "%d-%m-%Y", localtm);
    return string(buf);
}

// Function to get the current time as a string
string getCurrentTime() {
    time_t now = time(0);
    tm* localtm = localtime(&now);
    char buf[80];
    strftime(buf, sizeof(buf), "%H:%M", localtm);
    return string(buf);
}

// Function to generate a unique number as a string
string generateUniqueNumber() {
    time_t now = time(0);
    stringstream ss;
    ss << now; // Use time in seconds as the unique number
    return ss.str();
}

// Function to display the menu and get the user's choice
int displayMenu() {
    int choice;
    cout << "\n--- Menu ---" << endl;
    cout << "1. Add items to the bill" << endl;
    cout << "2. Generate and display bill" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Function to generate and display the bill
void displayBill(Item* items, int numItems, double totalAmount) {
    // Get current date, time, and unique number as strings
    string currentDate = getCurrentDate();
    string currentTime = getCurrentTime();
    string uniqueNumber = generateUniqueNumber();

    // Printing the receipt header with date, time, and unique number
    cout <<""<< setw(90) << setfill('_') << "_" << setfill(' ') <<"_"<< endl;
    cout << "| " << left << setw(25) << "TIN: 30750203865" << setw(30) << right 
         << "CASH/CREDIT BILL Fssai:10612001000124" << setw(26) << " " << " |" << endl;
    cout << "| " << left << setw(10) << "CST:2844" << setw(78) << " " << " |" << endl;
    cout << "| " << right << setw(60) << "M/s .R. V. KURTARKAR & SONS " << setw(28) << " " << " |" << endl;
    cout << "| " << setw(55) << "10, Vishwalaxmi Bldg, Ponda- Goa" << setw(33) << " " << " |" << endl;
    cout << "| " << setw(2) << "No." << setw(48) << "Ph:2312544" 
         << right << setw(20) << "Date: " << currentDate // Display current date
         << setw(5) << currentTime // Display current time
         << right << " " << " |" << endl;
    cout << "| " << setw(2) << "M/s." << setw(83) << uniqueNumber << " |" << endl; // Unique bill number
    cout <<"|"<< setw(90) << setfill('_') << "_" << setfill(' ') <<"|"<< endl;

    // Printing table headers
    cout <<"|"<< setw(90) << setfill('_') << "_" << setfill(' ') <<"|"<< endl;
    cout << "| " << setw(10) << " " << setw(5) << "|Qty"
         << " | " << setw(25) << "Particulars"
         << " | " << setw(8) << "Rate"
         << " | " << setw(10) << "Amount"
         << " | " << setw(5) << " " << setw(13) << " " << " |" << endl;
    cout <<"|"<< setw(90) << setfill('_') << "_" << setfill(' ') <<"|"<< endl;

    // Printing items
    for (int i = 0; i < numItems; ++i) {
        cout << "|" << setw(13) << "|" << setw(3) << items[i].quantity
             << " | " << setw(25) << items[i].description
             << " | " << setw(8) << fixed << setprecision(2) << items[i].rate
             << " | " << setw(10) << fixed << setprecision(2) << items[i].getAmount()
             << " | " << setw(5) << " " << setw(13) << " " << " |" << endl;
    }

    for (int i = 0; i < 6; ++i) {
        cout << "| " << setw(12) << "|" << setw(3) << " " 
             << " | " << setw(25) << " " 
             << " | " << setw(8) << " " 
             << " | " << setw(10) << " " 
             << " | " << setw(5) << "" << setw(13) << " " << " |" << endl;
    }

    cout <<"|"<< setw(90) << setfill('_') << "_" << setfill(' ')<<"|" << endl;
    cout << "| " << setw(10) << " " << setw(44) << "VAT" << endl;
    cout << "| " << setw(10) << " " << setw(44) << "Total"
         << " | " << setw(10) << fixed << setprecision(2) << totalAmount
         << " | " << setw(5) << " " << setw(13) << " " << " |" << endl;
    cout <<"|"<< setw(90) << setfill('_') << "_" << setfill(' ')<<"|" << endl;

    cout << "| " << setw(10) << " " << setw(70) << "Goods once sold will not be taken back" << setw(8) << " " << " |" << endl;
    cout <<"|"<< setw(90) << setfill('_') << "_" << setfill(' ') <<"|"<< endl;
}

int main() {
    int numItems = 0;
    Item* items = nullptr;
    double totalAmount = 0.0;
    int choice;

    do {
        choice = displayMenu();
        switch (choice) {
            case 1: {
                cout << "Enter the number of items: ";
                cin >> numItems;

                // Deallocate previous memory if new items are added
                if (items != nullptr) {
                    delete[] items;
                }

                items = new Item[numItems];

                for (int i = 0; i < numItems; ++i) {
                    cout << "Enter quantity for item " << i + 1 << ": ";
                    cin >> items[i].quantity;
                    cout << "Enter description for item " << i + 1 << ": ";
                    cin.ignore(); 
                    getline(cin, items[i].description);
                    cout << "Enter rate for item " << i + 1 << ": ";
                    cin >> items[i].rate;
                }

                // Calculate the total amount
                totalAmount = 0.0;
                for (int i = 0; i < numItems; ++i) {
                    totalAmount += items[i].getAmount();
                }
                break;
            }

            case 2:
                if (numItems > 0) {
                    displayBill(items, numItems, totalAmount);
                } else {
                    cout << "No items added to the bill. Please add items first." << endl;
                }
                break;

            case 3:
                cout << "Exiting the program." << endl;
                break;

            default:
                cout << "Invalid choice! Please select again." << endl;
        }
    } while (choice != 3);

    // Deallocate memory before exiting
    if (items != nullptr) {
        delete[] items;
    }

    return 0;
}