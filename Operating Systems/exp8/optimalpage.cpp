#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Function to find the page that will not be used for the longest time
int findOptimalPage(const vector<int>& frames, const vector<int>& referenceString, int currentIndex) {
    int farthest = currentIndex;
    int pageToReplace = -1;
    
    for (int i = 0; i < frames.size(); ++i) {
        int j;
        for (j = currentIndex; j < referenceString.size(); ++j) {
            if (frames[i] == referenceString[j]) {
                if (j > farthest) {
                    farthest = j;
                    pageToReplace = i;
                }
                break;
            }
        }
        if (j == referenceString.size()) {
            return i; // Page not used again
        }
    }
    return (pageToReplace == -1) ? 0 : pageToReplace;
}

// Function to simulate Optimal Page Replacement Algorithm
void optimalPageReplacement(const vector<int>& referenceString, int numFrames) {
    vector<int> frames(numFrames, -1);
    int pageFaults = 0;
    int hits = 0;

    // Print header
    cout << "\n=====================================\n";
    cout << "   Optimal Page Replacement Algorithm\n";
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
    for (size_t i = 0; i < referenceString.size(); ++i) {
        int page = referenceString[i];
        string status;
        vector<int> currentFrames = frames;
        bool pageFound = false;
        
        // Check if page is already in frames
        for (int j = 0; j < numFrames; ++j) {
            if (frames[j] == page) {
                pageFound = true;
                break;
            }
        }
        
        if (pageFound) {
            hits++;
            status = "Hit";
        } else {
            // Page fault
            pageFaults++;
            status = "Fault";
            auto it = find(frames.begin(), frames.end(), -1);
            if (it != frames.end()) {
                // Empty slot available
                *it = page;
            } else {
                // Replace the optimal page
                int replaceIndex = findOptimalPage(frames, referenceString, i + 1);
                frames[replaceIndex] = page;
            }
            currentFrames = frames;
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

    optimalPageReplacement(referenceString, numFrames);

    return 0;
}