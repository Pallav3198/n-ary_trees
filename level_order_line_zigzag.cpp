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
void Level_Order_ZigZag(Node*root){
    stack<Node*>ms,cs;
    int path = 1;
    ms.push(root);
    while(!ms.empty()){
        Node*ele = ms.top();
        ms.pop();
        cout<<ele->data<<"\t";
        if(path%2==1){
            for(Node*child:ele->children){
                cs.push(child);
            }
        }
        else{
            for(int i=ele->children.size()-1;i>=0;i--){
                cs.push(ele->children[i]);
            }
        }
        if(ms.empty()){
            swap(ms,cs);
            cout<<endl;
            path++;
        }
    }
    cout<<endl;
}

int main()
{    
    vector<int>path = {10,20,50,-1,60,-1,-1,30,70,-1,80,110,-1,120,-1,-1,90,-1,-1,40,100,-1,-1,-1};
    struct Node*root = constructor(path);
    Level_Order_ZigZag(root);
    //Display(root);              
    return 0;
}