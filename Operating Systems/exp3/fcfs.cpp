#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    string name;
    int arrival, burst, completion, turnaround, waiting;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "\nEnter Process Name, Arrival Time, Burst Time for P" << i + 1 << ": ";
        cin >> p[i].name >> p[i].arrival >> p[i].burst;
    }

    sort(p.begin(), p.end(), [](Process &a, Process &b) {
        return a.arrival < b.arrival;
    });

    int time = 0;
    float avgTAT = 0, avgWT = 0;
    int totalTAT = 0;  
    vector<string> ganttOrder;
    vector<int> ganttTime;

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival) {
            ganttOrder.push_back("Idle");
            ganttTime.push_back(p[i].arrival);
            time = p[i].arrival;
        }
        time += p[i].burst;
        p[i].completion = time;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        avgTAT += p[i].turnaround;
        avgWT += p[i].waiting;
        totalTAT += p[i].turnaround;  

        ganttOrder.push_back(p[i].name);
        ganttTime.push_back(time);
    }

    cout << "\n---------------------------------------------------------------\n";
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "---------------------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].name << "\t" << p[i].arrival << "\t" << p[i].burst << "\t"
             << p[i].completion << "\t" << p[i].turnaround << "\t" << p[i].waiting << "\n";
    }
    cout << "---------------------------------------------------------------\n";
    cout << "Total Turnaround Time = " << totalTAT << endl;  
    cout << "Average Turnaround Time = " << avgTAT / n << endl;
    cout << "Average Waiting Time = " << avgWT / n << endl;

    cout << "\nGantt Chart:\n";
    cout << "---------------------------------------------------------------\n";
    for (auto &proc : ganttOrder) {
        cout << "| " << setw(5) << proc << " ";
    }
    cout << "|\n";
    cout << "---------------------------------------------------------------\n";
    cout << 0;
    for (auto &t : ganttTime) {
        cout << setw(7) << t;
    }
    cout << "\n";

    return 0;
}
