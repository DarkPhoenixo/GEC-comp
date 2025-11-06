#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

int m, n;
vector<vector<int>> Allocation, Max, Need;
vector<int> Available;

int safety() {
    vector<int> safeSequence(n, -1), Work = Available;
    vector<bool> Finish(n, false);

    int k = 0;
    bool found;

    cout << "\nSafety Algorithm Execution:\n";
    cout << "Initial Work: ";
    for (int j = 0; j < m; j++) cout << Work[j] << " ";
    cout << endl;

    while (true) {
        found = false;

        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < m; j++)
                        Work[j] += Allocation[i][j];
                    Finish[i] = true;
                    safeSequence[k++] = i;
                    found = true;

                    cout << "Allocated P" << i << ", Work: ";
                    for (int j = 0; j < m; j++) cout << Work[j] << " ";
                    cout << ", Sequence so far: ";
                    for (int idx = 0; idx < k; idx++)
                        cout << "P" << safeSequence[idx] << (idx < k - 1 ? " " : "");
                    cout << endl;
                }
            }
        }

        if (!found)
            break;
    }

    vector<int> unfinished;
    for (int i = 0; i < n; i++) {
        if (!Finish[i]) {
            unfinished.push_back(i);
        }
    }

    if (!unfinished.empty()) {
        cout << "\nUnsafe state because the following processes cannot be allocated the required resources: ";
        for (size_t idx = 0; idx < unfinished.size(); idx++) {
            cout << "P" << unfinished[idx];
            if (idx < unfinished.size() - 1) cout << ", ";
        }
        cout << ". This indicates a potential deadlock risk." << endl;
        return 1;  // unsafe
    }

    cout << "\nSafe state. Sequence: <";
    for (int j = 0; j < n; j++)
        cout << "P" << safeSequence[j] << (j < n - 1 ? ", " : ">\n");

    return 0; // safe
}

void display() {
    // Column widths
    const int procW = 6;
    const int colW = 12;
    const int smallW = 2;

    // Header
    cout << left << setw(procW) << "Proc"
         << " | " << setw(colW) << "Allocated"
         << " | " << setw(colW) << "Maximum"
         << " | " << setw(colW) << "Available"
         << " | " << setw(colW) << "Need" << endl;

    cout << string(procW, '-') << "-|-" << string(colW, '-')
         << "-|-" << string(colW, '-')
         << "-|-" << string(colW, '-')
         << "-|-" << string(colW, '-') << endl;

    for (int i = 0; i < n; i++) {
        cout << "P" << i << setw(procW - 1) << " " << " | ";

        // Allocated
        for (int j = 0; j < m; j++) {
            cout << Allocation[i][j];
            if (j < m - 1) cout << " ";
        }
        // pad to column width
        cout << setw(colW - (m * 2 - 1)) << " " << " | ";

        // Maximum
        for (int j = 0; j < m; j++) {
            cout << Max[i][j];
            if (j < m - 1) cout << " ";
        }
        cout << setw(colW - (m * 2 - 1)) << " " << " | ";

        // Available (show only on first row to avoid repetition)
        if (i == 0) {
            for (int j = 0; j < m; j++) {
                cout << Available[j];
                if (j < m - 1) cout << " ";
            }
            cout << setw(colW - (m * 2 - 1)) << " ";
        } else {
            cout << setw(colW) << " ";
        }

        cout << " | ";

        // Need
        for (int j = 0; j < m; j++) {
            cout << Need[i][j];
            if (j < m - 1) cout << " ";
        }

        cout << endl;
    }

    cout << string(procW, '-') << "-|-" << string(colW, '-')
         << "-|-" << string(colW, '-')
         << "-|-" << string(colW, '-')
         << "-|-" << string(colW, '-') << endl;
}

