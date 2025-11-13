#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

void fcfsDiskScheduling() {
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
    
    for (int i = 0; i < requestQueue.size(); i++) {
        int request = requestQueue[i];
        int distance = abs(request - currentHead);
        totalHeadMovement += distance;
        
        cout << left << setw(10) << currentHead 
             << setw(10) << request 
             << setw(10) << distance << endl;
        
        currentHead = request;
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
    fcfsDiskScheduling();
    return 0;
}