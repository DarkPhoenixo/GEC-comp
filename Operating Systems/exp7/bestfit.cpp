#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#define INT_MAX 2147483647

using namespace std;

// Structure for Memory Block
struct MemoryBlock {
    int size;
    bool allocated;
    int processId; // -1 if not allocated
};

// Structure for Process
struct Process {
    int id;
    int size;
    bool allocated;
};

// Function to display memory blocks in a table format
void displayMemory(const vector<MemoryBlock>& blocks) {
    cout << "\n+-------------------+-------+------------+\n";
    cout << "| Memory Block      | Size  | Process ID |\n";
    cout << "+-------------------+-------+------------+\n";
    for (size_t i = 0; i < blocks.size(); ++i) {
        cout << "| Block " << setw(11) << i + 1 << " | " << setw(5) << blocks[i].size << " | ";
        if (blocks[i].allocated) {
            cout << setw(10) << blocks[i].processId << " |\n";
        } else {
            cout << setw(10) << "Free" << " |\n";
        }
    }
    cout << "+-------------------+-------+------------+\n";
}

// Function to display processes
void displayProcesses(const vector<Process>& processes) {
    cout << "\n+-----------+------+\n";
    cout << "| Process   | Size |\n";
    cout << "+-----------+------+\n";
    for (const auto& p : processes) {
        cout << "| P" << setw(8) << p.id << " | " << setw(4) << p.size << " |\n";
    }
    cout << "+-----------+------+\n";
}

// Best Fit Allocation Function
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
            cout << "Allocated Process P" << process.id << " (Size: " << process.size << ") to Block " << bestIndex + 1 << " (Size: " << blocks[bestIndex].size << ")\n";
        } else {
            cout << "Could not allocate Process P" << process.id << " (Size: " << process.size << ") - No suitable block found.\n";
        }
    }
}

int main() {
    cout << "=====================================\n";
    cout << "   Best Fit Memory Allocation\n";
    cout << "=====================================\n";

    // Sample data - can be modified for user input
    vector<MemoryBlock> blocks = {
        {100, false, -1},
        {500, false, -1},
        {200, false, -1},
        {300, false, -1},
        {600, false, -1}
    };

    vector<Process> processes = {
        {1, 212},
        {2, 417},
        {3, 112},
        {4, 426}
    };

    cout << "Initial Memory Blocks:\n";
    displayMemory(blocks);

    cout << "\nProcesses to Allocate:\n";
    displayProcesses(processes);

    cout << "\nAllocating using Best Fit Algorithm:\n";
    bestFit(blocks, processes);

    cout << "\nFinal Memory State:\n";
    displayMemory(blocks);

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