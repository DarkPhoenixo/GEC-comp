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
    int processSize; 
};

void displayMemoryDiagram(const vector<MemoryBlock>& blocks) {
    cout << "\n+--------------------------------------------------+\n";
    cout << "|                Memory Diagram                    |\n";
    cout << "+--------------------------------------------------+\n";
    
    for (const auto& block : blocks) {
        cout << "| [";
        if (block.allocated) {
            cout << "P" << block.processId << " (" << block.processSize << "KB)";
            int internalFrag = block.size - block.processSize;
            if (internalFrag > 0) {
                cout << " | Free (" << internalFrag << "KB)";
            }
        } else {
            cout << "Free (" << block.size << "KB)";
        }
        cout << "] " << block.start << "-" << block.end << " KB" << setw(20) << "|\n";
    }
    cout << "+--------------------------------------------------+\n";
}

void displayFragmentation(const vector<MemoryBlock>& blocks) {
    int totalInternalFrag = 0;
    cout << "\nInternal Fragmentation Details:\n";
    cout << "+---------------------------------------------------------+\n";
    cout << "| Block | Process | Block Size | Process Size | Waste    |\n";
    cout << "+---------------------------------------------------------+\n";
    
    for (size_t i = 0; i < blocks.size(); ++i) {
        if (blocks[i].allocated) {
            int waste = blocks[i].size - blocks[i].processSize;
            totalInternalFrag += waste;
            cout << "| " << setw(5) << (i + 1) 
                 << " | " << setw(7) << ("P" + blocks[i].processId)
                 << " | " << setw(10) << blocks[i].size << " KB"
                 << " | " << setw(12) << blocks[i].processSize << " KB"
                 << " | " << setw(8) << waste << " KB |\n";
        }
    }
    cout << "+---------------------------------------------------------+\n";
    cout << "| Total Internal Fragmentation:           " << setw(15) << totalInternalFrag << " KB |\n";
    cout << "+---------------------------------------------------------+\n";
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
    if (approach == "fixed" || approach == "variable") {
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
            int processSize = 0;
            if (occupied) {
                cout << "Enter process ID: ";
                cin >> ws;
                getline(cin, pid);
                cout << "Enter process size in KB: ";
                cin >> processSize;
                if (processSize > size) {
                    cout << "Process size cannot exceed block size. Setting to block size.\n";
                    processSize = size;
                }
            }
            blocks.push_back({currentStart, currentStart + size, size, occupied, pid, processSize});
            currentStart += size;
        }
    } else {
        cout << "Invalid approach. Choose 'fixed' or 'variable'.\n";
        return 1;
    }

    cout << "\nInitial Memory Blocks:";
    displayMemoryDiagram(blocks);
    
    if (approach == "fixed") {
        displayFragmentation(blocks);
    }

    // Dynamic request loop
    while (true) {
        string ans;
        cout << "\nDo you have a request? (yes/no): ";
        cin >> ans;
        if (ans == "no") {
            break;
        }
        if (ans != "yes") {
            continue;
        }

        string pid;
        int size;
        cout << "Enter process ID: ";
        cin >> pid;
        cout << "Enter process size in KB: ";
        cin >> size;

        // Find best fit
        int bestIndex = -1;
        int minWaste = INT_MAX;
        for (size_t i = 0; i < blocks.size(); ++i) {
            if (!blocks[i].allocated && blocks[i].size >= size) {
                int waste = blocks[i].size - size;
                if (waste < minWaste) {
                    minWaste = waste;
                    bestIndex = i;
                }
            }
        }

        if (bestIndex != -1) {
            blocks[bestIndex].allocated = true;
            blocks[bestIndex].processId = pid;
            blocks[bestIndex].processSize = size;
            cout << "\nRequest granted. Allocated Process P" << pid << " (Size: " << size << " KB) to Block " << bestIndex + 1 << " (Start: " << blocks[bestIndex].start << " KB, End: " << blocks[bestIndex].end << " KB)\n";
            displayMemoryDiagram(blocks);
            
            if (approach == "fixed") {
                displayFragmentation(blocks);
            }
        } else {
            cout << "\nRequest rejected as it will cause external fragmentation.\n";
        }
    }

    cout << "\nThank you.\n";
    return 0;
}
