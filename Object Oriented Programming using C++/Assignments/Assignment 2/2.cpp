#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class player {
private:
    string name;
    int runs;
    int innings;
    int notouting;
    float average;

public:
    void input() {
        cin.ignore();
        cout << "Enter the name of the player\n";
        getline(cin, name);
        cout << "Enter the runs he scored in his career\n";
        cin >> runs;
    label:
        cout << "Enter the innings he has played \n";
        cin >> innings;
        cout << "Enter the number of times he remained not out \n";
        cin >> notouting;
        if (notouting > innings) {
            cout << "Enter valid data\n";
            goto label;
        }
        average = static_cast<float>(runs) / (innings - notouting);
        return;
    }

    void display() {
        cout << setw(25) << left << name
             << setw(10) << right << runs
             << setw(10) << right << innings
             << setw(17) << right << notouting
             << setw(10) << right << fixed << setprecision(2) << average
             << endl;
    }
};

int main() {
    int n;
    player s[100];
    cout << "Enter the number of players\n";
    cin >> n;

    for (int i = 0; i < n; i++) {
        s[i].input();
    }

    cout << "\n" << setw(25) << left << "Player's name"
         << setw(10) << right << "Runs"
         << setw(10) << right << "Innings"
         << setw(17) << right << "Times not out"
         << setw(10) << right << "Average"
         << endl;
    
    for (int i = 0; i < n; i++) {
        s[i].display();
    }
    return 0;
}
