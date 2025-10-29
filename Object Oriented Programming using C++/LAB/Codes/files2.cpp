#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

struct Contact {
    string name;
    string phoneNumber;
};

class TelephoneDirectory {
private:
    const string filename = "contacts.txt";

    void saveContact(const Contact& contact) {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << contact.name << "," << contact.phoneNumber << "\n";
            file.close();
        } else {
            cout << "Unable to open file for writing.\n";
        }
    }

    bool loadContacts(vector<Contact>& contacts) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t pos = line.find(',');
                if (pos != string::npos) {
                    Contact contact;
                    contact.name = line.substr(0, pos);
                    contact.phoneNumber = line.substr(pos + 1);
                    contacts.push_back(contact);
                }
            }
            file.close();
            return true;
        } else {
            cout << "Unable to open file for reading.\n";
            return false;
        }
    }

    void saveAllContacts(const vector<Contact>& contacts) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& contact : contacts) {
                file << contact.name << "," << contact.phoneNumber << "\n";
            }
            file.close();
        } else {
            cout << "Unable to open file for writing.\n";
        }
    }

public:
    void addContact(const string& name, const string& phoneNumber) {
        Contact contact = {name, phoneNumber};
        saveContact(contact);
        cout << "Contact added successfully.\n";
    }

    bool searchContact(const string& name, Contact& contact) {
        vector<Contact> contacts;
        if (loadContacts(contacts)) {
            for (const auto& c : contacts) {
                if (c.name == name) {
                    contact = c;
                    return true;
                }
            }
        }
        return false;
    }

    bool updateContact(const string& name, const string& newPhoneNumber) {
        vector<Contact> contacts;
        if (loadContacts(contacts)) {
            for (auto& c : contacts) {
                if (c.name == name) {
                    c.phoneNumber = newPhoneNumber;
                    saveAllContacts(contacts);
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    TelephoneDirectory directory;
    int choice;
    Contact contact;
    string name, phoneNumber;

    while (true) {
        cout << "\nTelephone Directory Application\n";
        cout << "1. Add Contact\n";
        cout << "2. Search Contact\n";
        cout << "3. Update Contact\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer after numeric input

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter phone number: ";
                getline(cin, phoneNumber);
                directory.addContact(name, phoneNumber);
                break;
            case 2:
                cout << "Enter name to search: ";
                getline(cin, name);
                
                if (directory.searchContact(name, contact)) {
                    cout << "Name: " << contact.name << ", Phone Number: " << contact.phoneNumber << "\n";
                } else {
                    cout << "Contact not found.\n";
                }
                break;
            case 3:
                cout << "Enter name to update: ";
                getline(cin, name);
                cout << "Enter new phone number: ";
                getline(cin, phoneNumber);
                if (directory.updateContact(name, phoneNumber)) {
                    cout << "Contact updated successfully.\n";
                } else {
                    cout << "Contact not found.\n";
                }
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
