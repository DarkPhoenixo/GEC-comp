#include <iostream>
#include <string>
using namespace std;

class studrec {
private:
    string name;
    int roll_num;
    string address;
    string sub[4];
    int marks[4];
    float percentage;

public:
    void getdata() {
        cout << "Enter the name of the student\n";
        cin.ignore();
        getline(cin, name);
        cout << "Enter the Roll-Number of the student\n";
        cin >> roll_num;
        cin.ignore();
        cout << "Enter the address of the student\n";
        getline(cin, address);
        
        int total_marks = 0;
        for (int i = 0; i < 4; i++) {
            cout << "Enter the name of the subject\n";
            getline(cin, sub[i]);
            cout << "Enter the marks obtained in that subject\n";
            cin >> marks[i];
            cin.ignore();
            total_marks += marks[i];
        }
        percentage = percent(total_marks, 400);
    }

    float percent(int total_marks, int max_marks) {
        return (static_cast<float>(total_marks) / max_marks) * 100;
    }

    void display() {
        cout << "=======Marksheet============\n";
        cout << "Roll number--" << roll_num << endl;
        cout << "Name--" << name << endl;
        for (int i = 0; i < 4; i++) {
            cout << "Subject-- " << sub[i] << "  Marks-- " << marks[i] << endl;
        }
        cout << "Percentage-- " << percentage << "%" << endl;
    }
};

int main() {
    studrec s1;
    s1.getdata();
    s1.display();

    return 0;
}
