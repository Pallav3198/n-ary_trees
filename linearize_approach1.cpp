#include<iostream>
#include<vector>
#include<stack>
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

void Display(struct Node*root){
    string output = to_string(root->data)+"->";
    for(Node*child:root->children){
        output += to_string(child->data) + ",";
    }
    output+=".";
    cout<<output<<endl;
    for(Node*child:root->children){
        Display(child);
    }
}
Node*get_tail(Node*root){
    while(root->children.size()>0){
        root = root->children[0];
    }
    return root;
}
void  Linearize(Node*root){
    for(Node*child:root->children){
        Linearize(child);
    }
    while(root->children.size()>1){
        Node*last = root->children.back();
        root->children.pop_back();
        Node*slast = root->children.back();
        Node*tail = get_tail(slast);
        tail->children.push_back(last);
    }
}
int main()
{    
    vector<int>path = {10,20,50,-1,60,-1,-1,30,70,-1,80,110,-1,120,-1,-1,90,-1,-1,40,100,-1,-1,-1};
    struct Node*root = constructor(path);
    Display(root);            
    cout<<endl;
    Linearize(root);
    Display(root);  
    return 0;
}