#include<iostream>
#include<iomanip>

using namespace std;

int main(){
    int n1, n2;
    
    cout << "Enter number of blocks" << endl;
    cin >> n1;
    
    int mem_block[n1], original_block[n1];
    bool filled[n1] = {false};
    
    cout << "Enter block size" << endl;
    for(int i = 0; i < n1; i++){
        cin >> mem_block[i];
        original_block[i] = mem_block[i];
    }
    
    cout << "Enter number of processes" << endl;
    cin >> n2;
    
    int process[n2];
    int allocation[n2];
    
    cout << "Enter process size" << endl;
    for(int i = 0; i < n2; i++){
        cin >> process[i];
        allocation[i] = -1;  // -1 means not allocated
    }
    
    // First Fit Algorithm
    for(int i = 0; i < n2; i++){
        for(int j = 0; j < n1; j++){
            if(mem_block[j] >= process[i]){
                allocation[i] = j;
                mem_block[j] -= process[i];
                break;
            }
        }
    }
    
    // Display output
    cout << "\nMemory Size:\t\t";
    for(int i = 0; i < n1; i++){
        cout << original_block[i] << "\t";
    }
    cout << endl;
    
    cout << "Process:\t\t";
    for(int i = 0; i < n1; i++){
        bool found = false;
        for(int j = 0; j < n2; j++){
            if(allocation[j] == i){
                cout << "P" << (j+1) << "(" << process[j] << ")\t";
                found = true;
                break;
            }
        }
        if(!found){
            cout << "\t";
        }
    }
    cout << endl;
    
    cout << "Storage Available:\t";
    for(int i = 0; i < n1; i++){
        cout << mem_block[i] << "\t";
    }
    cout << endl;
    

    int total_available = 0;
    for(int i = 0; i < n1; i++){
        total_available += mem_block[i];
    }
    
    cout << "\nTotal Storage Available: " << total_available << endl;

    cout << "\n---------------------------------" << endl;
    for(int i = 0; i < n2; i++){
        if(allocation[i] != -1){
            cout << "Process " << (i+1) << " of " << process[i] 
                 << "KB will be put in " << original_block[allocation[i]] 
                 << "KB -> " << mem_block[allocation[i]] << "KB will be left" << endl;
        } else {
            cout << "Process " << (i+1) << " of " << process[i] 
                 << "KB cannot be allocated" << endl;
        }
    }
    cout << "---------------------------------" << endl;
    
    return 0;
}