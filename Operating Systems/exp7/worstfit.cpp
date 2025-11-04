#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Structure for Memory Block
struct MemoryBlock {
    int size;
    int allocatedTo; // Process ID, -1 if free
    MemoryBlock(int s) : size(s), allocatedTo(-1) {}
};

// Structure for Process
struct Process {
    int id;
    int size;
    Process(int i, int s) : id(i), size(s) {}
};

// Function to display memory blocks in a table
void displayMemory(const vector<MemoryBlock>& blocks) {
    cout << "\n+----------------+------------+------------------+" << endl;
    cout << "| Block Index    | Size       | Allocated To     |" << endl;
    cout << "+----------------+------------+------------------+" << endl;
    for (size_t i = 0; i < blocks.size(); ++i) {
        cout << "| " << setw(14) << i << " | " << setw(10) << blocks[i].size << " | " << setw(16) << (blocks[i].allocatedTo == -1 ? "Free" : "Process " + to_string(blocks[i].allocatedTo)) << " |" << endl;
    }
    cout << "+----------------+------------+------------------+" << endl;
}

// Function to display processes
void displayProcesses(const vector<Process>& processes) {
    cout << "\n+------------+------------+------------------+" << endl;
    cout << "| Process ID | Size       | Allocation Status|" << endl;
    cout << "+------------+------------+------------------+" << endl;
    for (const auto& p : processes) {
        cout << "| " << setw(10) << p.id << " | " << setw(10) << p.size << " | " << setw(16) << "Pending" << " |" << endl;
    }
    cout << "+------------+------------+------------------+" << endl;
}

// Worst Fit Allocation Function
void worstFit(vector<MemoryBlock>& blocks, vector<Process>& processes) {
    for (auto& process : processes) {
        // Find the largest block that can fit the process
        int bestIndex = -1;
        int maxSize = -1;
        for (size_t i = 0; i < blocks.size(); ++i) {
            if (blocks[i].allocatedTo == -1 && blocks[i].size >= process.size && blocks[i].size > maxSize) {
                maxSize = blocks[i].size;
                bestIndex = i;
            }
        }
        if (bestIndex != -1) {
            blocks[bestIndex].allocatedTo = process.id;
            blocks[bestIndex].size -= process.size; // Reduce the block size
            cout << "Process " << process.id << " (Size: " << process.size << ") allocated to Block " << bestIndex << endl;
        } else {
            cout << "Process " << process.id << " (Size: " << process.size << ") could not be allocated." << endl;
        }
    }
}

int main() {
    cout << "=====================================" << endl;
    cout << "  Worst Fit Memory Allocation Simulator" << endl;
    cout << "=====================================" << endl;

    int numBlocks, numProcesses;
    cout << "Enter number of memory blocks: ";
    cin >> numBlocks;
    vector<MemoryBlock> blocks;
    for (int i = 0; i < numBlocks; ++i) {
        int size;
        cout << "Enter size of block " << i << ": ";
        cin >> size;
        blocks.emplace_back(size);
    }

    cout << "\nEnter number of processes: ";
    cin >> numProcesses;
    vector<Process> processes;
    for (int i = 0; i < numProcesses; ++i) {
        int size;
        cout << "Enter size of process " << i << ": ";
        cin >> size;
        processes.emplace_back(i, size);
    }

    displayMemory(blocks);
    displayProcesses(processes);

    cout << "\nAllocating processes using Worst Fit Algorithm..." << endl;
    worstFit(blocks, processes);

    cout << "\nFinal Memory State:" << endl;
    displayMemory(blocks);

    return 0;
}