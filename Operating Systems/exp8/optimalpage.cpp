#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

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

// Function to display the current state of frames
void displayFrames(const vector<int>& frames, int pageFaults) {
    cout << "| ";
    for (int frame : frames) {
        if (frame == -1) {
            cout << setw(3) << " " << " | ";
        } else {
            cout << setw(3) << frame << " | ";
        }
    }
    cout << "Page Faults: " << pageFaults << endl;
}

int main() {
    int numFrames, numReferences;
    
    cout << "=====================================" << endl;
    cout << "   Optimal Page Replacement Algorithm" << endl;
    cout << "=====================================" << endl;
    
    cout << "Enter the number of frames: ";
    cin >> numFrames;
    
    cout << "Enter the number of references: ";
    cin >> numReferences;
    
    vector<int> referenceString(numReferences);
    cout << "Enter the reference string: ";
    for (int i = 0; i < numReferences; ++i) {
        cin >> referenceString[i];
    }
    
    vector<int> frames(numFrames, -1);
    int pageFaults = 0;
    
    cout << "\nSimulation:\n";
    cout << "Reference | Frames" << string(numFrames * 6, ' ') << "| Page Faults\n";
    cout << "----------|" << string(numFrames * 6, '-') << "|------------\n";
    
    for (int i = 0; i < numReferences; ++i) {
        int page = referenceString[i];
        bool pageFound = false;
        
        // Check if page is already in frames
        for (int j = 0; j < numFrames; ++j) {
            if (frames[j] == page) {
                pageFound = true;
                break;
            }
        }
        
        if (!pageFound) {
            // Page fault
            pageFaults++;
            if (find(frames.begin(), frames.end(), -1) != frames.end()) {
                // Empty slot available
                *find(frames.begin(), frames.end(), -1) = page;
            } else {
                // Replace the optimal page
                int replaceIndex = findOptimalPage(frames, referenceString, i + 1);
                frames[replaceIndex] = page;
            }
        }
        
        // Display current state
        cout << setw(9) << page << " | ";
        displayFrames(frames, pageFaults);
    }
    
    cout << "\nTotal Page Faults: " << pageFaults << endl;
    cout << "Total Page Hits: " << (numReferences - pageFaults) << endl;
    
    return 0;
}