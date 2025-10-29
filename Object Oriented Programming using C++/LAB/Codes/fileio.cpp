#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Function prototypes with definitions
void displayMenu() {
    cout << "\n------ Budgeting Application ------\n";
    cout << "1. Log a Transaction\n";
    cout << "2. Generate Monthly Report\n";
    cout << "3. View All Transactions\n";
    cout << "4. Delete All Transactions\n";
    cout << "5. Exit\n";
}

void logTransaction() {
    ofstream file("transactions.csv", ios::app);
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }

    string type, description;
    double amount;
    cout << "Enter type (income/expense): ";
    cin >> type;
    cout << "Enter description: ";
    cin.ignore();  
    getline(cin, description);
    cout << "Enter amount: ";
    cin >> amount;

    file << type << "," << description << "," << amount << "\n";
    file.close();

    cout << "Transaction logged successfully." << endl;
}

void generateMonthlyReport() {
    ifstream file("transactions.csv");
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }

    string line, type, description;
    double amount, totalIncome = 0, totalExpense = 0;

    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.rfind(',');
 
        if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
            type = line.substr(0, pos1);
            description = line.substr(pos1 + 1, pos2 - pos1 - 1);
            amount = stod(line.substr(pos2 + 1));

            if (type == "income") {
                totalIncome += amount;
            } else if (type == "expense") {
                totalExpense += amount;
            }
        }
    }

    file.close();

    cout << fixed << setprecision(2);
    cout << "\n------ Monthly Report ------\n";
    cout << "Total Income: Rs" << totalIncome << endl;
    cout << "Total Expenses: Rs" << totalExpense << endl;
    cout << "Net Savings: Rs" << (totalIncome - totalExpense) << endl;
}

void viewAllTransactions() {
    ifstream file("transactions.csv");
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }

    string line, type, description;
    double amount;

    cout << "\n------ All Transactions ------\n";
    cout << left << setw(15) << "Type" << setw(25) << "Description" << "Amount" << endl;
    cout << "-----------------------------------------------\n";
    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.rfind(',');

        if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
            type = line.substr(0, pos1);
            description = line.substr(pos1 + 1, pos2 - pos1 - 1);
            amount = stod(line.substr(pos2 + 1));

            cout << left << setw(15) << type << setw(25) << description << fixed << setprecision(2) << amount << endl;
        }
    }

    file.close();
}

void deleteAllTransactions() {
    ofstream file("transactions.csv", ios::trunc);
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }

    file.close();
    cout << "All transactions have been deleted." << endl;
}

int main() {
    int choice;

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                logTransaction();
                break;
            case 2:
                generateMonthlyReport();
                
                break;
            case 3:
                viewAllTransactions();
                break;
            case 4:
                deleteAllTransactions();
                break;
            case 5:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
