#include <bits/stdc++.h>
using namespace std;
struct Process{
    int id, BT, AT;
};

class compare{
    public:
     bool operator()(Process a, Process b){
        if(a.BT==b.BT)
        return a.AT>b.AT;
        return a.BT>b.BT;
    }
};

int main(){
    priority_queue<Process, vector<Process>, compare> pq;

    cout<<"Enter number of processes: ";
    int n;
    cin>>n;
    cout<<"Enter arrival time and burst time for the following process: \n";
    for(int i=0;i<n;i++){
        Process t;
        cout<<"P"<<i+1<<": ";
        cin>>t.AT>>t.BT;
        t.id=i;
        pq.push(t);
    }
    queue<Process> q;
    vector<int> wt(n,0), tat(n,0);
    int t=0;
    while(!pq.empty()){
        Process temp= pq.top();
        while(!pq.empty() && t<temp.AT){
            q.push(temp);
            pq.pop();
            temp= pq.top();
        }
        wt[temp.id]= t- temp.AT;
        t+= temp.BT;
        tat[temp.id]= t- temp.AT;

        pq.pop();
        while(!q.empty()){
            temp=q.front();
            pq.push(temp);
            q.pop();
        }
    }

    float totalWt=0, totalTat=0;
	
	cout<<"Process \t Waiting time\t Turn around time\n";
	for(int i=0;i<n; i++){
	    cout<<"P"<<i+1<<"\t\t"<<wt[i]<<"\t\t"<<tat[i]<<endl;
        totalWt+=wt[i];
        totalTat+=tat[i];
    }

    cout<<"Average Wating time: "<<totalWt/n<<endl;
    cout<<"Average Turn Around Time: "<<totalTat/n;

    return 0;
}