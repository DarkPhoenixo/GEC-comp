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
    cout << "\n================ Memory Layout ================\n";
    for (size_t i = 0; i < blocks.size(); ++i) {
        const auto& block = blocks[i];
        cout << "Block " << (i + 1) << ": [" << block.start << " - " << block.end << "] ";
        if (block.allocated) {
            cout << "Allocated to Process " << block.processId << " (Used: " << block.processSize << " KB, Block Size: " << block.size << " KB)\n";
        } else {
            cout << "Free (Size: " << block.size << " KB)\n";
        }
    }
    cout << "===============================================\n";
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
            if (occupied) {
                cout << "Enter process ID: ";
                cin >> ws;
                getline(cin, pid);
            }
            blocks.push_back({currentStart, currentStart + size, size, occupied, pid, occupied ? size : 0}); // processSize set to block size if occupied, else 0
            currentStart += size;
        }
    } else {
        cout << "Invalid approach. Choose 'fixed' or 'variable'.\n";
        return 1;
    }

    cout << "Initial Memory Blocks:\n";
    displayMemoryDiagram(blocks);

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
            cout << "Request granted. Allocated Process " << pid << " (Size: " << size << " KB, Wasted: " << (blocks[bestIndex].size - size) << " KB) to Block " << bestIndex + 1 << " (Start: " << blocks[bestIndex].start << ", End: " << blocks[bestIndex].end << ")\n";
            displayMemoryDiagram(blocks);
            if (approach == "fixed") {
                // Calculate and display total internal fragmentation
                int totalWaste = 0;
                for (const auto& b : blocks) {
                    if (b.allocated) {
                        totalWaste += b.size - b.processSize;
                    }
                }
                cout << "Total internal fragmentation: " << totalWaste << " KB\n";
            }
        } else {
            cout << "Request rejected as it will cause external fragmentation.\n";
        }
    }

    cout << "\nThank you.\n";
    return 0;
}
