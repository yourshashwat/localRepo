// OPtimal pages replacement

#include <bits/stdc++.h>
using namespace std;

bool found(vector<int> frames, int p){
    for(int it:frames){
        if(it==p) return true;
    }
    return false;
}

int predictIndex(vector<int> &pages, vector<int> &frames, int index){
    int res=-1, farthest=index;
    for(int i=0; i<frames.size(); i++){
        int j;
        for(j=index; j<pages.size(); j++){
            if(frames[i]==pages[j]){
                if(j>farthest){
                    farthest=j;
                    res=i;
                }
                break;
            }
        }
        if(j==pages.size()) return i;
    }
    return (res==-1) ? 0 : res;
}

 void optimalpageReplacement(vector<int> &pages, int fn){
    int phit=0, pmiss=0;
    vector<int> frames;
    for(int i=0; i<pages.size(); i++){
        if(found(frames,pages[i])){
            phit++;
        }
        else{
            pmiss++;
            if(frames.size()<fn){
                frames.push_back(pages[i]);
            }
            else{
                int j= predictIndex(pages, frames, i+1);
                frames[j]= pages[i];
            }
        }
    }
    cout<<"Pages hits= "<<phit<<"\nPages miss: "<<pmiss<<endl;
 }


int main(){

    vector<int> pages={7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2 };
    int fn=4; //frame number
    optimalpageReplacement(pages,fn);




    return 0;
}