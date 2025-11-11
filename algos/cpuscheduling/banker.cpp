#include <bits/stdc++.h>
using namespace std;

struct Process{
    int id;
    vector<int> maxDemand, allocated, need;
};



int main(){
    int n, r;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> r;

    cout << "Enter max available resources: ";
    vector<int> max_available(r), available(r);
    for(int i = 0; i < r; i++){
    cin >> max_available[i];
    available[i] = max_available[i]; // initially same as max_available
    }

    vector<Process> p(n);

    cout<<"Enter maximum demand and current allocated resources for each process: \n";
    
    for(int i=0; i<n; i++){
        cout<<"Max demand \n P "<<i<<": ";
        for(int j=0; j<r; j++){
            int x; cin>>x;
            p[i].maxDemand.push_back(x);
        }

        cout<<"Current allocation \n P "<<i<<": ";
        for(int j=0; j<r; j++){
            int x; cin>>x;
            p[i].allocated.push_back(x);
            p[i].need.push_back(p[i].maxDemand[j]-p[i].allocated[j]);
            available[j]-=x;
        }

       p[i].id=i;
    }

    



    return 0;
}