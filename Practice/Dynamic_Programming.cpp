#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

// ============================ Problem 3 ============================
int goldMine(const vector<vector<int>>& mine) {
    int m = mine.size(), n = mine[0].size();
    vector<vector<int>> gold(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) gold[i][n - 1] = mine[i][n - 1];
    for (int j = n - 2; j >= 0; j--)
        for (int i = 0; i < m; i++) {
            int best = gold[i][j + 1];
            if (i > 0)     best = max(best, gold[i - 1][j + 1]);
            if (i < m - 1) best = max(best, gold[i + 1][j + 1]);
            gold[i][j] = mine[i][j] + best;
        }
    int ans = gold[0][0];
    for (int i = 1; i < m; i++) ans = max(ans, gold[i][0]);
    return ans;
}

// ============================ Problem 6 ============================
int lps(const string& s) {
    int n = s.size();
    vector<vector<int>> L(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) L[i][i] = 1;
    for (int len = 2; len <= n; len++)
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) L[i][j] = (len == 2) ? 2 : 2 + L[i + 1][j - 1];
            else L[i][j] = max(L[i + 1][j], L[i][j - 1]);
        }
    return L[0][n - 1];
}

// ============================ Problem 9 ============================
struct KadaneResult { int best, top, bottom; };
struct Rectangle    { int sum, top, left, bottom, right; };

// Kadane(a): best sum of consecutive elements, and where that run starts and ends
KadaneResult Kadane(const vector<int>& a) {
    int best = a[0], cur = a[0];
    int s = 0, top = 0, bottom = 0;
    for (int i = 1; i < (int)a.size(); i++) {
        if (cur < 0) { cur = a[i]; s = i; }     // restart the run
        else           cur = cur + a[i];        // extend the run
        if (cur > best) { best = cur; top = s; bottom = i; }
    }
    return {best, top, bottom};
}

// MaxRectangle(A): try every pair of columns (l, r)
Rectangle maxSumRectangle(const vector<vector<int>>& A) {
    int m = A.size(), n = A[0].size();
    Rectangle ans = {INT_MIN, 0, 0, 0, 0};
    for (int l = 0; l < n; l++) {
        vector<int> rowSum(m, 0);
        for (int r = l; r < n; r++) {
            for (int i = 0; i < m; i++)
                rowSum[i] = rowSum[i] + A[i][r];       // add ONE column
            KadaneResult k = Kadane(rowSum);
            if (k.best > ans.sum)
                ans = {k.best, k.top, l, k.bottom, r};
        }
    }
    return ans;
}

int main() {
    cout << "Problem 3. Gold Mine:" << endl;
    cout << "Example 1: " << endl <<   
            "1 3 3" << endl <<
            "2 1 4" << endl <<
            "0 6 4" << endl;
    
    cout << "Result: " << goldMine({{1,3,3},
                                    {2,1,4},
                                    {0,6,4}}) << endl << endl;

    cout << "Example 2: " << endl <<    
            "1 3 1 5" << endl <<
            "2 2 4 1" << endl <<
            "5 0 2 3" << endl <<
            "0 6 1 2" << endl;
    
    cout << "Result: " << goldMine({{1,3,1,5},
                                    {2,2,4,1},
                                    {5,0,2,3},
                                    {0,6,1,2}}) << endl << endl;
    
    cout << "Problem 6. Longest Palindromic Subsequence:" << endl;
    cout << "Example 1: BBABCBCAB" << endl << "Result: " << lps("BBABCBCAB") << endl;
    cout << "Example 2: AGBDBA" << endl << "Result: " << lps("AGBDBA") << endl << endl;

    cout << "Problem 9. Maximum Sum Rectangle:" << endl;
    Rectangle res = maxSumRectangle({   {1 , 2,-1,-4,-20},
                                        {-8,-3, 4, 2,  1},
                                        { 3, 8,10, 1,  3},
                                        {-4,-1, 1, 7,  6}});
    cout << "Max sum: " << res.sum << endl;
    cout << "Top-left: (" << res.top << ", " << res.left << ")" << endl;
    cout << "Bottom-right: (" << res.bottom << ", " << res.right << ")" << endl;
}