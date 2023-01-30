#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
struct Node{
    int data;
    vector<Node*>children;
};
struct Node* create_newnode(int num){
    Node*newnode = new Node;
    newnode->data = num;
    return newnode;
}
struct Node* constructor(vector<int>&path){
    stack<Node*>st;
    Node* root = nullptr;
    for(int ele:path){
        if(ele==-1){
            st.pop();
        }
        else{
            Node*newnode = create_newnode(ele);
            if(st.size()==0){
                root = newnode;
                st.push(newnode);
            }
            else{
                st.top()->children.push_back(newnode);
                st.push(newnode);
            }
        }
    }
    return root;
}
void Level_order_delimiter(Node*root){
    queue<Node*>q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node*temp = q.front();
        q.pop();
        if(temp!=NULL){
            cout<<temp->data<<"\t";
            for(Node*child:temp->children){
                q.push(child);
            }
        }
        else{
            if(!q.empty()){
                cout<<endl;
                q.push(NULL);
            }
        }
    }
    cout<<endl;
}
void Level_order_loops(Node*root){
    queue<Node*>q;
    q.push(root);
    while(!q.empty()){
        int q_size = q.size();
        for(int i=0;i<q_size;i++){
            Node*temp = q.front();
            q.pop();
            cout<<temp->data<<"\t";
            for(Node*child:temp->children){
                q.push(child);
            }
        }
        cout<<endl;
    }
}
struct Pair{
    struct Node* ele;
    int level;
};
struct Pair* create_pair(struct Node*ele,int level){
    
}
void Level_order_pair(Node*root){

}
int main()
{    
    vector<int>path = {10,20,50,-1,60,-1,-1,30,70,-1,80,110,-1,120,-1,-1,90,-1,-1,40,100,-1,-1,-1};
    struct Node*root = constructor(path);      
    Level_order_loops(root);
    return 0;
}