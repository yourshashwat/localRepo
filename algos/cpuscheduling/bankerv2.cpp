#include <iostream>
#include <vector>
using namespace std;

int main1() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    vector<vector<int>> Max(n, vector<int>(m));
    vector<vector<int>> Allocation(n, vector<int>(m));
    vector<vector<int>> Need(n, vector<int>(m));
    vector<int> Available(m);

    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> Allocation[i][j];

    cout << "\nEnter Max Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> Max[i][j];

    cout << "\nEnter Available Resources:\n";
    for (int j = 0; j < m; j++)
        cin >> Available[j];

    // Step 1: Calculate Need Matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    // Step 2: Initialize
    vector<bool> Finish(n, false);
    vector<int> SafeSeq;
    vector<int> Work = Available;

    int count = 0;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    // Process i can safely execute
                    for (int j = 0; j < m; j++)
                        Work[j] += Allocation[i][j];

                    SafeSeq.push_back(i);
                    Finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) break;
    }

    // Step 3: Check Safe State
    bool safe = true;
    for (int i = 0; i < n; i++)
        if (!Finish[i])
            safe = false;

    if (safe) {
        cout << "\nSystem is in a SAFE STATE.\nSafe Sequence: ";
        for (int i = 0; i < n; i++)
            cout << "P" << SafeSeq[i] << " ";
    } else {
        cout << "\nSystem is in an UNSAFE STATE!";
    }

    return 0;
}

int main(){

    int n,m;
    cout<<"ENter total number of processes: ";
    cin>>n;
    cout<<"Enter total number of resources: ";
    cin>>m;
    vector<int> available(n);
    cout<<"Enter total number of instances fo each resource: ";
    for(int i=0; i<m; i++){
        cin>>available[i];
    }

    vector<vector<int>> max(n, vector<int>(m));
    vector<vector<int>> allocated(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));

    cout<<"Enter max matrix: "<<endl;
    for(int i=0;i<n; i++){
        for(int j=0;j<m;j++){
            cin>>max[i][j];
        }
    }

    cout<<"Enter allocation matrix: "<<endl;
    for(int i=0;i<n; i++){
        for(int j=0;j<m;j++){
            cin>>allocated[i][j];
            available[j]-=allocated[i][j];
            need[i][j]= max[i][j]- allocated[i][j];
        }
    }

    int count=0;
    vector<bool> Finish(n,false);
    vector<int> safeSequence;
    while(count<n){
        bool found=false;
        for(int i=0;i<n; i++){
            if(!Finish[i]){
                bool canExecute=true;
                for(int j=0; j<m; j++){
                    if(need[i][j]>available[j]){
                        canExecute=false;
                        break;
                    }
                }

                if(canExecute){
                    for(int j=0; j<m; j++){
                        available[j]+=allocated[i][j];
                    }
                    found=true;
                    count++;
                    safeSequence.push_back(i);
                    Finish[i]= true;
                }
            }
        }
        if(!found) break;
    }

    bool safeState=true;
    for(int i=0; i<n; i++){
        if(Finish[i]==false){
            safeState=false;
            break;
        }
    }

    if(safeState){
        cout<<"System is in safe state";
        cout<<"\nOrder: ";
        for(int i=0; i<n; i++){
            cout<<safeSequence[i]<<"-> ";
        }
    }
    else{
        cout<<"System is not in safe state";
    }

    
    return 0;
}