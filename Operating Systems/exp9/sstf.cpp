#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <climits>
using namespace std;

void sstfDiskScheduling() {
    int blockSize;
    cout << "Enter block size: ";
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
    
    cout << "\n" << string(40, '-') << endl;
    cout << left << setw(10) << "From" 
         << setw(10) << "To" 
         << setw(10) << "Distance" << endl;
    cout << string(40, '-') << endl;
    
    vector<int> trackSequence;
    trackSequence.push_back(currentHead);
    int totalHeadMovement = 0;
    
    vector<bool> serviced(requestQueue.size(), false);
    
    for (int i = 0; i < requestQueue.size(); i++) {
        int minDistance = INT_MAX;
        int closestIndex = -1;
        
        for (int j = 0; j < requestQueue.size(); j++) {
            if (!serviced[j]) {
                int distance = abs(requestQueue[j] - currentHead);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestIndex = j;
                }
            }
        }
        
        if (closestIndex != -1) {
            int request = requestQueue[closestIndex];
            serviced[closestIndex] = true;
            totalHeadMovement += minDistance;
            
            cout << left << setw(10) << currentHead 
                 << setw(10) << request 
                 << setw(10) << minDistance << endl;
            
            currentHead = request;
            trackSequence.push_back(currentHead);
        }
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
    
    // Print results
    cout << "\nTotal head movement: " << totalHeadMovement << endl;
    cout << fixed << setprecision(2);
    cout << "Average seek time: " << (double)totalHeadMovement / requestQueue.size() << endl;
}

int main() {
    sstfDiskScheduling();
    return 0;
}