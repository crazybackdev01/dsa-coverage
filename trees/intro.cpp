#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

// struct TreeNode {
//     int data;
//     TreeNode* left;
//     TreeNode* right;

//     TreeNode(int data){
//         this->data = data;
//         this->left = nullptr;
//         this->right = nullptr;
//     }
// };
class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

class linkedListNode{
    public:
        int data;
        linkedListNode* next;
    
    linkedListNode(int data){
        this->data = data;
        this->next = NULL;
    }
};

Node *buildTree(Node *root)
{

    // No need of this condition as we will start from NULL
    // if(root==NULL){
    //     cout<<"Enter valid root object which is not NULL"<<endl;
    //     return NULL;
    // }

    cout << "Enter the data: " << endl;
    int data;
    cin >> data;

    if (data == -1)
    {
        return NULL;
    }

    root = new Node(data);
    cout << "Enter data for inserting in left of " << root->data << endl;
    root->left = buildTree(root->left);
    cout << "Enter data for inserting in right of " << root->data << endl;
    root->right = buildTree(root->right);
    return root;
}

void levelOrder(Node *root)
{
    queue<Node *> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();

        // Traversed current level properly so encountered NULL so enter because of next line
        if (temp == NULL)
        {
            cout << endl;
            // Traversed the current level properly but queue still has some elements
            if (!q.empty())
            {
                q.push(NULL);
            }
        }
        else
        {
            cout << temp->data << " ";
            if (temp->left)
            {
                q.push(temp->left);
            }
            if (temp->right)
            {
                q.push(temp->right);
            }
        }
    }
}

void inorder(Node *root) {}
void preorder(Node *root) {}
void postorder(Node *root) {}

// root - left - right
// stack order = root -> left -> right 
vector<int> iterativePreorder(Node *root) {
    vector<int> ans;
    if(!root){
        return ans;
    }
    stack<Node*> st;
    st.push(root);

    while(!st.empty()){
        Node* temp = st.top();
        st.pop();

        ans.push_back(temp->data);

        if(temp->right){
            st.push(temp->right);
        }
        if(temp->left){
            st.push(temp->left);
        }
    }

    return ans;
}

// left - right - root
// stack order = left -> right -> root
// Root must come last, so reverse preorder.
// Normal preorder: Root Left Right
// Modified preorder: Root Right Left
//Reverse it : Left Right Root
vector<int> iterativePostorder(Node *root) {
    vector<int> ans;
    if(!root) return ans;

    stack<Node*> st;


}
vector<int> iterativeInorder(Node *root) {
    vector<int> ans;
    if(!root) return ans;
    stack<Node*> st;
    Node* curr = root;
    // st.push(root);
    while(curr && !st.empty()){
        while(curr){
            st.push(curr);
            curr = curr->left;
        }

        curr = st.top();
        st.pop();

        ans.push_back(curr->data);
        curr = curr->right;
    }
    return ans;
}

// used & here and not in buildTree method because in this function, we are going to change root to new reference in the function itself and not going to return new reference like in buildTree method
void buildFromLevelOrder(Node *&root)
{
    queue<Node *> q;
    cout << "Enter data for root " << endl;
    int data;
    cin >> data;
    root = new Node(data);
    q.push(root);

    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();

        cout << "Enter data for left of " << temp->data << endl;
        int leftData;
        cin >> leftData;
        if (leftData != -1)
        {
            Node *leftNode = new Node(leftData);
            temp->left = leftNode;
            q.push(leftNode);
        }

        cout << "Enter data for right of " << temp->data << endl;
        int rightData;
        cin >> rightData;

        if (rightData != -1)
        {
            Node *rightNode = new Node(rightData);
            temp->right = rightNode;
            q.push(rightNode);
        }
    }
}

int main()
{

    Node *root = NULL;
    // root = buildTree(root);
    buildFromLevelOrder(root);
    levelOrder(root);

    return 0;
}