#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

class Student {
protected:
    char *roll_number;
    char name[50];
public:
    Student() {
        roll_number = NULL;
        name[0] = '\0';
    }
    void input(char *r, const char *n) {
        roll_number = new char[strlen(r) + 1];
        strcpy(roll_number, r);
        strcpy(name, n);
    }
};

class Exam : virtual public Student {
protected:
    int n;
    char **subject;
    int *marks;
    int *max_marks;
public:
    Exam() {
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
    
        cin.ignore(); 
    
        for (int i = 0; i < n; i++) {
            subject[i] = new char[50];
            cout << "Enter the subject name: ";
            cin.getline(subject[i], 50);
            cout << "Enter the marks obtained: ";
            cin >> marks[i];
            cout << "Enter the maximum marks: ";
            cin >> max_marks[i];
            cin.ignore(); 
        }
    }
};

class sports : virtual public Student {
protected:
    string eval = "Sports";
    int score;
    int total;
public:
    sports() {
        score = 0;
        total = 0;
    }
    void getdata() {
        cout << "Enter the sports score of the student: ";
        cin >> score;
        cout << "Enter the total sports score: ";
        cin >> total;
    }
    void display() {
        cout << "The score of the student in " << eval << " is: " << score << endl;
        cout << "The total score in " << eval << " is: " << total << endl;
    }
};

class result : public Exam, public sports {
protected:
    int total_marks = 0;
    int total_max_marks = 0;
    float percentage;
    int sports_grade; 
public:
    result() : Student() {
        total_marks = 0;
        total_max_marks = 0;
        percentage = 0;
        sports_grade = 0; 
    }

    void calculateResult() {
        for (int i = 0; i < n; i++) {
            total_marks += marks[i];
            total_max_marks += max_marks[i];
        }
        total_marks += score;
        total_max_marks += total;
        if (total_max_marks > 0) {
            percentage = ((float)total_marks / total_max_marks) * 100;
        } else {
            percentage = 0;
        }
    }

    int calc(int marks) {
        if (marks <= 100 && marks >= 85) return 10;
        else if (marks < 85 && marks >= 75) return 9;
        else if (marks < 75 && marks >= 65) return 8;
        else if (marks < 65 && marks >= 55) return 7;
        else if (marks < 55 && marks >= 50) return 6;
        else if (marks < 50 && marks >= 40) return 5;
        else return 0;
    }

    char grap(int grade) {
        if (grade == 10) return 'O';
        else if (grade == 9) return 'A';
        else if (grade == 8) return 'B';
        else if (grade == 7) return 'C';
        else if (grade == 6) return 'D';
        else if (grade == 5) return 'E';
        else return 'F';
    }

    void display() {
        cout << "\n\nRoll Number: " << roll_number << endl;
        cout << "Name: " << name << endl;
        cout << "Semester RESULTS :\n";
        cout << "---------------------------------------------------------------------\n";
        cout << " :       SUBJECT                 :   MARKS   : TOTAL   :   GRADE :\n";
        cout << "---------------------------------------------------------------------\n";

        for (int i = 0; i < n; i++) {
            int mar = (marks[i] * 100) / max_marks[i];
            int grade = calc(mar);
            char grade_letter = grap(grade);

            cout << " : " << left << setw(30) << subject[i] << " :   "
                 << fixed << setprecision(1) << marks[i] << "    :   "
                 << max_marks[i] << "     :   "
                 << setw(2) << grade_letter << "     :\n";
        }
        
        int sports_max = (score * 100) / total;
        char sports_grade_letter = grap(calc(sports_max));

        cout << " : " << left << setw(30) << eval << " :   "
             << fixed << setprecision(1) << score << "    :   "
             << total << "     :   "<< sports_grade_letter << "     :\n"; 

        cout << "---------------------------------------------------------------------\n";
        cout << "Percentage: " << fixed << setprecision(2) << percentage << "%" << endl;
    }
};

int main() {
    char roll[50];
    char name[50];
    cout << "Enter Roll Number: ";
    cin.getline(roll, 50);
    cout << "Enter Name: ";
    cin.getline(name, 50);
    result r;
    r.input(roll, name);
    r.getinfo();
    r.getdata();  
    r.calculateResult();
    r.display();

cout<<"\n\n This type of inheritance is called hybrid inheritance."<<endl;
    return 0;
}