void displayTemp() {
    // Similar to display but labeled differently
    const int procW = 6;
    const int colW = 12;

    cout << "Running Resource State:" << endl;
    cout << left << setw(procW) << "Proc"
         << " | " << setw(colW) << "Allocation"
         << " | " << setw(colW) << "Available"
         << " | " << setw(colW) << "Need" << endl;

    cout << string(procW, '-') << "-|-" << string(colW, '-')
         << "-|-" << string(colW, '-')
         << "-|-" << string(colW, '-') << endl;

    for (int i = 0; i < n; i++) {
        cout << "P" << i << setw(procW - 1) << " " << " | ";

        // Allocation
        for (int j = 0; j < m; j++) {
            cout << Allocation[i][j];
            if (j < m - 1) cout << " ";
        }
        cout << setw(colW - (m * 2 - 1)) << " " << " | ";

        // Available (show only on first row)
        if (i == 0) {
            for (int j = 0; j < m; j++) {
                cout << Available[j];
                if (j < m - 1) cout << " ";
            }
            cout << setw(colW - (m * 2 - 1)) << " ";
        } else {
            cout << setw(colW) << " ";
        }

        cout << " | ";

        // Need
        for (int j = 0; j < m; j++) {
            cout << Need[i][j];
            if (j < m - 1) cout << " ";
        }

        cout << endl;
    }

    cout << string(procW, '-') << "-|-" << string(colW, '-')
         << "-|-" << string(colW, '-')
         << "-|-" << string(colW, '-') << endl;
}

int main() {
    cout << "Enter the number of Processes: ";
    cin >> n;
    cout << "Enter the number of Resource types: ";
    cin >> m;

    Allocation.assign(n, vector<int>(m, 0));
    Max.assign(n, vector<int>(m, 0));
    Need.assign(n, vector<int>(m, 0));
    Available.assign(m, 0);

    cout << "\nEnter Allocated Resources for each process:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < m; j++)
            cin >> Allocation[i][j];
    }

    cout << "\nEnter Max Resources for each process:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < m; j++)
            cin >> Max[i][j];
    }

    cout << "\nEnter Available Resources:" << endl;
    for (int i = 0; i < m; i++)
        cin >> Available[i];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    display();
    int stateFlag = safety();

    char choice = 'y';
    do {
        vector<int> Request(m);
        int p;

        cout << "\n\nEnter Process Number: ";
        cin >> p;

        if (p < 0 || p >= n) {
            cout << "\nInvalid process number.\n";
            cout << "Try another? (Y/N): ";
            cin >> choice;
            continue;
        }

        cout << "Enter Request: ";
        for (int i = 0; i < m; i++)
            cin >> Request[i];

        bool allZeroes = true;
        for (int i = 0; i < m; i++) {
            if (Request[i] != 0) {
                allZeroes = false;
                break;
            }
        }

        if (allZeroes) {
            cout << "\nCannot grant - request is all zeros.\n";
            cout << "Try another? (Y/N): ";
            cin >> choice;
            continue;
        }

        bool invalid = false;
        for (int i = 0; i < m; i++) {
            if (Request[i] > Need[p][i]) {
                cout << "\nProcess exceeded maximum claim for resources.\nRequest Cannot be granted" << endl;
                invalid = true;
                break;
            } else if (Request[i] > Available[i]) {
                cout << "\nProcess must wait. Resources not available." << endl;
                invalid = true;
                break;
            }
        }

        if (invalid) {
            cout << "Try another? (Y/N): ";
            cin >> choice;
            continue;
        }

        for (int i = 0; i < m; i++) {
            Available[i] -= Request[i];
            Allocation[p][i] += Request[i];
            Need[p][i] -= Request[i];
        }

        bool allZeroAvail = true;
        for (int i = 0; i < m; i++) {
            if (Available[i] != 0) {
                allZeroAvail = false;
                break;
            }
        }

        if (allZeroAvail) {
            cout << "\nBanker's Algorithm can't allow available resources to be 0,0,0 for this request. Request rejected.\n";
            // Restore state
            for (int i = 0; i < m; i++) {
                Available[i] += Request[i];
                Allocation[p][i] -= Request[i];
                Need[p][i] += Request[i];
            }
            cout << "Try another? (Y/N): ";
            cin >> choice;
            continue;
        }

        cout << "\nTemporary State:" << endl;
        displayTemp();
        stateFlag = safety();

        if (stateFlag) {
            cout << "\nRequest cannot be granted" << endl;
            for (int i = 0; i < m; i++) {
                Available[i] += Request[i];
                Allocation[p][i] -= Request[i];
                Need[p][i] += Request[i];
            }
            cout << "\nStates Restored:" << endl;
            display();
        } else {
            cout << "\nSafe Sequence Exists and request can be granted immediately to process.\nSnapshot after request:\n";
            display();
        }

        cout << "\n\nTry another Process?(Y/N)";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
