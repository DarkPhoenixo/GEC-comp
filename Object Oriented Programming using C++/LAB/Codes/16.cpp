#include <iostream>
#include <string>

using namespace std;

class Bill {
public:
    long int bill_num = 2437;
    string customer;
    string carnumber;
    string hiringperson;
    string hiring_date;
    string visiting_route;
    string closing_kilometer;
    string opening_kilometer;
    int total_kilometer;
    int charge_perkm;
    int total_charge;
    int toll_charge;
    int waiting_chargeperhr;
    int total_tym;
    int Total_wait_charge;
    int night_chargeperhr;
    int total_nights;
    int Total_night_charge;
    int total;
    string charge_in_words;
    string date;

    void inputDetails() {
        cout << "Enter customer name: ";
        getline(cin, customer);

        cout << "Enter car number: ";
        getline(cin, carnumber);

        cout << "Enter hiring person name: ";
        getline(cin, hiringperson);

        cout << "Enter hiring date: ";
        getline(cin, hiring_date);

        cout << "Enter visiting route: ";
        getline(cin, visiting_route);

        cout << "Enter closing kilometer: ";
        getline(cin, closing_kilometer);

        cout << "Enter opening kilometer: ";
        getline(cin, opening_kilometer);

        cout << "Enter total kilometers: ";
        cin >> total_kilometer;

        cout << "Enter charge per kilometer: ";
        cin >> charge_perkm;

        cout << "Enter total charge: ";
        cin >> total_charge;

        cout << "Enter toll charge: ";
        cin >> toll_charge;

        cout << "Enter waiting charge per hour: ";
        cin >> waiting_chargeperhr;

        cout << "Enter total waiting time (in hours): ";
        cin >> total_tym;

        cout << "Enter total waiting charge: ";
        cin >> Total_wait_charge;

        cout << "Enter night charge per hour: ";
        cin >> night_chargeperhr;

        cout << "Enter total nights: ";
        cin >> total_nights;

        cout << "Enter total night charge: ";
        cin >> Total_night_charge;

        cout << "Enter total amount: ";
        cin >> total;

        cin.ignore(); // To ignore the leftover newline character

        cout << "Enter total charge in words: ";
        getline(cin, charge_in_words);

        cout << "Enter date: ";
        getline(cin, date);
    }
};

int main() {
    Bill bill;
    bill.inputDetails();

    return 0;
}
