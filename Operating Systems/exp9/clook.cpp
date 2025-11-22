#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

void clookDiskScheduling() {
    int blockSize;
    cout << "Enter Total number of cylinder:  ";
    cin >> blockSize;
    
    cout << "Enter request queue (-1 to exit):" << endl;
    vector<int> requestQueue;
    int req;
    while (true) {
        cin >> req;
        if (req == -1) {
            break;
        }
        requestQueue.push_back(req);
    }
 
    int currentHead;
    cout << "Enter current head position: ";
    cin >> currentHead;
    
    int previousHead;
    cout << "Enter previous head position: ";
    cin >> previousHead;
 
    // Determine direction based on previousHead and currentHead
    string direction = (previousHead < currentHead) ? "right" : "left";
   
    vector<int> left, right;
    
    for (int i = 0; i < requestQueue.size(); i++) {
        if (requestQueue[i] < currentHead) {
            left.push_back(requestQueue[i]);
        } else {
            right.push_back(requestQueue[i]);
        }
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    cout << "\n" << string(40, '-') << endl;
    cout << std::left << setw(10) << "From" 
         << setw(10) << "To" 
         << setw(10) << "Distance" << endl;
    cout << string(40, '-') << endl;
 
    vector<int> trackSequence;
    trackSequence.push_back(previousHead);
    int totalHeadMovement = 0;
    vector<int> seekSequence;

    // Add initial movement from previousHead to currentHead
    int initialDistance = abs(currentHead - previousHead);
    totalHeadMovement += initialDistance;
    cout << std::left << setw(10) << previousHead 
         << setw(10) << currentHead 
         << setw(10) << initialDistance << endl;
    trackSequence.push_back(currentHead);

    if (direction == "right") {
        seekSequence.insert(seekSequence.end(), right.begin(), right.end());
        seekSequence.insert(seekSequence.end(), left.begin(), left.end());
    } else {
        reverse(left.begin(), left.end());
        seekSequence.insert(seekSequence.end(), left.begin(), left.end());
        reverse(right.begin(), right.end());
        seekSequence.insert(seekSequence.end(), right.begin(), right.end());
    }
    
    for (int i = 0; i < seekSequence.size(); i++) {
        int distance = abs(seekSequence[i] - currentHead);
        totalHeadMovement += distance;
        
        cout << std::left << setw(10) << currentHead 
             << setw(10) << seekSequence[i] 
             << setw(10) << distance << endl;
        
        currentHead = seekSequence[i];
        trackSequence.push_back(currentHead);
    }
    
    cout << string(40, '-') << endl;
    cout << "\nTrack sequence: ";
    for (int i = 0; i < trackSequence.size(); i++) {
        cout << trackSequence[i];
        if (i < trackSequence.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
    cout << "\nTotal head movement: " << totalHeadMovement << endl;
    cout << fixed << setprecision(2);
    cout << "Average seek time: " << (double)totalHeadMovement / requestQueue.size() << endl;
}

int main() {
    clookDiskScheduling();
    return 0;
}