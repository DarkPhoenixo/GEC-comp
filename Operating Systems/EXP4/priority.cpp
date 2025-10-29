#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    string name;
    int at, bt, ct, tat, wt, pr;
    int remainingTime;
    bool done;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter Process Name, Arrival Time, Burst Time, Priority for P" << i + 1 << ": ";
        cin >> p[i].name >> p[i].at >> p[i].bt >> p[i].pr;
        p[i].remainingTime = p[i].bt;
        p[i].done = false;
    }

    int time = 0, completed = 0;
    vector<string> ganttProcess;
    vector<int> ganttTime;
    ganttTime.push_back(0);
    
    string currentProcess = "";

    while (completed != n) {
        int idx = -1;
        int highestPriority = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].done) {
                if (p[i].pr < highestPriority) {
                    highestPriority = p[i].pr;
                    idx = i;
                } else if (p[i].pr == highestPriority) {
                    if (p[i].at < p[idx].at)
                        idx = i;
                }
            }
        }

        if (idx != -1) {
            if (currentProcess != p[idx].name) {
                currentProcess = p[idx].name;
                ganttProcess.push_back(currentProcess);
                ganttTime.push_back(time);
            }
            
            p[idx].remainingTime--;
            time++;
            
            if (p[idx].remainingTime == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].done = true;
                completed++;
                currentProcess = "";
            }
        } else {
            time++;
            if (currentProcess != "IDLE") {
                currentProcess = "IDLE";
                ganttProcess.push_back(currentProcess);
                ganttTime.push_back(time - 1);
            }
        }
    }
    
    ganttTime.push_back(time);

    int totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    cout << "---------------------------------------------------------------\n";
    cout << "Process\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    cout << "---------------------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].name << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].pr << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\n";
    }
    cout << "---------------------------------------------------------------\n";

    cout << "Total Turnaround Time = " << totalTAT << "\n";
    cout << "Average Turnaround Time = " << (float)totalTAT / n << "\n";
    cout << "Average Waiting Time = " << (float)totalWT / n << "\n\n";

    cout << "Gantt Chart:\n";
    cout << "---------------------------------------------------------------\n|";
    for (size_t i = 0; i < ganttProcess.size(); i++) {
        cout << "    " << setw(2) << ganttProcess[i] << " |";
    }
    cout << "\n---------------------------------------------------------------\n";
    for (size_t i = 0; i < ganttTime.size(); i++) {
        cout << setw(7) << ganttTime[i];
    }
    cout << "\n";

    return 0;
}
