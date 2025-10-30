#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    vector<string> processNames(n);
    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> maxRes(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> available(m);

    // Input process details
    for (int i = 0; i < n; i++) {
        cout << "Enter name for process " << i + 1 << ": ";
        cin >> processNames[i];
        cout << "Enter allocation for " << processNames[i] << " (" << m << " values): ";
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
        cout << "Enter max for " << processNames[i] << " (" << m << " values): ";
        for (int j = 0; j < m; j++) {
            cin >> maxRes[i][j];
            need[i][j] = maxRes[i][j] - allocation[i][j];
        }
    }

    cout << "Enter available resources (" << m << " values): ";
    for (int j = 0; j < m; j++) {
        cin >> available[j];
    }

    // Display tables side by side
    cout << "\nTables:\n";
    cout << setw(10) << "Process";
    for (int j = 0; j < m; j++) {
        cout << setw(5) << "R" << j;
    }
    cout << " | ";
    cout << setw(10) << "Process";
    for (int j = 0; j < m; j++) {
        cout << setw(5) << "R" << j;
    }
    cout << " | ";
    cout << setw(10) << "Process";
    for (int j = 0; j < m; j++) {
        cout << setw(5) << "R" << j;
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(10) << processNames[i];
        for (int j = 0; j < m; j++) {
            cout << setw(5) << allocation[i][j];
        }
        cout << " | ";
        cout << setw(10) << processNames[i];
        for (int j = 0; j < m; j++) {
            cout << setw(5) << maxRes[i][j];
        }
        cout << " | ";
        cout << setw(10) << processNames[i];
        for (int j = 0; j < m; j++) {
            cout << setw(5) << need[i][j];
        }
        cout << endl;
    }

    // Display Available
    cout << "\nAvailable Resources: ";
    for (int j = 0; j < m; j++) {
        cout << available[j] << " ";
    }
    cout << endl;

    // Banker's Algorithm with step-by-step output
    vector<int> work = available;
    vector<bool> finish(n, false);
    vector<int> safeSequence;

    int count = 0;
    cout << "\nStep-by-step execution:\n";
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    cout << "Executing process " << processNames[i] << ". Resources freed: ";
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                        cout << allocation[i][j];
                        if (j < m - 1) cout << ",";
                    }
                    cout << ". New available: ";
                    for (int j = 0; j < m; j++) {
                        cout << work[j];
                        if (j < m - 1) cout << ",";
                    }
                    cout << endl;
                    safeSequence.push_back(i);
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            cout << "\nSystem is in unsafe state. No safe sequence found.\n";
            return 0;
        }
    }

    cout << "\nSafe Sequence: ";
    for (int i = 0; i < safeSequence.size(); i++) {
        cout << processNames[safeSequence[i]];
        if (i < safeSequence.size() - 1) cout << " -> ";
    }
    cout << endl;

    return 0;
}