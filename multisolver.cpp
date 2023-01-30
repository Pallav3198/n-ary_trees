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
// - - - MULTISOLVER - - - // 
int tree_size = 0, max_node = INT_MIN, min_node = INT_MAX,height = 0;
void Multisolver(Node*root,int depth){
    tree_size+=1;
    max_node = max(max_node,root->data);
    min_node = min(min_node,root->data);
    height = max(height,depth);
    for(Node*child:root->children){
        Multisolver(child,depth+1);
    }
}
int state = 0;
Node*predessor=NULL;
Node*sucessor=NULL;
void Predecessor_and_Successor(Node*root,int data){
    if(state==0){
        if(root->data==data){
            state = 1;
        }
        else{
            predessor = root;
        }
    }
    else if(state==1){
        sucessor = root;
        state = 2;
    }
    for(Node*child:root->children){
        Predecessor_and_Successor(child,data);
    }
}
int main()
{  
    vector<int>path = {10,20,50,-1,60,-1,-1,30,70,-1,80,110,-1,120,-1,-1,90,-1,-1,40,100,-1,-1,-1};
    struct Node*root = constructor(path);
    Predecessor_and_Successor(root,100);
    if(predessor==NULL){
         cout<<"Predecessor is NULL"<<endl;
         cout<<"Successor"<<sucessor->data<<endl;
    }
    else if(sucessor==NULL){
        cout<<"Predecessor"<<predessor->data<<endl;
        cout<<"Successor is NULL"<<endl;
    }
    else{
        cout<<"Predecessor"<<predessor->data<<endl;
        cout<<"Successor"<<sucessor->data<<endl;
    }
    return 0;
}