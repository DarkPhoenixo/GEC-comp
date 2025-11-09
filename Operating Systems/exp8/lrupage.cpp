#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

// Function to simulate LRU Page Replacement Algorithm
void lruPageReplacement(const vector<int>& referenceString, int numFrames) {
    list<int> lruList; // front: most recent, back: least recent
    unordered_map<int, list<int>::iterator> pageMap;
    int pageFaults = 0;
    int hits = 0;

    // Print header
    cout << "\n=====================================\n";
    cout << "   LRU Page Replacement Algorithm\n";
    cout << "=====================================\n";
    cout << "Number of Frames: " << numFrames << endl;
    cout << "Reference String: ";
    for (int page : referenceString) {
        cout << page << " ";
    }
    cout << "\n\n";

    // Table header
    cout << left << setw(10) << "Reference" << setw(20) << "Frames" << setw(10) << "Status" << endl;
    cout << string(40, '-') << endl;

    // Process each page in the reference string
    for (int page : referenceString) {
        string status;
        vector<int> currentFrames;
        if (pageMap.find(page) != pageMap.end()) {
            // Page hit: move to front
            hits++;
            status = "Hit";
            lruList.erase(pageMap[page]);
            lruList.push_front(page);
            pageMap[page] = lruList.begin();
        } else {
            // Page fault
            pageFaults++;
            status = "Fault";
            if (lruList.size() == numFrames) {
                // Remove least recently used (back of list)
                int lru = lruList.back();
                lruList.pop_back();
                pageMap.erase(lru);
            }
            // Add new page to front
            lruList.push_front(page);
            pageMap[page] = lruList.begin();
        }

        // Collect current frames
        for (int p : lruList) {
            currentFrames.push_back(p);
        }
        // Pad to numFrames size
        while (currentFrames.size() < numFrames) {
            currentFrames.push_back(-1); // -1 indicates empty
        }

        // Build frames string
        string framesStr = "[";
        for (size_t j = 0; j < currentFrames.size(); ++j) {
            if (currentFrames[j] != -1) framesStr += to_string(currentFrames[j]);
            else framesStr += " ";
            if (j < currentFrames.size() - 1) framesStr += ",";
        }
        framesStr += "]";

        // Display row
        cout << left << setw(10) << page << left << setw(20) << framesStr << setw(10) << status << endl;
    }

    // Summary
    cout << "\n=====================================\n";
    cout << "Summary:\n";
    cout << "Total Page Faults: " << pageFaults << endl;
    cout << "Total Hits: " << hits << endl;
    cout << "Hit Ratio: " << fixed << setprecision(2) << (hits * 100.0) / referenceString.size() << "%" << endl;
    cout << "=====================================\n";
}

int main() {
    int numFrames;
    vector<int> referenceString;

    cout << "Enter the number of frames: ";
    cin >> numFrames;

    cout << "Enter the reference string (space-separated, end with -1): ";
    int page;
    while (cin >> page && page != -1) {
        referenceString.push_back(page);
    }

    if (referenceString.empty()) {
        cout << "No reference string provided. Exiting." << endl;
        return 1;
    }

    lruPageReplacement(referenceString, numFrames);

    return 0;
}
