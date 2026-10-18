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

// ==================== Class Work 2: Problems ====================
#pragma region Cases
// ========================== Problem 1 ===========================
void case_1(Node* node) {
    // Case 1: delete the root (40). It has two children.
    // 1. find the inorder successor: the smallest value in the right subtree
    Node* parent = node;
    Node* succ = node->right;
    while (succ->left != nullptr) {
        parent = succ;
        succ = succ->left;
    }

    // 2. copy the successor's value into the root
    node->data = succ->data;

    // 3. remove the successor node (it has no left child)
    if (parent == node)
        parent->right = succ->right;
    else
        parent->left = succ->right;
    delete succ;
}

void case_1_3(Node* node) {
    // Case 1: delete the root (40). It has two children.
    // 1. find the inorder predecessor: the largest value in the left subtree
    Node* parent = node;
    Node* pred = node->left;
    while (pred->right != nullptr) {
        parent = pred;
        pred = pred->right;
    }

    // 2. copy the successor's value into the root
    node->data = pred->data;

    // 3. remove the successor node (it has no left child)
    if (parent == node)
        parent->left = pred->left;
    else
        parent->right = pred->left;
    delete pred;
}

void case_2(Node* node, int leaf) {
    // Case 2: delete a leaf (10). It has no children.
    // 1. search for 10, remembering its parent
    Node* parent = nullptr;
    Node* cur = node;
    int key = leaf;
    while (cur != nullptr && cur->data != key) {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else cur = cur->right;
    }
    
    // 2. unlink it from its parent (20) and free it
    if (parent->left == cur) parent->left = nullptr;
    else parent->right = nullptr;
    delete cur;
}

void case_3(Node* node, int target) {
    return;
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
    default:
        break;
    }

    TreeBuilder builder;
    Node* root = builder.createTree(inorder, preorder);

    printInorder(root); cout << endl;
    
    return root;
}

void caseSelection(Node* root, int i, int target) {
    switch (i)
    {
    case 1:
        printInorder(root); cout << endl;
        case_1(root);
        printInorder(root); cout << endl;
        break;
    case 2:
        printInorder(root); cout << endl;
        case_2(root, target);
        printInorder(root); cout << endl;
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
    cout << "Tree selection (T: 1, P:2): ";
    cin >> tree;
    cout << "Case selection (1 - 5): ";
    cin >> cnum;

    int target = 10;
    Node* root = treeSelection(tree);
    caseSelection(root, cnum, target);

    return 0;
}