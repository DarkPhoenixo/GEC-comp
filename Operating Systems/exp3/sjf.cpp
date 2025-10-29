#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    string name;
    int arrival, burst, start, completion, turnaround, waiting;
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

    vector<bool> done(n, false);
    int time = 0, completed = 0;
    float avgTAT = 0, avgWT = 0;
    int totalTAT = 0;
    vector<string> ganttOrder;
    vector<int> ganttTime;

    while (completed < n) {
        int idx = -1, minBT = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time && p[i].burst < minBT) {
                minBT = p[i].burst;
                idx = i;
            }
        }
        if (idx == -1) {
            // No process available, add idle time
            int nextArrival = 1e9;
            for (int i = 0; i < n; i++) {
                if (!done[i] && p[i].arrival < nextArrival) {
                    nextArrival = p[i].arrival;
                }
            }
            ganttOrder.push_back("Idle");
            ganttTime.push_back(nextArrival);
            time = nextArrival;
        } else {
            p[idx].start = time;
            time += p[idx].burst;
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            avgTAT += p[idx].turnaround;
            avgWT += p[idx].waiting;
            totalTAT += p[idx].turnaround;
            done[idx] = true;
            completed++;
            ganttOrder.push_back(p[idx].name);
            ganttTime.push_back(time);
        }
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
