#include<iostream>
#include<vector>
#include<stack>
#include<limits>
using namespace std;
struct Node{
    int data;
    vector<Node*>children;
};
Node*create_newnode(int data){
    Node*newnode = new Node;
    newnode->data = data;
    return newnode;
}
Node*constructor(vector<int>path){
    stack<Node*>st;
    Node*root;
    for(int ele:path){
        if(ele==-1){
            st.pop();
        }
        else{
            Node*newnode = create_newnode(ele);
            if(st.empty()){
                root = newnode;
                st.push(root);
            }
            else{
                st.top()->children.push_back(newnode);
                st.push(newnode);
            }
        }
    }
    return root;
}
void Display(Node*root){
    string str = to_string(root->data)+"->";
    for(Node*child:root->children){
        str+= to_string(child->data)+",";
    }
    str+=".";
    cout<<str<<endl;
    for(Node*child:root->children){
        Display(child);
    }
}
int floor = INT_MIN; // largest amongst smaller-> comparsion: large , therefore-> INT_MIN
int find_floor(Node*root,int data){
    if(root->data<data){
        if(root->data>floor){
            floor = root->data;
        }
    }
    for(auto child: root->children){
        find_floor(child,data);
    }
    return floor;
}
int kth_largest(Node*root,int k){
    floor = INT_MIN;
    int factor = INT_MAX;
    for(int i=0;i<k;i++){
        floor = find_floor(root,factor);
        factor = floor;
        floor = INT_MIN;
    }
    return factor;
}
int main()
{  
    vector<int>path = {10,20,50,-1,60,-1,-1,30,70,-1,80,110,-1,120,-1,-1,90,-1,-1,40,100,-1,-1,-1};
    struct Node*root = constructor(path);
    int ele = kth_largest(root,3);
    cout<<ele<<endl;
    return 0;
}