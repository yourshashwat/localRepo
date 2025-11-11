#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id, at, bt, rt, ct,tat,wt;
};

int main1() {
    cout << "Enter number of processes: ";
    int n;
    cin >> n;

    vector<Process> all(n);
    cout << "Enter arrival time and burst time for the following process:\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << ": ";
        cin >> all[i].at >> all[i].bt;
        all[i].id = i;
        all[i].rt = all[i].bt;
        all[i].ct = 0;
    }

    sort(all.begin(), all.end(), [](const Process &a, const Process &b) {
        return a.at < b.at;
    });

    cout << "Enter time quantum: ";
    int tq;
    cin >> tq;

    queue<int> q; // store indices instead of process copies
    int time = 0, completed = 0, index = 0;
    vector<int> order;

    while (completed != n) {
        // push newly arrived processes
        while (index < n && all[index].at <= time) {
            q.push(index);
            index++;
        }

        // if queue is empty, move time to next process arrival
        if (q.empty()) {
            if (index < n)
                time = all[index].at;
            continue;
        }

        int pid = q.front();
        q.pop();
        Process &p = all[pid];

        // execute for tq or remaining time
        if (p.rt > tq) {
            p.rt -= tq;
            time += tq;
            // push newly arrived processes during this time window
            while (index < n && all[index].at <= time) {
                q.push(index);
                index++;
            }
            q.push(pid); // requeue the same process
        } else {
            time += p.rt;
            p.rt = 0;
            p.ct = time;
            completed++;
            order.push_back(p.id + 1); // store process order
        }
    }

    // restore original order by id
    sort(all.begin(), all.end(), [](const Process &a, const Process &b) {
        return a.id < b.id;
    });

    vector<int> tat(n), wt(n);
    double avgWT = 0, avgTAT = 0;

    for (int i = 0; i < n; i++) {
        tat[i] = all[i].ct - all[i].at;
        wt[i] = tat[i] - all[i].bt;
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << all[i].at << "\t"
             << all[i].bt << "\t" << all[i].ct << "\t"
             << tat[i] << "\t" << wt[i] << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << (avgWT / n);
    cout << "\nAverage Turnaround Time: " << (avgTAT / n) << endl;

    cout << "\nExecution Order: ";
    for (int x : order) cout << "P" << x << " ";
    cout << endl;

    return 0;
}

int main(){

    cout << "Enter number of processes: ";
    int n;
    cin >> n;

    vector<Process> all(n);
    cout << "Enter arrival time and burst time for the following process:\n";

    for(int i=0;i<n; i++){
        cout<<"P"<<i+1<<": ";
        cin>>all[i].at>>all[i].bt;
        all[i].rt=all[i].bt;
        all[i].id=i;
        all[i].ct=0;
    }

    //sort wrt arrival time

    sort(all.begin(), all.end(), [](const Process &a, const Process &b){
        return a.at<b.at;
    });

    vector <int> order;

    queue<int> q;
    int time=0, tq, completed=0, idx=0;
    cout<<"Enter time quantum: ";
    cin>>tq;

    while(completed!=n){
        while(idx<n && all[idx].at<=time){
            q.push(idx);
            idx++;
        }

        if(q.empty()){
            if(idx<n)
                time=all[idx].at;
            continue;
        }

        int pid= q.front();
        q.pop();
        Process &p= all[pid];

        if(p.rt>tq){
            p.rt-=tq;
            time+=tq;
            
            while(idx<n && all[idx].at<=time){
            q.push(idx);
            idx++;
            }
            q.push(pid);
        }
        else{
            time+=p.rt;
            p.ct=time;
            p.rt=0;
            completed++;
            order.push_back(p.id+1);
        }


    }

    //sort according to id

    sort(all.begin(), all.end(), [](const Process &a, const Process &b){
        return a.id<b.id;
    });
    int totalTat=0, totalWt=0;
    for(int i=0;i<n; i++){
        all[i].tat= all[i].ct- all[i].at;
        all[i].wt= all[i].tat- all[i].bt;
        totalTat+=all[i].tat;
        totalWt+=all[i].wt;
    }

      cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << all[i].at << "\t"
             << all[i].bt << "\t" << all[i].ct << "\t"
             << all[i].tat << "\t" << all[i].wt << "\n";
    }

    cout<<"Average Tunr around time "<<(double)totalTat/n<<endl;
    cout<<"Average waiting time "<< (double)totalWt/n;



    return 0;
}
