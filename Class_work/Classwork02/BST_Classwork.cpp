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
    if (parent == node) parent->right = succ->right;
    else parent->left = succ->right;
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
    if (parent == node) parent->left = pred->left;
    else parent->right = pred->left;
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
};

void case_3(Node* node, int target) {
    // Case 3: delete a node with ONE child.
    // 1. search for the target, remembering its parent
    Node* parent = nullptr;
    Node* cur = node;
    int key = target;
    while (cur != nullptr && cur->data != key) {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else cur = cur->right;
    }
    // 2. its only child takes its place
    Node* child = (cur->left != nullptr) ? cur->left : cur->right;
    if (parent->left == cur) parent->left = child;
    else parent->right = child;
    delete cur;
}

void case_4(Node* node, int target) {
    // Case 4: delete a node with TWO children (20).
    // 1. search for target
    Node* cur = node;
    int key = target;
    while (cur != nullptr && cur->data != key) {
        if (key < cur->data) cur = cur->left;
        else cur = cur->right;
    }
    
    // 2. find the inorder successor: right once, then left as far as possible
    Node* parent = cur;
    Node* succ = cur->right; // 30
    while (succ->left != nullptr) {
        parent = succ;
        succ = succ->left;
    }
    
    // 3. copy the successor's value into the node
    cur->data = succ->data;

    // 4. remove the successor node (it has no left child)
    if (parent == cur)
        parent->right = succ->right;
    else
        parent->left = succ->right;
    delete succ;
}

void case_4_4(Node* node, int target) {
    // Case 4: delete a node with TWO children (20).
    // 1. search for target
    Node* cur = node;
    int key = target;
    while (cur != nullptr && cur->data != key) {
        if (key < cur->data) cur = cur->left;
        else cur = cur->right;
    }
    
    // 2. find the inorder predecessor: left once, then right as far as possible
    Node* parent = cur;
    Node* succ = cur->left;
    while (succ->right != nullptr) {
        parent = succ;
        succ = succ->right;
    }
    
    // 3. copy the successor's value into the node
    cur->data = succ->data;

    // 4. remove the successor node (it has no left child)
    if (parent == cur)
        parent->left = succ->left;
    else
        parent->right = succ->left;
    delete succ;
}

void case_5(Node* node, int target) {
    // Case 5: the key is not in the tree.
    Node* cur = node;
    int key = target;
    while (cur != nullptr && cur->data != key) {
        if (key < cur->data) cur = cur->left;
        else cur = cur->right;
    }
    if (cur == nullptr)
        cout << key << " is not in the tree: nothing to delete" << endl;
}

void case_5_3(Node* node, int target) {
    // Case 5: the key is not in the tree.
    if (!node) {
        cout << "Tree is empty" << endl;
        return;
    }
    Node* parent = nullptr;
    Node* cur = node;
    int key = target;
    while (cur != nullptr && cur->data != key) {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else cur = cur->right;
    }
    if (cur == nullptr)
        if (parent->data > target) {
            parent->left = new Node(target);
        } else {
            parent->right = new Node(target);
        }
}

void deleteNode(Node* node, int target) {
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
        if (prev->data > target) {
            prev->left = new Node(target);
        } else {
            prev->right = new Node(target);
        }
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

void caseSelection(Node* root, int i, int target) {
    switch (i)
    {
    case 1:
        cout << "Before: "; printInorder(root); cout << endl;
        case_1(root);
        cout << "After:  "; printInorder(root); cout << endl;
        break;
    case 2:
        cout << "Before: "; printInorder(root); cout << endl;
        case_2(root, target);
        cout << "After:  "; printInorder(root); cout << endl;
        break;
    case 3:
        cout << "Before: "; printInorder(root); cout << endl;
        case_3(root, target);
        cout << "After:  "; printInorder(root); cout << endl;
        break;
    case 4:
        cout << "Before: "; printInorder(root); cout << endl;
        case_4(root, target);
        cout << "After:  "; printInorder(root); cout << endl;
        break;
    case 5:
        cout << "Before: "; printInorder(root); cout << endl;
        case_5(root, target);
        cout << "After:  "; printInorder(root); cout << endl;
        break;
    case 6: // Bonus question
        cout << "Before: "; printInorder(root); cout << endl;
        deleteNode(root, target);
        cout << "After:  "; printInorder(root); cout << endl;
        break;
    case 7: // Case 1 question 3
        cout << "Before: "; printInorder(root); cout << endl;
        case_1_3(root);
        cout << "After:  "; printInorder(root); cout << endl;
        break;
    case 8: // Case 4 question 4
        cout << "Before: "; printInorder(root); cout << endl;
        case_4_4(root, target);
        cout << "After:  "; printInorder(root); cout << endl;
        break;
    case 9: // Case 5 questions 3-4
        cout << "Before: "; printInorder(root); cout << endl;
        case_5_3(root, target);
        cout << "After:  "; printInorder(root); cout << endl;
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
    cout << "Tree selection (T: 1, P: 2): ";
    cin >> tree;
    Node* root = treeSelection(tree);
    
    cout << "Case selection (Cases: 1 - 5, General deletion: 6): ";
    cin >> cnum;
    cout << "Select a target: ";
    cin >> target;

    caseSelection(root, cnum, target);

    return 0;
}
