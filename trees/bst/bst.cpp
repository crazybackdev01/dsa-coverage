#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

// Height definition :
// 1. If it is no. of nodes in the longest path from root to leaf then for root == NULL; height = 0;
// 2. If it is no. of nodes in the longest path from root to leaf then for root == NULL; height = -1;
// for both cases we have to return
// 1 + max(rightSubTreeHeight, leftSubTreeHeight)

class BST
{
private:
    struct Node
    {
        int data;
        Node *left;
        Node *right;
        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node *root;
    int nodeCount;

    Node *insertHelper(Node *node, int value)
    {
        if (node == nullptr)
        {
            return new Node(value);
        }
        if (node->data > value)
        {
            node->left = insertHelper(node->left, value);
        }
        else if (node->data < value)
        {
            node->right = insertHelper(node->right, value);
        }
        // Duplicate — ignore (or handle as you prefer)
        return node;
    }

    Node *searchHelper(Node *node, int key)
    {
        if (node == nullptr || node->data == key)
        {
            return node;
        }

        if (key > node->data)
        {
            return searchHelper(node->right, key);
        }
        else
        {
            return searchHelper(node->left, key);
        }
    }

    Node *findMin(Node *node)
    {
        // Node *node = this->root;

        // checking both node and node->left not NULL ensures single node case in tree that we do not return NULL in single node tree case for minimum;
        while (node && node->left)
        {
            node = node->left;
        }
        return node;
    }

    Node *findMax(Node *node)
    {
        Node *curr = node;
        while (node->right)
        {
            node = node->right;
        }
        return node;
    }

    Node *deleteHelper(Node *node, int key)
    {
        if (node == nullptr)
            return nullptr;
        if (key > node->data)
        {
            node->right = deleteHelper(node->right, key);
        }
        else if (key < node->data)
        {
            node->left = deleteHelper(node->left, key);
        }
        else
        {
            // equality case : node->data = key
            // case 1: node has 0 children - leaf node (Do nothing just remove it and set the current pointer NULL)
            // case 2: node has 1 children - replace current node with its only children
            // case 3: node has 2 children - replace the current node with its inorder predecessor or inorder successor
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr || node->right == nullptr)
            {
                if (node->left == nullptr)
                {
                    Node *temp = node->right;
                    delete node;
                    return temp;
                }
                else if (node->right == nullptr)
                {
                    Node *temp = node->left;
                    delete node;
                    return temp;
                }
            }
            else
            {
                // case 3 node has 2 children
                // store the inorder successor as temp
                // delete node
                // return the inorder successor
                Node *inorderSuccessor = findMin(node->right);
                // inorder predecessor is maximum in left subtree
                node->data = inorderSuccessor->data;
                // Delete the inorder successor in the root's right subtree after assigning its data value to root->data; here node stands for root as we will pass root to the function deleteHelper()
                node->right = deleteHelper(node->right, inorderSuccessor->data);
            }
        }
        // return the root after deleting the key
        return node;
    }

    void inorderHelper(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }

    void preorderHelper(Node *node)
    {
        if (node == nullptr)
            return;
        cout << node->data << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }

    void postorderHelper(Node *node)
    {
        if (node == nullptr)
            return;
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->data << " ";
    }

    int heightHelper(Node *node)
    {
        // following no. of edges definition
        if (node == nullptr)
            return -1;
        return 1 + max(heightHelper(node->left), heightHelper(node->right));
    }

