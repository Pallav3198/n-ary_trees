#include<iostream>
#include<stack>
#include<vector>
#include<string>
#include<limits>
#include<math.h>
#include<queue>
using namespace std;
struct Node{
    int data;
    vector<Node*>children;
};
Node*create_node(int data){
    Node*newnode = new Node;
    newnode->data = data;
    return newnode;
}
Node*constructor(vector<int>&path){
    stack<Node*>st;
    Node*root = new Node;
    for(int ele:path){
        if(ele==-1){
            st.pop();
        }
        else{
            Node*node = create_node(ele);
            if(st.empty()){
                root = node;
            }
            else{
                st.top()->children.push_back(node);
            }
            st.push(node);
        }
    }
    return root;
}
void Display(Node*root){
    string str = to_string(root->data) + "->";
    for(Node*child:root->children){
        str+= to_string(child->data) + ",";
    }
    str+='.';
    cout<<str<<endl;
    for(Node*child:root->children){
        Display(child);
    }
}
int Size(Node*root){
    int s=0;
    for(Node*child:root->children){
        int cs = Size(child);
        s+=cs;
    }
    s+=1;
    return s;
}
int Max(Node*root){
    int max_tree = INT_MIN;
    for(Node*child:root->children){
        int cm = Max(child);
        max_tree = max(cm,max_tree);
    }
    max_tree = max(max_tree,root->data);
    return max_tree;
}
int Height(Node*root){
    int h=-1;
    for(Node*child:root->children){
        int ch = Height(child);
        h = max(h,ch);
    }
    h+=1;
    return h;
}
void Traversals(Node*root){
    cout<<"Node Pre "<<root->data<<endl;
    for(Node*child:root->children){
        cout<<"Edge Pre "<<root->data<<" "<<child->data<<endl;
        Traversals(child);
         cout<<"Edge Post "<<root->data<<" "<<child->data<<endl;
    }
    cout<<"Node Post "<<root->data<<endl;
}
void Level_Order_Single_Queue(Node*root){
    queue<Node*>q;
    q.push(root);
    while(!q.empty()){
        Node*ele = q.front();
        q.pop();
        cout<<ele->data<<"\t";
        for(Node*child:ele->children){
            q.push(child);
        }
    }
    cout<<endl;
}
void Level_Order_Linewise(Node*root){
    queue<Node*>mq,cq;
    mq.push(root);
    while(!mq.empty()){
        Node*ele = mq.front();
        mq.pop();
        cout<<ele->data<<"\t";
        for(Node*child:ele->children){
            cq.push(child);
        }
        if(mq.empty()){
            cout<<endl;
            swap(mq,cq);
        }
    }
}
void Level_Order_ZigZag(Node*root){
    stack<Node*>ms,cs;
    int flag = 1;
    ms.push(root);
    while(!ms.empty()){
        Node*ele = ms.top();
        ms.pop();
        cout<<ele->data<<"\t";
        if(flag%2==1){
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
            cout<<endl;
            swap(ms,cs);
            flag++;
        }
    }
}
void Level_order_marker(Node*root){
    queue<Node*>q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node*ele = q.front();
        q.pop();
        if(ele!=NULL){
            cout<<ele->data<<"\t";
            for(Node*child:ele->children){
                q.push(child);
            }
        }
        else{
            cout<<endl;
            if(!q.empty()){
                q.push(NULL);
            }
        }
    }
}
void Level_order_constant_space(Node*root){
    queue<Node*>q;
    q.push(root);
    while(!q.empty()){
        int size = q.size();
        for(int i=0;i<size;i++){
            Node*ele = q.front();
            q.pop();
            cout<<ele->data<<"\t";
            for(Node*child:ele->children){
                q.push(child);
            }
        }
        cout<<endl;
    }
}
bool find_element(int ele,Node*root){
    if(root->data==ele){
        return true;
    }
    for(Node*child:root->children){
        bool cr = find_element(ele,child);
        if(cr==1){
            return true;
        }
    }
    return false;
}
vector<int>node_2_root_path(Node*root,int ele){
    if(root->data==ele){
        vector<int>base;
        base.push_back(root->data);
        return base;
    }
    for(Node*child:root->children){
        vector<int>res = node_2_root_path(child,ele);
        if(res.size()>0){
            res.push_back(root->data);
            return res;
        }
    }
    vector<int>a;
    return a;
}
int Lowest_common_ancestor(int a,int b,Node*root){
    //it is given that both a and b will definitely exist in the tree.
    vector<int>path1 = node_2_root_path(root,a);
    vector<int>path2 = node_2_root_path(root,b);
    int i=path1.size()-1,j=path2.size()-1;
    while(i>=0 && j>=0 && path1[i]==path2[j]){
        i--;
        j--;
    }
    i++;
    j++;
    return path1[i];
}
int distance_between_nodes(int a,int b, Node*root){
    vector<int>path1 = node_2_root_path(root,a);
    vector<int>path2 = node_2_root_path(root,b);
    int i=path1.size()-1,j=path2.size()-1;
    while(i>=0 && j>=0 && path1[i]==path2[j]){
        i--;
        j--;
    }
    i++;
    j++;
    return i+j;

}
bool similar_trees(Node*root1,Node*root2){
    if(root1->children.size()!=root2->children.size()){
        return false;
    }
    for(int i=0;i<root1->children.size();i++){
        bool res = similar_trees(root1->children[i],root2->children[i]);
        if(!res){
            return false;
        }
    }
    return true;
}
bool similar_trees_mirror(Node*root1,Node*root2){
    if(root1->children.size()!=root2->children.size()){
        return false;
    }
    for(int i=0;i<root1->children.size();i++){
        int j = root1->children.size()-1-i;
        bool res = similar_trees_mirror(root1->children[i],root2->children[j]);
        if(res==false){
            return false;
        }
    }
    return true;
}
bool Symmetric(Node*root){
    // a tree is symmetric if it is a mirror image of itself.
    return similar_trees_mirror(root,root);

}
int main()
{  
    vector<int>path = {10,20,-1,30,50,-1,60,-1,-1,40,-1,-1};
    vector<int>path2 = {10,20,-1,30,50,-1,60,-1,-1,-1};
    Node*root1 = constructor(path);
    Node*root2 = constructor(path2);
    // bool res = similar_trees_mirror(root1,root2);
    //cout<<res<<endl;
    bool res = Symmetric(root2);
    cout<<res;
    return 0;
}