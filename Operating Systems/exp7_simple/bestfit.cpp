#include<iostream>
#include<iomanip>
#define max 9999

using namespace std;

int mem_block[10];
float process[10];
bool filled[10];
int flag;

int main(){
	int n1,n2;
	cout<<"\nEnter the number of Memory Blocks: ";
    cin>>n1;
    float alloc[n1], unalloc[n1];
    int original_block[n1];
    int allocation[10];  // To track which block each process is allocated to
    
    cout<<"\nEnter the size of each Block in KB:"<<endl;
    for(int i=0;i<n1;i++){      
        cout<<"Block "<<i+1<<": ";
        cin>>mem_block[i];
        original_block[i] = mem_block[i];
        alloc[i]=0;
        unalloc[i]=0;
        filled[i]=false;
   	}
    
    cout<<"\nEnter the number of processes: ";
    cin>>n2;
    cout<<"\nEnter the size of each Process in KB:"<<endl;
    for(int i=0;i<n2;i++){      
        cout<<"Process "<<i+1<<" : ";
        cin>>process[i];
        allocation[i] = -1;  // -1 means not allocated
    }
    
    //best_fit
    int k=0, best, index;
    for(int i=0; i<n2; i++){
        best=max;
        for(int j=0; j<n1; j++){
            if(process[i]<=mem_block[j] && mem_block[j]<best && filled[j]==false){
                best=mem_block[j];
                index=j;	
            }
        }
        if(best!=max){
            alloc[index]=process[i];
            filled[index]=true;
            allocation[i] = index;  // Store which block this process got
            mem_block[index] -= process[i];  // Calculate remaining space
        }
        else{
            flag=1;
            unalloc[k]=process[i];
            k++;
        }
    }
    
    cout<<"\n---- BEST FIT ALGORITHM ----"<<endl;
    cout<<"\nMemory Block -- Process"<<endl;
    for(int i=0;i<n1;i++){      
        cout<<original_block[i];
        cout<<"\t\t";
        if(alloc[i]==0)
            cout<<"X";
        else
            cout<<alloc[i];
        cout<<endl;
    }
    
    if(flag==1){
        cout<<"\n-----------------------------"<<endl;
        cout<<"\nUnallocated Processes:"<<endl;
        for(int i=0; i<k;i++)
            cout<<unalloc[i]<<" KB"<<endl;
    }
    
    // Print allocation details
    cout<<"\n-----------------------------"<<endl;
    for(int i=0; i<n2; i++){
        if(allocation[i] != -1){
            cout<<"Process "<<(i+1)<<" of "<<process[i]
                <<"KB will be put in "<<original_block[allocation[i]]
                <<"KB -> "<<mem_block[allocation[i]]
                <<"KB will be left"<<endl;
        } else {
            cout<<"Process "<<(i+1)<<" of "<<process[i]
                <<"KB cannot be allocated"<<endl;
        }
    }
    cout<<"-----------------------------"<<endl;
    
    return 0;
}