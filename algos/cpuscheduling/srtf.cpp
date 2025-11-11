#include <bits/stdc++.h>
using namespace std;
struct Process{
    int id, BT, AT,RT;
};

class compare{
    public:
     bool operator()(Process a, Process b){
        if(a.RT==b.RT)
        return a.AT>b.AT;
        return a.RT>b.RT;
    }
};

int main(){
    priority_queue<Process, vector<Process>, compare> pq;

    cout<<"Enter number of processes: ";
    int n;
    cin>>n;
    vector<Process> all(n);
    cout<<"Enter arrival time and burst time for the following process: \n";
    for(int i=0;i<n;i++){
        Process t;
        cout<<"P"<<i+1<<": ";
        cin>>t.AT>>t.BT;
        t.RT=t.BT;
        t.id=i;
        all[i]=t;
    }
   
    sort(all.begin(), all.end(), [](Process &a, Process &b){
        return a.AT<b.AT;
    });


    vector<int> wt(n,0), tat(n,0), ct(n,0);
    int t=0,completed=0, index=0;

    while(completed<n){
        while(index<n && all[index].AT<=t){
            pq.push(all[index]);
            index++;
        }

        if(!pq.empty()){
            Process temp= pq.top();
            pq.pop();

            temp.RT--;
            t++;
            if(temp.RT==0){
                completed++;
                ct[temp.id]=t;
                tat[temp.id]= ct[temp.id]-temp.AT;
                wt[temp.id]= tat[temp.id]- temp.BT;
            }
            else{
                pq.push(temp);
            }
        }

        else  if(all[index].AT>t) t= all[index].AT;


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


