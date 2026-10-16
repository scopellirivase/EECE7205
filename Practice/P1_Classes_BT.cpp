#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// ====================== Binary Tree ======================
struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : data(x), left(nullptr), right(nullptr) {}
};

// Solution classes - algorithms
class BuildTree {
// A class for building a binary tree given their inorder and preorder traversals
private:
    unordered_map<int, int> inorderMap;
    int preorderI = 0;

    TreeNode* buildTreeHelper(const vector<int>& preorder, int inStart, int inEnd) {
        // Base case: if the range is invalid, there are no elements for this subtree
        if (inStart > inEnd) {
            return nullptr;
        }
        int rootValue = preorder[preorderI++];
        TreeNode* root = new TreeNode(rootValue);

        // Find the index of this root in the inorder traversal
        int inorderRootI = inorderMap[rootValue];

        // Recursively build the left and right subtrees
        root->left = buildTreeHelper(preorder, inStart, inorderRootI - 1);
        root->right = buildTreeHelper(preorder, inorderRootI + 1, inEnd);

        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        inorderMap.clear();
        preorderI = 0;

        // Hash map mapping the value of the inorder element to its index
        for (int i = 0; i < inorder.size(); ++i) {
            inorderMap[inorder[i]] = i;
        }

        return buildTreeHelper(preorder, 0, inorder.size() - 1);
    }

    void deleteTree(TreeNode* node) {
        if (!node) return;
        
        return;
    }
};

void printInorder(TreeNode* node) {
    if (!node) return;
    printInorder(node->left);
    std::cout << node->data << " ";
    printInorder(node->right);
}

// ====================== Linked List ======================

struct ListNode {
    int data;
    ListNode *next;
    ListNode(int x) : data(x), next(nullptr) {}
};

class BuildList {
private:
    int i = 0;
    ListNode* linkedListHelper(const vector<int>& values, int i, int n) {
        if (i >= n) return nullptr;

        ListNode node = ListNode(values[i]);
    }
public:
    ListNode* buildLinkedList(const vector<int>& values) {
        i = 0;
        int n = values.size();

        ListNode head = ListNode(values[i]);
        i++;
        head.next = linkedListHelper(values, i, n);
        return;
    }
};

// Helper functions / test executions
void runAlgo(int n) {
    // Binary Tree Builder
    BuildTree solver;
    vector<int> preorder = {5, 12, 21, 3, 8, 17, 9};
    vector<int> inorder = {21, 12, 3, 5, 17, 8, 9};
    
    switch (n)
    {
    case 0:
        TreeNode* root = solver.buildTree(preorder, inorder);

        cout << "Inorder of constructed tree: ";
        printInorder(root);
        cout << endl;
        break;
    
    default:
        break;
    }
}

int main() {
    runAlgo(1);
    return 0;
}

