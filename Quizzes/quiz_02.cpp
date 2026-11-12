#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

#pragma region Class and Function Definitions
// ====================== Class Definitions =======================
class Node {
    public:
        int data;
        Node* left;
        Node* right;
        Node(int value)
        {
            data = value;
            left = nullptr;
            right = nullptr;
        }
};

class TreeBuilder { // Based on question 11 of Assignment 2
    private:
        unordered_map<int, int> inorderMap;
        int pindex = 0;

        Node* createTreeHelper(vector<int> preorder, int left, int right) {
            if (left > right) return nullptr;

            int rootVal = preorder[pindex++];
            Node* root = new Node(rootVal);

            int iindex = inorderMap[rootVal];
            root->left = createTreeHelper(preorder, left, iindex - 1);
            root->right = createTreeHelper(preorder, iindex + 1, right);

            return root;
        }
    public:
        // Create a tree based on it's inorder and preorder traversals
        Node* createTree(vector<int> inorder, vector<int> preorder) {
            int n = inorder.size();
            pindex = 0;
            inorderMap.clear();

            for (int i = 0; i < n; i++) {
                inorderMap[inorder[i]] = i;
            }

            return createTreeHelper(preorder, 0, n - 1);
        }
};

// ======================= Helper Functions =======================
// Inorder (Left, Node, Right) prints a BST in sorted order
void printInorder(Node* node) {
    if (node == nullptr) return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}

// Free every node (postorder: children before parent)
void freeTree(Node* node) {
    if (node == nullptr) return;
    
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}
#pragma endregion


#pragma region Cases

void deleteNode(Node* node, int target) {
    if (node == nullptr) {
        cout << "The tree is empty" << endl;
        return;
    }
    
    Node* curr = node;
    Node* prev = nullptr;

    // Step 1: Search for the target node
    while (curr != nullptr && curr->data != target) {
        prev = curr;
        if (target < curr->data) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    // Key not found in the tree (Case 5)
    if (curr == nullptr) {
        cout << target << " is not in the tree: nothing to delete" << endl;
        return;
    }

    // Leaf or single child node (Case 2-3)
    if (curr->left == nullptr || curr->right == nullptr) {
        // Find the non-null child (or nullptr if it's a leaf node)
        Node* newChild = (curr->left != nullptr) ? curr->left : curr->right;

        // If the node to delete is the root node
        if (prev == nullptr) {
            delete curr;
            node = newChild;
            return;
        }

        if (curr == prev->left) {
            prev->left = newChild;
        } else {
            prev->right = newChild;
        }
        delete curr;
    } 
    // Two children (Case 1 - 4)
    else {
        Node* succParent = curr;
        Node* succ = curr->right;
        while (succ->left != nullptr) {
            succParent = succ;
            succ = succ->left;
        }

        curr->data = succ->data;

        if (succParent->left == succ) {
            succParent->left = succ->right;
        } else {
            succParent->right = succ->right;
        }
        
        delete succ;
    }
}

#pragma endregion

// ======================== Main Execution ========================
Node* treeSelection(int i) {
    vector<int> inorder = {};
    vector<int> preorder = {};
    
    switch (i)
    {
    case 1:
        // Binary Search Tree T
        inorder = {10, 20, 30, 40, 50, 60, 70};
        preorder = {40, 20, 10, 30, 60, 50, 70};
        break;
    case 2:
        // Binary Search Tree P
        inorder = {15, 25, 30, 35, 45, 55, 60, 65, 75};
        preorder = {45, 25, 15, 35, 30, 65, 55, 60, 75};
        break;
    default:
        break;
    }

    TreeBuilder builder;
    Node* root = builder.createTree(inorder, preorder);

    cout << "Generated tree: "; printInorder(root); cout << endl;
    
    return root;
}

void caseSelection(Node* root, int i) {
    switch (i)
    {
    case 1:
        cout << "Before: "; printInorder(root); cout << endl;
        deleteNode(root, 40);
        cout << "After 40:  "; printInorder(root); cout << endl;
        deleteNode(root, 10);
        cout << "After 10:  "; printInorder(root); cout << endl;
        deleteNode(root, 60);
        cout << "After 60:  "; printInorder(root); cout << endl;
        deleteNode(root, 25);
        cout << "After 25:  "; printInorder(root); cout << endl;
        break;
    case 2:
        cout << "Before: "; printInorder(root); cout << endl;
        deleteNode(root, 45);
        cout << "After 45:  "; printInorder(root); cout << endl;
        deleteNode(root, 25);
        cout << "After 25:  "; printInorder(root); cout << endl;
        deleteNode(root, 65);
        cout << "After 65:  "; printInorder(root); cout << endl;
        break;
    default:
        break;
    }

    freeTree(root);
    return;
}

int main() {
    int tree;
    int cnum;
    int target;
    
    tree = 1;
    cnum = 1;
    Node* root = treeSelection(tree);
    
    caseSelection(root, cnum);
    
    tree = 2;
    cnum = 2;
    root = treeSelection(tree);
    
    caseSelection(root, cnum);

    return 0;
}
