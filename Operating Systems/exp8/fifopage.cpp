#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <iomanip>
#include <string>

using namespace std;

// Function to simulate FIFO Page Replacement Algorithm
void fifoPageReplacement(const vector<int>& referenceString, int numFrames) {
    queue<int> fifoQueue;  // Queue to maintain the order of pages in frames
    set<int> frames;       // Set to quickly check if a page is in frames
    int pageFaults = 0;
    int hits = 0;

    // Print header
    cout << "\n=====================================\n";
    cout << "   FIFO Page Replacement Algorithm\n";
    cout << "=====================================\n";
    cout << "Number of Frames: " << numFrames << endl;
    cout << "Reference String: ";
    for (int page : referenceString) {
        cout << page << " ";
    }
    cout << "\n\n";

    // Table header
    cout << left << setw(10) << "Reference" << setw(15) << "Frames" << setw(10) << "Status" << endl;
    cout << string(35, '-') << endl;

    // Process each page in the reference string
    for (int page : referenceString) {
        string status;
        if (frames.find(page) != frames.end()) {
            // Page hit
            hits++;
            status = "Hit";
        } else {
            // Page fault
            pageFaults++;
            status = "Fault";
            if (frames.size() == numFrames) {
                // Remove the oldest page
                int oldest = fifoQueue.front();
                fifoQueue.pop();
                frames.erase(oldest);
            }
            // Add new page
            frames.insert(page);
            fifoQueue.push(page);
        }

        // Display current frames
        cout << left << setw(10) << page;
        cout << "[";
        for (int f : frames) {
            cout << f << " ";
        }
        cout << "]" << setw(10) << status << endl;
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

    fifoPageReplacement(referenceString, numFrames);

    return 0;
}