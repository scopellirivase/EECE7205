#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* insertSorted(Node* head, int x) {
    Node* newNode = new Node(x);
    if (head == nullptr || x <= head->data) {
        newNode->next = head;
        return newNode;
    }
    Node* cur = head;
    while (cur->next != nullptr && cur->next->data < x) {
        cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
    return head;
}

void printList(Node* head) {
    for (Node* p = head; p != nullptr; p = p->next)
        cout << p->data << " -> ";
    cout << "NULL" << endl;
}

void freeList(Node* head) {
    while (head != nullptr) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main() {
    Node* head = nullptr;
    int keys[] = {40, 65, 35, 80, 45, 60};

    for (int k : keys) {
        head = insertSorted(head, k);
    }

    printList(head);
    head = insertSorted(head, 42);
    printList(head);
    head = insertSorted(head, 10);
    printList(head);

    freeList(head);
    return 0;
}