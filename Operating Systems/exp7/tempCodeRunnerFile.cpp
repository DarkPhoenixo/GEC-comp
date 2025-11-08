#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#define INT_MAX 2147483647

using namespace std;

// Structure for Memory Block
struct MemoryBlock {
    int start;
    int end;
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
    cout << "\n+-------------------+-------+-------+------------+\n";
    cout << "| Memory Block      | Start | End   | Process ID |\n";
    cout << "+-------------------+-------+-------+------------+\n";
    for (size_t i = 0; i < blocks.size(); ++i) {
        cout << "| Block " << setw(11) << i + 1 << " | " << setw(5) << blocks[i].start << " | " << setw(5) << blocks[i].end << " | ";
        if (blocks[i].allocated) {
            cout << setw(10) << blocks[i].processId << " |\n";
        } else {
            cout << setw(10) << "Free" << " |\n";
        }
    }
    cout << "+-------------------+-------+-------+------------+\n";
}

// Function to display a simple diagram of memory
void displayMemoryDiagram(const vector<MemoryBlock>& blocks) {
    cout << "\nMemory Diagram:\n";
    for (const auto& block : blocks) {
        cout << "[";
        if (block.allocated) {
            cout << "P" << block.processId << " (" << block.size << "KB)";
        } else {
            cout << "Free (" << block.size << "KB)";
        }
        cout << "] ";
    }
    cout << "\n";
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
        int blockSize;
        cout << "Enter block size in KB: ";
        cin >> blockSize;
        if (blockSize <= 0 || totalMemory % blockSize != 0) {
            cout << "Invalid block size. Must divide total memory evenly and be positive.\n";
            return 1;
        }
        int numBlocks = totalMemory / blockSize;
        for (int i = 0; i < numBlocks; ++i) {
            blocks.push_back({i * blockSize, (i + 1) * blockSize, blockSize, false, -1});
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
            int pid = -1;
            if (occupied) {
                cout << "Enter process ID: ";
                cin >> pid;
            }
            blocks.push_back({currentStart, currentStart + size, size, occupied, pid});
            currentStart += size;
        }
    } else {
        cout << "Invalid approach. Choose 'fixed' or 'variable'.\n";
        return 1;
    }

    cout << "Initial Memory Blocks:\n";
    displayMemory(blocks);
    displayMemoryDiagram(blocks);

    // Sample processes - can be modified for user input
    vector<Process> processes = {
        {1, 212},
        {2, 417},
        {3, 112},
        {4, 426}
    };

    cout << "\nProcesses to Allocate:\n";
    displayProcesses(processes);

    cout << "\nAllocating using Best Fit Algorithm:\n";
    bestFit(blocks, processes);

    cout << "\nFinal Memory State:\n";
    displayMemory(blocks);
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