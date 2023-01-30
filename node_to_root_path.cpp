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
vector<int> Node_2_root_path(Node*root,int ele){
    if(root->data==ele){
        vector<int> res;
        res.push_back(root->data);
        return res;
    }
    for(Node*child:root->children){
        vector<int>res = Node_2_root_path(child,ele);
        if(res.size()>0){
            return res;
        }
    }
    vector<int>res;
    return res;
}
int main()
{    
    vector<int>path = {10,20,50,-1,60,-1,-1,30,70,-1,80,110,-1,120,-1,-1,90,-1,-1,40,100,-1,-1,-1};
    struct Node*root = constructor(path);    
    int ele = 110;
    vector<int> res = Node_2_root_path(root,ele);
    for(int i:res){
        cout<<i<<"\t";
    }
    return 0;
}