#include <bits/stdc++.h>
using namespace std;

struct Process{
    int id,rt,bt,at,ct,tat,pr,wt;
};

int main(){

     int n;
     cout<<"ENter number of processes: ";
     cin>>n;
    vector<Process> all(n);
     cout<<"Enter arrival time, burst time and priority for each process.\n";
     for(int i=0; i<n; i++){
        cout<<"P"<<i<<": ";
        cin>>all[i].at>>all[i].bt>>all[i].pr;
        all[i].rt=all[i].bt;
        all[i].id=i;
        
     }

     sort(all.begin(), all.end(), [](const Process &a, const Process &b){
        return a.at<b.at;
     });
     vector<int> gc;
     queue<int> q1,q2;
     int time=0, tq=3, completed=0,idx=0;
     while(completed<n){

        while(idx<n && all[idx].at<=time){
            if(all[idx].pr==1) q1.push(idx);
            else q2.push(idx);
            idx++;
        }
        if(!q1.empty()){
            int pid=q1.front();
            q1.pop();
            Process &p= all[pid];
            if(p.rt>tq){
                time+=tq;
                p.rt-=tq;
                while(idx<n && all[idx].at<=time){
                if(all[idx].pr==1) q1.push(idx);
                else q2.push(idx);
                idx++;
            }
            gc.push_back(p.id);
            q1.push(pid);
            
        }
            else{
                time+=p.rt;
                p.ct=time;
                p.rt=0;
                completed++;
                gc.push_back(p.id);
                p.tat= p.ct-p.at;
                p.wt=p.tat-p.bt;

            }

            
        }
        else if(!q2.empty()){
            int pid=q2.front();
            Process &p= all[pid];
            q2.pop();
            time+=p.rt;
            p.ct=time;
            p.rt=0;
            completed++;
            gc.push_back(p.id);
            p.tat= p.ct-p.at;
            p.wt=p.tat-p.bt;
            while(idx<n && all[idx].at<=time){
                if(all[idx].pr==1) q1.push(idx);
                else q2.push(idx);
                idx++;
            }

        }
        else{
            time=all[idx].at;
        }

     }

        sort(all.begin(), all.end(), [](const Process &a, const Process &b){
            return a.id<b.id;
        });

    cout<<"Gantt Chart:\n";
    for(int id: gc){
        cout<<"P"<<id+1<<" ";
    }
    cout<<endl;
    cout<<"Process\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i=0;i<n; i++){
        cout<<"P"<<i+1<<"\t"<<all[i].at<<"\t"<<all[i].bt<<"\t"<<all[i].ct<<"\t"<<all[i].tat<<"\t"<<all[i].wt<<"\n";
    }

    // Calculate average TAT and WT
    double totalTAT=0, totalWT=0;
    for(int i=0; i<n; i++){
        totalTAT+=all[i].tat;
        totalWT+=all[i].wt;
    }
    cout<<"Average Turn Around Time: "<<totalTAT/n<<endl;
    cout<<"Average Waiting Time: "<<totalWT/n<<endl;

    return 0;
}