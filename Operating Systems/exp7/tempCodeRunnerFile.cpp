#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#define INT_MAX 2147483647

using namespace std;

struct MemoryBlock {
    int start;
    int end;
    int size;
    bool allocated;
    string processId;
};

struct Process {
    string id;
    int size;
    bool allocated;
};

void displayMemoryDiagram(const vector<MemoryBlock>& blocks) {
    cout << "\n+--------------------------------------------------+\n";
    cout << "|                Memory Diagram                    |\n";
    cout << "+--------------------------------------------------+\n";
    cout << "| ";
    for (const auto& block : blocks) {
        cout << "[";
        if (block.allocated) {
            cout << "P" << block.processId << " (" << block.size << "KB)";
        } else {
            cout << "Free (" << block.size << "KB)";
        }
        cout << "] ";
    }
    cout << "|\n";
    cout << "+--------------------------------------------------+\n";
}

void displayProcesses(const vector<Process>& processes) {
    cout << "\n+-----------+------+\n";
    cout << "| Process   | Size |\n";
    cout << "+-----------+------+\n";
    for (const auto& p : processes) {
        cout << "| P" << setw(8) << p.id << " | " << setw(4) << p.size << " |\n";
    }
    cout << "+-----------+------+\n";
}

void bestFit(vector<MemoryBlock>& blocks, vector<Process>& processes) {
    for (auto& process : processes) {
        int bestIndex = -1;
        int minWaste = INT_MAX;
        for (size_t i = 0; i < blocks.size(); ++i) {
            if (!blocks[i].allocated && blocks[i].size >= process.size) {
                int waste = blocks[i].size - process.size;
                if (waste < minWaste) {
                    minWaste = waste;
                    bestIndex = i;
                }
            }
        }
        if (bestIndex != -1) {
            blocks[bestIndex].allocated = true;
            blocks[bestIndex].processId = process.id;
            process.allocated = true;
            cout << "Allocated Process P" << process.id << " (Size: " << process.size << ") to Block " << bestIndex + 1 << " (Start: " << blocks[bestIndex].start << ", End: " << blocks[bestIndex].end << ")\n";
        } else {
            cout << "Could not allocate Process P" << process.id << " (Size: " << process.size << ") - No suitable block found.\n";
        }
    }
}

int main() {
    cout << "=====================================\n";
    cout << "   Best Fit Memory Allocation\n";
    cout << "=====================================\n";

    string approach;
    cout << "Enter the approach (fixed/variable): ";
    cin >> approach;

    int totalMemory;
    cout << "Enter total memory size in KB: ";
    cin >> totalMemory;

    vector<MemoryBlock> blocks;
    if (approach == "fixed") {
        int currentStart = 0;
        while (currentStart < totalMemory) {
            int size;
            cout << "Enter size of block starting at " << currentStart << " KB (remaining: " << (totalMemory - currentStart) << " KB): ";
            cin >> size;
            if (size <= 0 || currentStart + size > totalMemory) {
                cout << "Invalid size. Must be positive and not exceed remaining memory. Try again.\n";
                continue;
            }
            string state;
            cout << "Is this block occupied? (yes/no): ";
            cin >> state;
            bool occupied = (state == "yes");
            string pid = "";
            if (occupied) {
                cout << "Enter process ID (leave empty to mark occupied without id): ";
                cin >> ws;
                getline(cin, pid);
            }
            blocks.push_back({currentStart, currentStart + size, size, occupied, pid});
            currentStart += size;
        }
    } else if (approach == "variable") {
        int currentStart = 0;
        while (currentStart < totalMemory) {
            int size;
            cout << "Enter size of block starting at " << currentStart << " KB (remaining: " << (totalMemory - currentStart) << " KB): ";
            cin >> size;
            if (size <= 0 || currentStart + size > totalMemory) {
                cout << "Invalid size. Must be positive and not exceed remaining memory. Try again.\n";
                continue;
            }
            string state;
            cout << "Is this block occupied? (yes/no): ";
            cin >> state;
            bool occupied = (state == "yes");
            string pid = "";
            if (occupied) {
                cout << "Enter process ID (leave empty to mark occupied without id): ";
                cin >> ws;
                getline(cin, pid);
            }
            blocks.push_back({currentStart, currentStart + size, size, occupied, pid});
            currentStart += size;
        }
    } else {
        cout << "Invalid approach. Choose 'fixed' or 'variable'.\n";
        return 1;
    }

    cout << "Initial Memory Blocks:\n";
    displayMemoryDiagram(blocks);

    vector<Process> processes = {
        {"1", 212},
        {"2", 417},
        {"3", 112},
        {"4", 426}
    };

    cout << "\nProcesses to Allocate:\n";
    displayProcesses(processes);

    cout << "\nAllocating using Best Fit Algorithm:\n";
    bestFit(blocks, processes);

    cout << "\nFinal Memory State:\n";
    displayMemoryDiagram(blocks);

    cout << "\nAllocation Summary:\n";
    for (const auto& p : processes) {
        if (p.allocated) {
            cout << "Process P" << p.id << " allocated successfully.\n";
        } else {
            cout << "Process P" << p.id << " could not be allocated.\n";
        }
    }

    return 0;
}
