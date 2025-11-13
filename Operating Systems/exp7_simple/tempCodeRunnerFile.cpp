#include<iostream>
#include<iomanip>

using namespace std;

int main(){
    int n1, n2;
    
    cout << "Enter no of memory blocks : ";
    cin >> n1;
    
    int mem_block[n1];
    int original_block[n1];
    
    cout << "Enter size of each blocks :" << endl;
    for(int i = 0; i < n1; i++){
        cin >> mem_block[i];
        original_block[i] = mem_block[i];
    }
    
    cout << "Enter no of processes : ";
    cin >> n2;
    
    int process[n2];
    int allocation[n2];
    
    cout << "Enter size of each processes :" << endl;
    for(int i = 0; i < n2; i++){
        cin >> process[i];
        allocation[i] = -1;  // -1 means not allocated
    }
    
    // Worst Fit Algorithm
    for(int i = 0; i < n2; i++){
        int worst_idx = -1;
        int worst_size = -1;
        
        for(int j = 0; j < n1; j++){
            if(mem_block[j] >= process[i]){
                if(mem_block[j] > worst_size){
                    worst_size = mem_block[j];
                    worst_idx = j;
                }
            }
        }
        
        if(worst_idx != -1){
            allocation[i] = worst_idx;
            mem_block[worst_idx] -= process[i];
        }
    }
    
    // Display output
    cout << "Worst Fit" << endl;
    cout << "\nProcess No.\tProcess Size\tBlock no." << endl;
    
    for(int i = 0; i < n2; i++){
        cout << "   " << (i+1) << "\t\t   " << process[i] << "\t\t";
        if(allocation[i] != -1){
            cout << (allocation[i] + 1) << endl;
        } else {
            cout << "Not Allocated" << endl;
        }
    }
    
    cout << "\n------------------------------------" << endl;
    
    // Print allocation details
    for(int i = 0; i < n2; i++){
        if(allocation[i] != -1){
            cout << "Process " << (i+1) << " of " << process[i]
                 << "KB will be put in " << original_block[allocation[i]]
                 << "KB -> " << mem_block[allocation[i]]
                 << "KB will be left" << endl;
        } else {
            cout << "Process " << (i+1) << " of " << process[i]
                 << "KB cannot be allocated" << endl;
        }
    }
    cout << "------------------------------------" << endl;
    
    return 0;
}