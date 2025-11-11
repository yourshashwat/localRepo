//shortest seek time first SSTF

#include <bits/stdc++.h>
using namespace std;


int main(){

    vector<int> q={98,183,37,122,14,124,65,67};
    int movement=0,curr=53;
    unordered_map<int, bool> mp;

    for(int i:q){
        mp[i]=false;
    }

    int completed=0;
    cout<<curr;
    while(completed<q.size()){
        int shortest=INT_MAX, shortestIndex=-1;
        
        for(int i=0; i<q.size(); i++){
            if(mp[q[i]]==false){
            int diff=abs(q[i]-curr);
            if(diff<shortest){
                shortest=diff;
                shortestIndex=i;
            }
            }
        }

        cout<<"--> " <<q[shortestIndex];
        completed++;
        mp[q[shortestIndex]]=true;
        
        movement+= abs(curr-q[shortestIndex]);
        curr=q[shortestIndex];

    }


    cout<<"\nHead movements= "<<movement<<endl;

    return 0;
}
