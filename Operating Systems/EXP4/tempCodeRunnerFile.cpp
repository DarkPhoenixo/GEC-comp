#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <climits>
using namespace std;

struct Process {
    string name;
    int arrival, burst, remaining, start, completion, turnaround, waiting;
    bool started;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "\nEnter Process Name, Arrival Time, Burst Time for P" << i + 1 << ": ";
        cin >> p[i].name >> p[i].arrival >> p[i].burst;
        p[i].remaining = p[i].burst;
        p[i].started = false;
    }

    int time_quantum;
    cout << "\nEnter Time Quantum: ";
    cin >> time_quantum;

    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    vector<bool> done(n, false);
    int time = 0, completed = 0;
    float avgTAT = 0, avgWT = 0;
    int totalTAT = 0;
    vector<string> runningOrder;
    vector<int> runningTime;
    vector<string> readyOrder;
    vector<int> readyTime;
    queue<int> ready_queue;

    time = p[0].arrival;
    for (int i = 0; i < n; i++) {
        if (p[i].arrival == time) {
            ready_queue.push(i);
        }
    }

    while (completed < n) {
        if (ready_queue.empty()) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!done[i] && p[i].arrival < nextArrival) {
                    nextArrival = p[i].arrival;
                }
            }
            time = nextArrival;
            for (int i = 0; i < n; i++) {
                if (!done[i] && p[i].arrival == time) {
                    ready_queue.push(i);
                }
            }
        } else {
            int idx = ready_queue.front();
            ready_queue.pop();

            if (!p[idx].started) {
                p[idx].start = time;
                p[idx].started = true;
            }

            runningOrder.push_back(p[idx].name);
            runningTime.push_back(time);

            int exec_time = min(time_quantum, p[idx].remaining);
            time += exec_time;
            p[idx].remaining -= exec_time;

            for (int i = 0; i < n; i++) {
                if (!done[i] && p[i].arrival > time - exec_time && p[i].arrival <= time) {
                    ready_queue.push(i);
                    readyOrder.push_back(p[i].name);
                    readyTime.push_back(time - exec_time + (p[i].arrival - (time - exec_time)));
                }
            }

            if (p[idx].remaining == 0) {
                p[idx].completion = time;
                p[idx].turnaround = p[idx].completion - p[idx].arrival;
                p[idx].waiting = p[idx].turnaround - p[idx].burst;
                avgTAT += p[idx].turnaround;
                avgWT += p[idx].waiting;
                totalTAT += p[idx].turnaround;
                done[idx] = true;
                completed++;
            } else {
                ready_queue.push(idx);
                readyOrder.push_back(p[idx].name);
                readyTime.push_back(time);
            }
        }
    }

    runningTime.push_back(time);
    readyTime.push_back(time);

    cout << "\n---------------------------------------------------------------\n";
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "---------------------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].name << "\t" << p[i].arrival << "\t" << p[i].burst << "\t"
             << p[i].completion << "\t" << p[i].turnaround << "\t" << p[i].waiting << "\n";
    }
    cout << "---------------------------------------------------------------\n";
    cout << "Average Turnaround Time = " << avgTAT / n << endl;
    cout << "Average Waiting Time = " << avgWT / n << endl;

    auto displayChart = [&](string title, vector<string>& order, vector<int>& times) {
        cout << "\n" << title << ":\n";
        cout << "---------------------------------------------------------------\n";
        for (size_t i = 0; i < order.size(); i++) {
            cout << "| " << setw(3) << order[i] << " ";
        }
        cout << "|\n";
        cout << "---------------------------------------------------------------\n";
        cout << setw(2) << times[0];
        for (size_t i = 1; i < times.size(); i++) {
            cout << setw(6) << times[i];
        }
        cout << "\n";
    };

    displayChart("Ready Queue", readyOrder, readyTime);
    displayChart("Running Queue", runningOrder, runningTime);

    return 0;
}
