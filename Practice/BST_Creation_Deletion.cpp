#include <iostream>
#include <vector>
using namespace std;

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

class BST {
    private:
        Node* root;
        
        void freeTree(Node* node) {
            if (node == nullptr) return;
            freeTree(node->left);
            freeTree(node->right);
            delete node;
        }
        void inorderHelper(Node* node) const {
            if (node == nullptr) return;

            inorderHelper(node->left);
            cout << node->data << " ";
            inorderHelper(node->right);
        }
    public:
        BST() {
            root = nullptr;
        }
        void clear() {
            freeTree(root);
            root = nullptr;
            cout << "Tree deleted" << endl;
        }
        void printInorder() {
            if (root == nullptr) {
                cout << "Empty tree" << endl; 
                return;
            }
            inorderHelper(root);
            cout << " (Root = " << root->data << ")" << endl;
        }
        
        // =================== Tree Creation ===================
        void insertNode(int key) {
            if (root == nullptr) {
                root = new Node(key);
                return;
            }

            Node* parent = nullptr;
            Node* cur = root;
            while (cur != nullptr && cur->data != key) {
                parent = cur;
                if (key < cur->data) cur = cur->left;
                else cur = cur->right;
            }

            if (cur == nullptr) {
                if (key < parent->data) parent->left = new Node(key);
                else parent->right = new Node(key);
            } else {
                cout << "Duplicate node, key = " << key << endl;
            }
        }
        void loadArray(vector<int> A) {
            for (int i : A) {
                insertNode(i);
            }
        }

        // =================== Tree Creation ===================
        void deleteNode(int key) {
            if (root == nullptr) {
                cout << "Tree is empty" << endl;
                return;
            }

            Node* cur = root;
            Node* prev = nullptr;

            // Step 1: Search for the target node
            while (cur != nullptr && cur->data != key) {
                prev = cur;
                if (key < cur->data) cur = cur->left;
                else cur = cur->right;
            }

            // Key not found in the tree (Case 5)
            if (cur == nullptr) {
                cout << key << " is not in the tree: nothing to delete" << endl;
                return;
            }

            // Leaf or single child node (Case 2-3)
            if (cur->left == nullptr || cur->right == nullptr) {
                Node* newChild = (cur->left != nullptr) ? cur->left : cur->right;

                // If the node to delete is the root node
                if (prev == nullptr) {
                    delete cur;
                    root = newChild;
                    return;
                }

                if (cur == prev->left) prev->left = newChild;
                else prev->right = newChild;
                delete cur;
            }

            // Two children (Case 1 - 4)
            else {
                Node* succParent = cur;
                Node* succ = cur->right;
                while (succ->left != nullptr) {
                    succParent = succ;
                    succ = succ->left;
                }

                cur->data = succ->data;

                if (succParent->left == succ) {
                    succParent->left = succ->right;
                } else {
                    succParent->right = succ->right;
                }
                
                delete succ;
            }
        }
};

int main () {
    vector<int> Ex1 = {40, 20, 60, 10, 30, 50, 70};
    vector<int> Ex2 = {45, 25, 65, 15, 35, 55, 75, 30, 60};
    vector<int> Ex3 = {10, 20, 30};

    vector<int> Del1 = {40, 60, 10, 25};
    vector<int> Del2 = {45, 25, 65};
    vector<int> Del3 = {10, 20, 30};

    BST BSTbuilder;
    // Example 1
    cout << "Example 1" << endl;
    BSTbuilder.loadArray(Ex1);
    BSTbuilder.printInorder();
    for (int k : Del1) {
        BSTbuilder.deleteNode(k);
        BSTbuilder.printInorder();
    }
    BSTbuilder.clear();
    cout << endl;

    // Example 2
    cout << "Example 2" << endl;
    BSTbuilder.loadArray(Ex2);
    BSTbuilder.printInorder();
    for (int k : Del2) {
        BSTbuilder.deleteNode(k);
        BSTbuilder.printInorder();
    }
    BSTbuilder.clear();
    cout << endl;

    // Example 3
    cout << "Example 3" << endl;
    BSTbuilder.loadArray(Ex3);
    BSTbuilder.printInorder();
    for (int k : Del3) {
        BSTbuilder.deleteNode(k);
        BSTbuilder.printInorder();
    }
    BSTbuilder.clear();
}