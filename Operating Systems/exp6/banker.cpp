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

    for (int i = 0; i < n; i++) {
        if (!Finish[i]) {
            cout << "\nUnsafe state.\n";
            return 1;  // unsafe
        }
    }

    cout << "\nSafe state. Sequence: <";
    for (int j = 0; j < n; j++)
        cout << "P" << safeSequence[j] << (j < n - 1 ? ", " : ">\n");

    return 0; // safe
}

void display() {
    const int procWidth = 8;
    const int resWidth = 12;  // Adjust as needed for better alignment

    cout << left << setw(procWidth) << "Process" << "| " << left << setw(resWidth) << "Allocated" << "| " << left << setw(resWidth) << "Maximum" << "| " << left << setw(resWidth) << "Need" << endl;
    cout << string(procWidth, '-') << "|-" << string(resWidth, '-') << "|-" << string(resWidth, '-') << "|-" << string(resWidth, '-') << endl;

    for (int i = 0; i < n; i++) {
        string allocStr = "";
        for (int j = 0; j < m; j++) {
            allocStr += to_string(Allocation[i][j]) + (j < m - 1 ? " " : "");
        }
        string maxStr = "";
        for (int j = 0; j < m; j++) {
            maxStr += to_string(Max[i][j]) + (j < m - 1 ? " " : "");
        }
        string needStr = "";
        for (int j = 0; j < m; j++) {
            needStr += to_string(Need[i][j]) + (j < m - 1 ? " " : "");
        }

        cout << left << setw(procWidth) << ("P" + to_string(i)) << "| " << left << setw(resWidth) << allocStr << "| " << left << setw(resWidth) << maxStr << "| " << left << setw(resWidth) << needStr << endl;
    }

    cout << string(procWidth, '-') << "|-" << string(resWidth, '-') << "|-" << string(resWidth, '-') << "|-" << string(resWidth, '-') << endl;

    string availStr = "";
    for (int j = 0; j < m; j++) {
        availStr += to_string(Available[j]) + (j < m - 1 ? " " : "");
    }
    cout << left << setw(procWidth) << "Available" << "| " << left << setw(resWidth) << availStr << "| " << string(resWidth, ' ') << "| " << string(resWidth, ' ') << endl;
}

void displayTemp() {
    const int numWidth = 3;
    int allocWidth = m * numWidth;
    int availWidth = m * numWidth;
    int needWidth = m * numWidth;
    int procWidth = 7;

    cout << left << setw(procWidth) << "Process" << " | " << left << setw(allocWidth) << "Allocation" << " | " << left << setw(availWidth) << "Available" << " | " << left << setw(needWidth) << "Need" << endl;

    cout << string(procWidth, '-') << "|" << string(allocWidth, '-') << "|" << string(availWidth, '-') << "|" << string(needWidth, '-') << endl;

    for (int i = 0; i < n; i++) {
        cout << left << setw(procWidth) << ("P" + to_string(i)) << " | ";
        for (int j = 0; j < m; j++) cout << right << setw(numWidth) << Allocation[i][j];
        cout << " | ";
        if (i == 0) {
            for (int j = 0; j < m; j++) cout << right << setw(numWidth) << Available[j];
        } else {
            cout << string(availWidth, ' ');
        }
        cout << " | ";
        for (int j = 0; j < m; j++) cout << right << setw(numWidth) << Need[i][j];
        cout << endl;
    }

    cout << string(procWidth, '-') << "|" << string(allocWidth, '-') << "|" << string(availWidth, '-') << "|" << string(needWidth, '-') << endl;
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
