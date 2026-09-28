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

string printSubArray(vector<int> A, int start, int end)
{
    string s = "[ ";
    for (int i = start; i <= end; i++) {
        s += to_string(A[i]) + " ";
    }
    s += "]";
    return s;
}

vector<int> subVector(vector<int> A, int start, int end)
{
    vector<int> B = {};
    for (int i = start; i <= end; i++) {
        B.push_back(A[i]);
    }

    return B;
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
                cout << "Pass " << count_s << ": " << printArray(A) << endl;
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
    int count_c = 0;
    int count_s = 0;

    for (int i = 1; i <= n - 1; i++) {
        int key = A[i];
        int j = i - 1;
        
        while (j >= 0 && A[j] > key)
        {
            count_c++;
            A[j + 1] = A[j];
            j--;
        }
        if (j != i - 1) {
            A[j + 1] = key;
            count_s++;
            cout << "Key: " << key << "; Pass " << count_s << ": " << printArray(A) << endl;
        }
    }

    cout << "Comparisons: " << count_c << endl;
    cout << "Swaps: " << count_s << endl;

    return A;
}

vector<int> selectionSort(vector<int> A)
{
    int n = A.size();
    int count_c = 0;
    int count_s = 0;

    for (int i = 0; i <= n - 2; i++) {
        int min_i = i;
        for (int j = i; j <= n - 1; j++) {
            if (A[j] < A[min_i]) {
                count_c++;
                min_i = j;
            }
        }
        if (i != min_i) {
            int temp = A[min_i];
            A[min_i] = A[i];
            A[i] = temp;
            count_s++;
            cout << "Min: " << temp << " at index " << min_i << "; Pass " << count_s << ": " << printArray(A) << endl;
        }
    }

    cout << "Comparisons: " << count_c << endl;
    cout << "Swaps: " << count_s << endl;

    return A;
}

int partition(vector<int>& A, int start, int end)
{
    int i = start - 1;
    int pivot = A[end];

    for (int j = start; j < end; j++) {
        if (A[j] <= pivot) {
            i++;
            int temp = A[j];
            A[j] = A[i];
            A[i] = temp;
        }
    }

    int temp = A[end];
    A[end] = A[i + 1];
    A[i + 1] = temp;

    cout << "Pivot: " << pivot << "; Start: " << start << "; End: " << end << " - "; 
    cout << printSubArray(A, start, end) << " - " << printArray(A) << endl;

    return i + 1;
    
}

void quickSort(vector<int>& A, int start, int end)
{
    if (start < end) {
        int pivot = partition(A, start, end);

        quickSort(A, start, pivot - 1);
        quickSort(A, pivot + 1, end);
    }
}

void merge(vector<int>& A, int low, int mid, int high)
{
    vector<int> L = subVector(A, low, mid);
    vector<int> R = subVector(A, mid + 1, high);

    int l = 0; int r = 0; int a = low;

    while (l < L.size() && r < R.size()) {
        if (L[l] < R[r]) {
            A[a] = L[l];
            l++; a++;
        } else {
            A[a] = R[r];
            r++; a++;
        }
    }
    while (l < L.size()) {
        A[a] = L[l];
        l++; a++;
    }
    while (r < R.size()) {
        A[a] = R[r];
        r++; a++;
    }
}

void mergeSort(vector<int>& A, int low, int high)
{
    cout << "Sub-array: " << printSubArray(A, low, high) << " - " << printArray(A) << endl;
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(A, low, mid);
        mergeSort(A,mid + 1, high);
        merge(A, low, mid, high);
        cout << "Merged array: " << printSubArray(A, low, high) << " - " << printArray(A) << endl;
    }
}

void heapSort(vector<int>& A)
{
    
}

void selectSortType(int p, vector<int> A)
{
    switch (p)
    {
    case 1:
        cout << printArray(A) << endl;
        cout << printArray(bubbleSort(A)) << endl;
        break;
    case 2:
        cout << printArray(A) << endl;
        cout << printArray(insertionSort(A)) << endl;
        break;
    case 3:
        cout << printArray(A) << endl;
        cout << printArray(selectionSort(A)) << endl;
        break;
    case 4:
        cout << printArray(A) << endl;
        quickSort(A, 0, A.size() - 1);
        cout << printArray(A) << endl;
        break;
    case 5: 
        cout << printArray(A) << endl;
        mergeSort(A, 0, A.size() - 1);
        cout << printArray(A) << endl;
        break;
    default:
        break;
    }
}

int main()
{
    vector<int> A = {34, 7, 23, 32, 5, 62, 14, 19};
    cout << "Select a Sorting Algorithm: ";
    int n = 0;
    cin >> n;
    cout << endl;

    selectSortType(n, A);

    return 0;
}