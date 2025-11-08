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

void displayVisualDiagram(const vector<MemoryBlock>& blocks) {
    cout << "\n================  Memory Diagram ================\n";
    
    // Top border
    cout << "+";
    for (const auto& block : blocks) {
        int width = max(8, block.size / 10); // Scale width based on size
        for (int i = 0; i < width; ++i) cout << "-";
        cout << "+";
    }
    cout << "\n";
    
    // Block content (with hatching for allocated blocks)
    cout << "|";
    for (const auto& block : blocks) {
        int width = max(8, block.size / 10);
        if (block.allocated) {
            // Show hatching pattern for allocated blocks
            for (int i = 0; i < width; ++i) {
                cout << (i % 2 == 0 ? '/' : ' ');
            }
        } else {
            // Empty for free blocks
            for (int i = 0; i < width; ++i) cout << " ";
        }
        cout << "|";
    }
    cout << "\n";
    
    // Bottom border
    cout << "+";
    for (const auto& block : blocks) {
        int width = max(8, block.size / 10);
        for (int i = 0; i < width; ++i) cout << "-";
        cout << "+";
    }
    cout << "\n";
    
    // Position labels
    cout << " ";
    for (const auto& block : blocks) {
        int width = max(8, block.size / 10);
        cout << setw(width) << left << block.start << " ";
    }
    // Print the final end position
    if (!blocks.empty()) {
        cout << blocks.back().end;
    }
    cout << "\n";
    

    
    // Process details
    cout << "\nAllocated Processes:\n";
    for (size_t i = 0; i < blocks.size(); ++i) {
        if (blocks[i].allocated) {
            cout << "  Block " << (i + 1) << " [" << blocks[i].start << "-" << blocks[i].end 
                 << "]: Process " << blocks[i].processId << " (" << blocks[i].processSize << " KB)\n";
        }
    }
    cout << "=======================================================\n";
}

void allocateFixed(vector<MemoryBlock>& blocks, const string& pid, int size, int worstIndex) {
    blocks[worstIndex].allocated = true;
    blocks[worstIndex].processId = pid;
    blocks[worstIndex].processSize = size;
    cout << "Request granted. Allocated Process " << pid << " (Size: " << size << " KB, Wasted: " << (blocks[worstIndex].size - size) << " KB) to Block " << worstIndex + 1 << " (Start: " << blocks[worstIndex].start << ", End: " << blocks[worstIndex].end << ")\n";
    displayMemoryDiagram(blocks);
    displayVisualDiagram(blocks);
    // Calculate and display total internal fragmentation
    int totalWaste = 0;
    for (const auto& b : blocks) {
        if (b.allocated) {
            totalWaste += b.size - b.processSize;
        }
    }
    cout << "Total internal fragmentation: " << totalWaste << " KB\n";
}

void allocateVariable(vector<MemoryBlock>& blocks, const string& pid, int size, int worstIndex) {
    vector<MemoryBlock> newBlocks;
    for (size_t i = 0; i < blocks.size(); ++i) {
        if (i != worstIndex) {
            newBlocks.push_back(blocks[i]);
        } else {
            // Allocated part
            newBlocks.push_back({blocks[i].start, blocks[i].start + size, size, true, pid, size});
            // Free part if any
            if (blocks[i].size > size) {
                int remainingSize = blocks[i].size - size;
                newBlocks.push_back({blocks[i].start + size, blocks[i].end, remainingSize, false, "", 0});
            }
        }
    }
    blocks = newBlocks;
    cout << "Request granted. Allocated Process " << pid << " (Size: " << size << " KB) starting at " << blocks[worstIndex].start << " KB.\n";
    displayMemoryDiagram(blocks);
    displayVisualDiagram(blocks);
}

int main() {
    cout << "=====================================\n";
    cout << "   Worst Fit Memory Allocation\n";
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
            blocks.push_back({currentStart, currentStart + size, size, occupied, pid, occupied ? size : 0});
            currentStart += size;
        }
    } else {
        cout << "Invalid approach. Choose 'fixed' or 'variable'.\n";
        return 1;
    }

    cout << "Initial Memory Blocks:\n";
    displayMemoryDiagram(blocks);
    displayVisualDiagram(blocks);

    // Dynamic request loop
    int requestId = 1;
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

        cout << "\n====================================\n";
        cout << "         Request ID: " << requestId << "\n";
        cout << "====================================\n";

        string pid;
        int size;
        cout << "Enter process ID: ";
        cin >> pid;
        cout << "Enter process size in KB: ";
        cin >> size;

        // Find worst fit (largest free block that can fit)
        int worstIndex = -1;
        int maxSize = -1;
        for (size_t i = 0; i < blocks.size(); ++i) {
            if (!blocks[i].allocated && blocks[i].size >= size && blocks[i].size > maxSize) {
                maxSize = blocks[i].size;
                worstIndex = i;
            }
        }

        if (worstIndex != -1) {
            if (approach == "fixed") {
                allocateFixed(blocks, pid, size, worstIndex);
            } else if (approach == "variable") {
                allocateVariable(blocks, pid, size, worstIndex);
            }
        } else {
            cout << "Request rejected as it will cause external fragmentation.\n";
        }

        requestId++;
    }

    cout << "\nThank you.\n";
    return 0;
}