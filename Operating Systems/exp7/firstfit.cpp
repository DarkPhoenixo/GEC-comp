#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

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
    int blockIndex; // -1 if not allocated
};

// Function to display memory blocks in a table
void displayMemory(const vector<MemoryBlock>& blocks, const string& title) {
    cout << "\n" << string(50, '=') << "\n";
    cout << title << "\n";
    cout << string(50, '=') << "\n";
    cout << left << setw(10) << "Block" << setw(10) << "Size" << setw(12) << "Allocated" << "Process ID\n";
    cout << string(50, '-') << "\n";
    for (size_t i = 0; i < blocks.size(); ++i) {
        cout << left << setw(10) << i + 1
             << setw(10) << blocks[i].size
             << setw(12) << (blocks[i].allocated ? "Yes" : "No")
             << (blocks[i].allocated ? to_string(blocks[i].processId) : "N/A") << "\n";
    }
    cout << string(50, '=') << "\n";
}

// Function to display processes in a table
void displayProcesses(const vector<Process>& processes, const string& title) {
    cout << "\n" << string(50, '=') << "\n";
    cout << title << "\n";
    cout << string(50, '=') << "\n";
    cout << left << setw(10) << "Process" << setw(10) << "Size" << setw(12) << "Allocated" << "Block Index\n";
    cout << string(50, '-') << "\n";
    for (const auto& p : processes) {
        cout << left << setw(10) << p.id
             << setw(10) << p.size
             << setw(12) << (p.allocated ? "Yes" : "No")
             << (p.allocated ? to_string(p.blockIndex + 1) : "N/A") << "\n";
    }
    cout << string(50, '=') << "\n";
}

// First Fit Memory Allocation Algorithm
void firstFit(vector<MemoryBlock>& blocks, vector<Process>& processes) {
    for (auto& process : processes) {
        for (size_t i = 0; i < blocks.size(); ++i) {
            if (!blocks[i].allocated && blocks[i].size >= process.size) {
                blocks[i].allocated = true;
                blocks[i].processId = process.id;
                process.allocated = true;
                process.blockIndex = i;
                break;
            }
        }
    }
}

int main() {
    int numBlocks, numProcesses;
    
    cout << "First Fit Memory Allocation Simulator\n";
    cout << "=====================================\n";
    
    // Input number of memory blocks
    cout << "Enter the number of memory blocks: ";
    cin >> numBlocks;
    
    vector<MemoryBlock> blocks(numBlocks);
    cout << "Enter the sizes of the memory blocks:\n";
    for (int i = 0; i < numBlocks; ++i) {
        cout << "Block " << i + 1 << ": ";
        cin >> blocks[i].size;
        blocks[i].allocated = false;
        blocks[i].processId = -1;
    }
    
    // Input number of processes
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    
    vector<Process> processes(numProcesses);
    cout << "Enter the sizes of the processes:\n";
    for (int i = 0; i < numProcesses; ++i) {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << ": ";
        cin >> processes[i].size;
        processes[i].allocated = false;
        processes[i].blockIndex = -1;
    }
    
    // Display initial state
    displayMemory(blocks, "Initial Memory Blocks");
    displayProcesses(processes, "Initial Processes");
    
    // Perform First Fit Allocation
    firstFit(blocks, processes);
    
    // Display final state
    displayMemory(blocks, "Memory Blocks After Allocation");
    displayProcesses(processes, "Processes After Allocation");
    
    cout << "\nAllocation complete!\n";
    return 0;
}