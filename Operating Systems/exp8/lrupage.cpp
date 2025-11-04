#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <iomanip>

using namespace std;

// Function to simulate LRU Page Replacement
void simulateLRU(int frames, const vector<int>& referenceString) {
    list<int> pageList; // To maintain order of pages (most recently used at front)
    unordered_map<int, list<int>::iterator> pageMap; // To quickly find pages in the list
    int pageFaults = 0;
    vector<vector<int>> states; // To store states for display

    cout << "\n=== LRU Page Replacement Simulation ===\n";
    cout << "Number of Frames: " << frames << "\n";
    cout << "Reference String: ";
    for (int page : referenceString) {
        cout << page << " ";
    }
    cout << "\n\n";

    // Table header
    cout << left << setw(10) << "Step" << setw(15) << "Page" << setw(20) << "Frames" << setw(15) << "Fault?" << "\n";
    cout << string(60, '-') << "\n";

    for (size_t i = 0; i < referenceString.size(); ++i) {
        int page = referenceString[i];
        vector<int> currentFrames;

        // Check if page is already in memory
        if (pageMap.find(page) != pageMap.end()) {
            // Page hit: move to front
            pageList.erase(pageMap[page]);
            pageList.push_front(page);
            pageMap[page] = pageList.begin();
            // Collect current frames
            for (int p : pageList) {
                currentFrames.push_back(p);
            }
            // Pad to frames size
            while (currentFrames.size() < static_cast<size_t>(frames)) {
                currentFrames.push_back(-1); // -1 indicates empty
            }
            states.push_back(currentFrames);
            // Display
            cout << left << setw(10) << (i + 1) << setw(15) << page;
            cout << "[";
            for (size_t j = 0; j < currentFrames.size(); ++j) {
                if (currentFrames[j] != -1) cout << currentFrames[j];
                else cout << " ";
                if (j < currentFrames.size() - 1) cout << ",";
            }
            cout << "]" << setw(15) << "No" << "\n";
        } else {
            // Page fault
            pageFaults++;
            if (pageList.size() == static_cast<size_t>(frames)) {
                // Remove least recently used (back of list)
                int lru = pageList.back();
                pageList.pop_back();
                pageMap.erase(lru);
            }
            // Add new page to front
            pageList.push_front(page);
            pageMap[page] = pageList.begin();
            // Collect current frames
            for (int p : pageList) {
                currentFrames.push_back(p);
            }
            // Pad to frames size
            while (currentFrames.size() < static_cast<size_t>(frames)) {
                currentFrames.push_back(-1);
            }
            states.push_back(currentFrames);
            // Display
            cout << left << setw(10) << (i + 1) << setw(15) << page;
            cout << "[";
            for (size_t j = 0; j < currentFrames.size(); ++j) {
                if (currentFrames[j] != -1) cout << currentFrames[j];
                else cout << " ";
                if (j < currentFrames.size() - 1) cout << ",";
            }
            cout << "]" << setw(15) << "Yes" << "\n";
        }
    }

    cout << "\nTotal Page Faults: " << pageFaults << "\n";
    cout << "Page Fault Rate: " << fixed << setprecision(2) << (static_cast<double>(pageFaults) / referenceString.size()) * 100 << "%\n";
    cout << "=== Simulation Complete ===\n";
}

int main() {
    int frames;
    cout << "Enter the number of page frames: ";
    cin >> frames;

    int n;
    cout << "Enter the number of pages in reference string: ";
    cin >> n;

    vector<int> referenceString(n);
    cout << "Enter the reference string (space-separated): ";
    for (int i = 0; i < n; ++i) {
        cin >> referenceString[i];
    }

    simulateLRU(frames, referenceString);

    return 0;
}