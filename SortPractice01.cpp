#include <iostream>
#include <vector>
using namespace std;

string printArray(vector<int> A)
{
    string s = "[ ";
    for (int n : A) {
        s += to_string(n) + " ";
    }
    s += "]";
    return s;
}

// ============================================

vector<int> bubbleSort(vector<int> A)
{
    int n = A.size();
    int count_c = 0;
    int count_s = 0;

    for (int i = 0; i <= n - 2; i++) {
        bool swapped = false;
        for (int j = 0; j <= n - i - 2; j++) {
            //cout << "Comparing " << A[j] << " > " << A[j + 1] << endl;
            count_c++;
            if (A[j] > A[j + 1]) {
                //cout << "Swapping " << A[j] << " and " << A[j + 1] << endl;
                count_s++;
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
                swapped = true;
                //cout << count_s << ": " << printArray(A) << endl;
            }
        }
        if (swapped == false) {
            break;
        }
    }

    cout << "Comparisons: " << count_c << endl;
    cout << "Swaps: " << count_s << endl;
    
    return A;
}

vector<int> insertionSort(vector<int> A)
{
    int n = A.size();
    for (int i = 1; i <= n - 1; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
    return A;
}

vector<int> selectionSort(vector<int> A)
{
    int n = A.size();
    for (int i = 0; i <= n - 2; i++) {
        int min_i = i;
        for (int j = i; j <= n - 1; j++) {
            if (A[j] < A[min_i]) {
                min_i = j;
            }
        }
        if (i != min_i) {
            int temp = A[i];
            A[i] = A[min_i];
            A[min_i] = temp;
        }
    }
    return A;
}

int main()
{
    vector<int> A = {34, 7, 23, 32, 5, 62, 14, 19};

    cout << printArray(A) << endl;
    cout << printArray(bubbleSort(A)) << endl;

}