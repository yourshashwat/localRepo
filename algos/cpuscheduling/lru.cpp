#include <bits/stdc++.h>
using namespace std;

struct Node{
    int page;
    Node *next, *prev;
    Node(int p): page(p), next(nullptr), prev(nullptr){}
    int pageFault=0, pageHit=0;
};

class LRU{
    int capacity;
    Node *head, *tail;
    unordered_map<int, Node*> mp;
    

    void moveToBeg(Node *node){
        if(node==head) return;

        if(node->prev) node->prev->next= node->next;
        if(node->next) node->next->prev= node->prev;
        if(node==tail) tail=node->prev;
 
        node->next=head;
        node->prev=nullptr;
        if(head) head->prev= node;
        head=node;
        if(!tail) tail=head;

    }

    void removeLRU(){
        if(!tail) return;
        
        Node *prev=tail->prev;
        mp.erase(tail->page);
        if(tail->prev) tail->prev->next=nullptr;
        delete(tail);
        tail=prev;
        if(!tail) head=nullptr;
    }

    public:

        LRU(int size): capacity(size), head(nullptr), tail(nullptr) {}

        void accessPage(int p){
            if(mp.count(p)){
                cout<<"Page hit \n";
                moveToBeg(mp[p]);
                
            }
            else{
                
                cout<<"Page fault \n";
                if(mp.size()==capacity){
                    removeLRU();
                }
                    Node *newNode= new Node(p);
                    mp[p]= newNode;
                    newNode->next=head;
                    if(head) head->prev=newNode;
                    head=newNode;
                    if(!tail) tail=head;
                
            }
        }

        void display(){
            Node *curr=head;
            while(curr){
                cout<<curr->page<<" ";
                curr=curr->next;
            }
            cout<<endl;
        }


};

int main(){
    LRU cache(3);
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4};

    for (int page : pages) {
        cache.accessPage(page);
        cache.display();
    }

    return 0;


}