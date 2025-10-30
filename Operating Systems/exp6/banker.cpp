#include<iostream>
#include<iomanip>
#include<stdlib.h>
using namespace std;
int m, n, flag;
int allocation[10][10], max_v[10][10], need[10][10], available[10];
void safety()
{	int safe[n], work[m],k=0;
    bool finish[n];
             for(int i=0;i<n;i++)
             {    	safe[i]=-1;   		finish[i]=false;			}
    for(int i=0; i<m; i++)
        work[i] = available[i];
    do
    {	for(int i=0; i<n; i++)
        {	flag=0;
            for(int j=0; j<m; j++)
            { 	if(finish[i]==false && need[i][j]<=work[j])
                    continue;
                else
                    flag=1;						}
            if(flag==0)
            {	finish[i] = true;
                for(int j=0; j<m; j++)
                    work[j] = work[j] + allocation[i][j];
                    safe[k]=i; k++;						} 	}
        flag=0;
        for(int i=0; i<n; i++)
        {	if(finish[i]==false)
                flag=1;			}
        if(flag==0)
            break;
    }while(true);
    if(flag==0)
    {	cout<<"\nSafe Sequence: -> ";
        for(int j=0; j<n; j++)
            cout<<safe[j]<<" -> ";		}
    else
        cout<<"\nNo Safe sequence exists";
    cout<<endl;
}
void display()
{	int k=0;
    cout<<"\nAllocated\tMaximum\tAvail\tRequired"<<endl;
        for(int i=0;i<n;i++)
        {    	cout<<setiosflags(ios::right)<<" ";
        for(int j=0;j<m;j++)
            cout<<allocation[i][j]<<" ";
        cout<<setw(10);
        for(int j=0;j<m;j++)
            cout<<max_v[i][j]<<" ";
        cout<<setw(7);
        for(int j=0;j<m;j++)
        {	if(k==1)
            {	cout<<"  ";	continue;		}
            else
                cout<<available[j]<<" ";			}
        if(k==1)
            cout<<" ";
        cout<<setw(9);
        for(int j=0;j<m;j++)
            cout<<need[i][j]<<" ";
        k=1;
        cout<<endl;								    }
}
int main()
{    cout<<"Enter the number of Processes: ";
       cin>>n;
       cout<<"Enter the number of Resource types: ";
       cin>>m;
       cout<<"Enter Allocated Resources for each process:"<<endl;
       for(int i=0;i<n;i++)
       {    	cout<<"P"<<i<<": ";
    for(int j=0;j<m;j++)
        cin>>allocation[i][j];				    }
         cout<<"\nEnter max_v Resources for each process:"<<endl;
         for(int i=0;i<n;i++)
         {    	cout<<"R"<<i+1<<": ";
        for(int j=0;j<m;j++)
                        cin>>max_v[i][j];			    }
           cout<<"\nEnter Available Resources:"<<endl;
           for(int i=0;i<m;i++)
           cin>>available[i];
           for(int i=0;i<n;i++)
           {		for(int j=0;j<m;j++)
                need[i][j] = max_v[i][j] - allocation[i][j];	    }
    display();	safety();
    char ans='y';
    do
{	int request[m], p;
        cout<<"\n\nEnter Process Number: ";
        cin>>p;
        cout<<"Enter Request: ";
        for(int i=0; i<m; i++)
        {	cin>>request[i];	}
for(int i=0; i<m; i++)
        {	if(need[p][i]<request[i])
            {	cout<<"\nProcess exceeded maximum claim for resorces.\nRequest Cannot be granted"<<endl;
            exit(1);									}
            if(available[i]<request[i])
            {	cout<<"\nProcess must wait.Resorces not available."<<endl;
                exit(1);								}
        }
for(int i=0; i<m; i++)
            {    	available[i] -= request[i];
                allocation[p][i] += request[i];
        need[p][i] -= request[i];			}
        cout<<"\nTemporary"<<endl;
        int k=0;
    cout<<"\nAllocation\tAvailable\tNeed"<<endl;
    for(int i=0;i<n;i++)
    {    	cout<<setiosflags(ios::right)<<" ";
            for(int j=0;j<m;j++)
            cout<<allocation[i][j]<<" ";
            cout<<setw(11);
            for(int j=0;j<m;j++)
            {	if(k==1)
                {	cout<<"  ";	continue;	}
                else
                    cout<<available[j]<<" ";			}
            if(k==1)
                cout<<" ";
            cout<<setw(9);
            for(int j=0;j<m;j++)
            cout<<need[i][j]<<" ";
            k=1;
            cout<<endl;								    }
        safety();
        if(flag==1)
        {	cout<<"\n request cannot be granted"<<endl;
            for(int i=0; i<m; i++)
            {	available[i] += request[i];
                    allocation[p][i] -= request[i];
                    need[p][i] += request[i];		}
            cout<<"\nStates Restored:"<<endl;
            display();							}
        else
        {	cout<<"\nSafe Sequence Exists and request can be granted immediately to process.\nSnapshot after request:\n";
            display();							}
        cout<<"\n\nTry another Process?(Y/N)";
        cin>>ans;
}while(ans=='y' || ans=='Y');
}