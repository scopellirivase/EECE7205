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
    int count_c = 0; // Initialize count of comparisons
    int count_s = 0; // Initialize count of swaps

    for (int i = 0; i <= n - 2; i++) {
        bool swapped = false;
        for (int j = 0; j <= n - i - 2; j++) {
            count_c++;
            if (A[j] > A[j + 1]) {
                count_s++;
                int temp = A[j]; // Swap array values using a temporal variable
                A[j] = A[j + 1];
                A[j + 1] = temp;
                swapped = true;
                cout << "Pass " << count_s << ": " << printArray(A) << endl;
            }
        }
        if (swapped == false) { // No swaps means the array is in order
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
        int key = A[i]; // Define key value for each iteration
        int j = i - 1;
        count_c++;
        
        while (j >= 0 && A[j] > key)
        {
            count_c++;
            count_s++;
            A[j + 1] = A[j]; // Shift larger values to the right
            j--;
        }
        if (j != i - 1) {
            A[j + 1] = key; // Insert key value into it's final position
            cout << "Key: " << key << "; Pass " << count_s << ": " << printArray(A) << endl;
        }
    }

    cout << "Comparisons: " << count_c << endl;
    cout << "Insertions: " << count_s << endl;

    return A;
}

vector<int> selectionSort(vector<int> A)
{
    int n = A.size();
    int count_c = 0;
    int count_s = 0;

    for (int i = 0; i <= n - 2; i++) {
        int min_i = i;
        for (int j = i + 1; j <= n - 1; j++) {
            count_c++;
            if (A[j] < A[min_i]) {
                min_i = j;  // Determine index of smallest value
            }
        }
        if (i != min_i) {
            int temp = A[min_i];    // Swaps smallest value to beginning of the array
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

#pragma region Quick Sort
int partition(vector<int>& A, int start, int end)
{
    int i = start - 1;
    int pivot = A[end]; // Pivot selected at the end of the array

    for (int j = start; j < end; j++) {
        if (A[j] <= pivot) {
            i++;        // Determine final position for pivot value
            int temp = A[j];
            A[j] = A[i];
            A[i] = temp;
        }
    }

    int temp = A[end];  // Swap pivot value to it's corresponding position
    A[end] = A[i + 1];
    A[i + 1] = temp;

    cout << "Pivot: " << pivot << "; Start: " << start << "; End: " << end << " - "; 
    cout << printSubArray(A, start, end) << " - " << printArray(A) << endl;

    return i + 1;
}

void quickSort(vector<int>& A, int start, int end)
{
    if (start < end) {
        int pivot = partition(A, start, end); // Determine pivot value to split array

        quickSort(A, start, pivot - 1); // Split array along pivot and repeat process
        quickSort(A, pivot + 1, end);
    }
}
#pragma endregion

#pragma region Merge Sort
void merge(vector<int>& A, int low, int mid, int high)
{
    vector<int> L = subVector(A, low, mid);     // Use helper function to split array
    vector<int> R = subVector(A, mid + 1, high);

    int l = 0; int r = 0; int a = low;  // Initialize pointers per array

    while (l < L.size() && r < R.size()) {  // Merge arrays L and R by smallest values
        if (L[l] < R[r]) {
            A[a] = L[l];
            l++; a++;
        } else {
            A[a] = R[r];
            r++; a++;
        }
    }
    while (l < L.size()) {  // Add remaining values in arrays L / R
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
        mergeSort(A, low, mid);     // Split input array into two
        mergeSort(A,mid + 1, high);
        merge(A, low, mid, high);   // Merge split arrays
        cout << "Merged array: " << printSubArray(A, low, high) << " - " << printArray(A) << endl;
    }
}
#pragma endregion

#pragma region Heap Sort
void heapify(vector<int>& A, int n, int i)
{
    int max = i;    // Index values for a parent - children pair in a binary tree
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[max]) {
        max = left;
    }
    if (right < n && A[right] > A[max]) {
        max = right;
    }
    if (max != i) {     // Move largest element to parent position (max heap constraint)
        int temp = A[i];
        A[i] = A[max];
        A[max] = temp;

        heapify(A, n, max); // Move down binary tree
    }
}

void heapSort(vector<int>& A){
    int n = A.size();

    for (int i = n / 2 - 1; i >= 0; i--) {  // Create initial max-heap
        heapify(A, n, i);
    }
    cout << "Initial max heap: " << printArray(A) << endl;
    
    for (int i = n - 1; i > 0; i--) {
        int temp = A[0];    // Move largest value to the end
        A[0] = A[i];
        A[i] = temp;
        cout << "Iteration " << n - i << " - " << printArray(A) << endl;
        heapify(A, i, 0);
        cout << "Max heap  " << n - i << " - " << printArray(A) << endl;
    }
}
#pragma endregion

void selectSortType(int p, vector<int> A)
{
    switch (p)
    {
    case 1: // Bubble Sort Algorithm
        cout << printArray(A) << endl;
        cout << printArray(bubbleSort(A)) << endl;
        break;
    case 2: // Insertion Sort Algorithm
        cout << printArray(A) << endl;
        cout << printArray(insertionSort(A)) << endl;
        break;
    case 3: // Selection Sort Algorithm
        cout << printArray(A) << endl;
        cout << printArray(selectionSort(A)) << endl;
        break;
    case 4: // Quick Sort Algorithm
        cout << printArray(A) << endl;
        quickSort(A, 0, A.size() - 1);
        cout << printArray(A) << endl;
        break;
    case 5: // Merge Sort Algorithm
        cout << printArray(A) << endl;
        mergeSort(A, 0, A.size() - 1);
        cout << printArray(A) << endl;
        break;
    case 6: // Heap Sort Algorithm
        cout << printArray(A) << endl;
        heapSort(A);
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



