#include <iostream>
#include <string>
using namespace std;

struct student {
    string name;
    int rollnum;
    float sgpa;
    int marks[8];
};

int calc(int mak);
char grap(int grad);
int grade[8];
char gp[8];

int main() {
    int n;
    struct student s1[100];
    string sub[8] = {
        "Maths-I",
        "Basics of Mechanical Engineering",
        "Basics of Electrical Engineering",
        "Chemistry",
        "Introduction to Civil Engineering",
        "Computer Programming",
        "Maths-II",
        "Physics"
    };

    cout << "Enter the number of students" << endl;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        if (n < 10) {
            cout << "Enter the name of student 00" << i + 1 << endl;
        } else {
            cout << "Enter the name of student 0" << i + 1 << endl;
        }
        getline(cin, s1[i].name);

        for (int j = 0; j < 8; j++) {
            cout << "Enter the student's marks in " << sub[j] << " out of 100 " << endl;
            cin >> s1[i].marks[j];
            if (s1[i].marks[j] > 100) {
                cout << "Enter marks out of 100\n";
                j--;  
                continue;
            }
            cin.ignore();

            grade[j] = calc(s1[i].marks[j]);
            gp[j] = grap(grade[j]);
        }

        s1[i].sgpa = 0;
        for (int k = 0; k < 8; k++) {
            s1[i].sgpa += grade[k];
        }
        s1[i].sgpa /= 8;  
    }

    for (int i = 1; i <= n; i++) {
        cout << "=========================Marksheet====================================" << endl;
        if (i < 10) {
            cout << "Roll No-00" << i << endl;
        } else {
            cout << "Roll No-0" << i << endl;
        }
        cout << "Student Name: " << s1[i - 1].name << endl;

        cout << "-----------------------------------------------------------------" << endl;
        for (int j = 0; j < 8; j++) {
            cout << "Subject: " << sub[j] << "\n    Marks: " << s1[i - 1].marks[j]
                 << "         Grade Point: " << grade[j] << "          Grade: " << gp[j];
            if (grade[j] == 0) {
                cout << "  Remarks: FAIL" << endl;
            } else {
                cout << "  Remarks: PASS" << endl;
            }
        }
        cout << "-------------------------------------------------------------------" << endl;
        cout << "SGPA: " << s1[i - 1].sgpa << endl;
        cout << endl;
    }

    return 0;
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
