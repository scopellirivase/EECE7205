#include <iostream>
#include <vector>
using namespace std;

class Stack {
    private:
        vector<int> data;
    public:
        void push(int val) {
            data.push_back(val);
        }
        void pop() {
            if(isEmpty()) {
                throw out_of_range("Stack underflow: pop() called on empty stack");
            }
            data.pop_back();
        }
        int top() const {
            if(isEmpty()) {
                throw out_of_range("Stack underflow: top() called on empty stack");
            }
            return data.back();
        }
        bool isEmpty() const {
            return data.empty();
        }
        int size() const {
            return data.size();
        }
};

int main()
{
    Stack s1;

    int keys[4] = {10, 20, 30, 40};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        cout << keys[i] << " ";
    }
    cout << endl << n << endl;
}