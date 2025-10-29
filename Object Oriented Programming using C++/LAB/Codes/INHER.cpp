#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

class Student {
protected:
    int roll_number;
    char name[50];
public:
    Student() {
        roll_number = 0;
        name[0] = '\0';
    }
    void input(int r, const char *n) {
        roll_number = r;
        strcpy(name, n);
    }
};

class EXAM :  public Student {
protected:
    int n;
    char **subject;
    int *marks;
    int *max_marks;
public:
    EXAM() {
        n = 0;
        subject = NULL;
        marks = NULL;
        max_marks = NULL;
    }
    
    void getinfo() {
        cout << "Enter the number of subjects: ";
        cin >> n;

        subject = new char*[n];
        marks = new int[n];
        max_marks = new int[n];

        for (int i = 0; i < n; i++) {
            subject[i] = new char[50];
            cout << "Enter the subject name: ";
            cin.ignore();
            cin.getline(subject[i], 50);
            cout << "Enter the marks obtained: ";
            cin >> marks[i];
            cout << "Enter the maximum marks: ";
            cin >> max_marks[i];
        }
    }
};

class result : public max {
protected:
    int total_marks = 0;
    int total_max_marks = 0;
    float percentage;
public:
    result() : Student() {
        total_marks = 0;
        total_max_marks = 0;
        percentage = 0;
    }

    void calculateResult() {
        for (int i = 0; i < n; i++) {
            total_marks += marks[i];
            total_max_marks += max_marks[i];
        }
        if (total_max_marks > 0) {
            percentage = ((float)total_marks / total_max_marks) * 100;
        } else {
            percentage = 0;
        }
    }

    int calc(int mak) {
        if (mak <= 100 && mak >= 85) {
            return 10;
        } else if (mak < 85 && mak >= 75) {
            return 9;
        } else if (mak < 75 && mak >= 65) {
            return 8;
        } else if (mak < 65 && mak >= 55) {
            return 7;
        } else if (mak < 55 && mak >= 50) {
            return 6;
        } else if (mak < 50 && mak >= 40) {
            return 5;
        } else if (mak < 40) {
            return 0;
        }
        return 0; 
    }

    char grap(int grad) {
        if (grad == 10) {
            return 'O';
        } else if (grad == 9) {
            return 'A';
        } else if (grad == 8) {
            return 'B';
        } else if (grad == 7) {
            return 'C';
        } else if (grad == 6) {
            return 'D';
        } else if (grad == 5) {
            return 'E';
        } else if (grad == 0) {
            return 'F';
        }
        return ' '; 
    }

    void display() {
        cout << "\n\nRoll Number: " << roll_number << endl;
        cout << "Name: " << name << endl;
        cout << "Semesters RESULTS :\n";
        cout << "---------------------------------------------------------------------\n";
        cout << " :       SUBJECT                 :   MARKS   : TOTAL   :   GRADE :\n";
        cout << "---------------------------------------------------------------------\n";

        for (int i = 0; i < n; i++) {
            int grade = calc(marks[i]); 
            char grade_letter = grap(grade); // Get the grade letter
            
            cout << " : " << left << setw(30) << subject[i] << " :   " 
                 << fixed << setprecision(1) << marks[i] << "    :   " 
                 << max_marks[i] << "     :   " 
                 << setw(2) << grade_letter << "     :\n";
        }

        cout << "---------------------------------------------------------------------\n";
        cout << "Percentage: " << fixed << setprecision(2) << percentage << "%" << endl;
    }
};

        
        int main() {
    int roll;
    char name[50];
    cout << "Enter Roll Number: ";
    cin >> roll;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(name, 50);
    result r;
    r.input(roll,name);
    r.getinfo();
    r.calculateResult();
    r.display();

cout<<"This type of inheritance is called Multilevel Inheritance"<<endl;
    return 0;
}
