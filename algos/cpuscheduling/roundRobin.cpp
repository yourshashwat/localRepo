#include <bits/stdc++.h>
using namespace std;

struct Process{
    int id, RT, BT;
};

int main(){
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;
    queue<Process> q;
    vector<Process> all(n);
    cout<<"Enter burst time for processes: \n";
    for(int i=0; i<n; i++){
        Process t;
        t.id=i;
        cout<<"P"<<i+1<<": ";
        cin>>t.BT;
        t.RT=t.BT;
        q.push(t);
        all[i]= t;
    }
    vector<int> wt(n,0), tat(n,0), ct(n,0);
    int t=0, tq=4;
    vector<int> order;
    while(!q.empty()){
        Process temp= q.front();
        q.pop();

        if(temp.RT>tq){
            t+=tq;
            temp.RT-=tq;
            q.push(temp);
            order.push_back(temp.id+1);
        }
        else{
            t+=temp.RT;
            temp.RT=0;
            order.push_back(temp.id+1);
            ct[temp.id]= t;
            tat[temp.id]= ct[temp.id];
            wt[temp.id]= tat[temp.id]- temp.BT;
        }
    }

    double avgWT = 0, avgTAT = 0;
    cout << "\nProcess\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t" << all[i].BT << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << (avgWT/n);
    cout << "\nAverage Turnaround Time: " << (avgTAT/n) << endl;

    return 0;
}