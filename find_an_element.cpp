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
bool Find_element(Node*root,int ele){
    if(root->data==ele){
        return true;
    }
    for(Node*child:root->children){
        bool res = Find_element(child,ele);
        if(res==true)
            return res;
    }
    return false;
}
int main()
{    
    vector<int>path = {10,20,50,-1,60,-1,-1,30,70,-1,80,110,-1,120,-1,-1,90,-1,-1,40,100,-1,-1,-1};
    struct Node*root = constructor(path);
    //Display(root);       
    int ele = 110;
    
    return 0;
}