    void destroyTree(Node *node)
    {
        if (node == nullptr)
            return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    // Constructor
    BST() : root(nullptr), nodeCount(0) {};

    // Destructor
    ~BST()
    {
        destroyTree(root);
    };

    // Public operations

    // insert(int value)
    void insert(int value)
    {
        root = this->insertHelper(root, value);
        this->nodeCount++;
    }
    // search(int value)
    Node *search(int key)
    {
        Node *findNode = this->searchHelper(this->root, key);
        if (findNode)
        {
            return findNode;
        }
        else
        {
            return nullptr;
        }
    }

    bool ifTreeHasKey(int key)
    {
        // if (searchHelper(root, key))
        // {
        //     return true;
        // }
        // else
        // {
        //     return false;
        // }
        return this->searchHelper(root, key) != nullptr;
    }
    // remove(int value)
    void remove(int key)
    {
        if (ifTreeHasKey(key))
        {
            root = deleteHelper(root, key);
            this->nodeCount--;
        }
    }
    // inorder()
    void inorderTraversal()
    {
        inorderHelper(root);
        cout << endl;
    }
    // preorder()
    void preorderTraversal()
    {
        preorderHelper(root);
        cout << endl;
    }
    // postorder()
    void postorderTraversal()
    {
        postorderHelper(root);
        cout << endl;
    }
    // levelOrder()
    void levelOrderTraversal()
    {
        // mistake : did not checked root == nullptr condition
        if (root == nullptr)
            return;
        queue<Node *> q;
        q.push(this->root);
        q.push(NULL);
        while (!q.empty())
        {
            Node *curr = q.front();
            q.pop();
            if (curr == NULL)
            {
                cout << endl;
                /*
                if we will push NULL without checking queue empty or not then It will keep popping and pushing NULL forever.
                q.push(NULL);
                */
                if (!q.empty())
                {
                    q.push(NULL);
                }
                continue;
            }
            else
            {
                cout << curr->data << " ";
                if (curr->left)
                    q.push(curr->left);

                if (curr->right)
                    q.push(curr->right);
            }
        }
    }
    // inorderIterative()
    // void inorderIterative(Node *root)
    // {
    //     if (root == nullptr)
    //         return;
    //     stack<Node *> s;
    //     Node *current = root;
    //     s.push(current);
    //     while (current != nullptr || !s.empty())
    //     {
    //         while (current)
    //         {
    //             s.push(current);
    //             current = current->left;
    //         }
    //         current = s.top();
    //         s.pop();
    //         cout << current->data << " ";
    //     }
    // }
    void inorderIterative(Node *root)
    {
        stack<Node *> st;
        Node *curr = this->root;
        // apan yahaa || isliye laga rahe hai && ki jagah kuki curr = NULL ho sakta hai jab previous curr->right ki value NULL hojaayegiii aur agar tab stack empty nahi huaa toh root stack me hogaa jisko pop karke print karengee and then right subtree me jaayengee
        while (curr || !st.empty())
        { // yeh galat hai kuki agar current ka yaani root ka left exist nahi kiya toh wo kud bhi push nahi hogaa stack me.
            // while (current->left)
            // {
            //     s.push(current);
            //     current = current->left
            // };

            /*
            while(current->left){
                current=current->left;
                s.push(current);
            }
            */
            while (curr)
            {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top();
            st.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
        cout << endl;
    }
    // height()
    int height()
    {
        return heightHelper(root);
    }
    // size()
    int size() const
    {
        return this->nodeCount;
    }
    // isEmpty()
    bool isEmpty() const
    {
        return this->root == nullptr;
    }
    // findMin()
    int findMinimumInTree()
    {
        if (this->root == nullptr)
        {
            throw runtime_error("Tree is empty");
        }
        return this->findMin(root)->data;
    }
    // findMax()
    int findMaximumInTree()
    {
        if (this->root == nullptr)
        {
            throw runtime_error("Tree is empty");
        }
        return this->findMax(root)->data;
    }
};

int main()
{
    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Inorder:    ";
    tree.inorderTraversal(); // 20 30 40 50 60 70 80
    cout << "Preorder:   ";
    tree.preorderTraversal(); // 50 30 20 40 70 60 80
    cout << "Postorder:  ";
    tree.postorderTraversal(); // 20 40 30 60 80 70 50
    cout << "Level Order Traversal : " << endl;
    tree.levelOrderTraversal(); // 50 30 70 20 40 60 80

    cout << "Height: " << tree.height() << endl; // 2
    cout << "Size: " << tree.size() << endl;     // 7

    cout << "Search 40: " << (tree.search(40) ? "Found" : "Not Found") << endl;
    cout << "Search 90: " << (tree.search(90) ? "Found" : "Not Found") << endl;

    tree.remove(30);
    cout << "After removing 30: " << endl;
    tree.levelOrderTraversal(); // 20 40 50 60 70 80

    return 0;
}

/*
Operation	Average	Worst (Skewed)
Search	O(log n)	O(n)
Insert	O(log n)	O(n)
Delete	O(log n)	O(n)
Traversal	O(n)	O(n)
Height	O(n)	O(n)
Space	O(n)	O(n)
*/