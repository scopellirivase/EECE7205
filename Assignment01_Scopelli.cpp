#include <iostream>
#include <vector>
#include <cassert>
#include <math.h>
#include <map>
#include <algorithm>
using namespace std;

// P1
vector<vector<int>> mergeIntervals(vector<vector<int>> intervals)
{
  const int n = intervals.size();
  
  // Edge case: n <= 1
  if (n <= 1) {
    return intervals;
  }

  // Sort intervals based on start time
  for (int i = 0; i <= n - 2; i++) {
    for (int j = 0; j <= n - i - 2; j++) {
      if (intervals[j][0] > intervals[j + 1][0]) {
        vector<int> temp = intervals[j];
        intervals[j] = intervals[j + 1];
        intervals[j + 1] = temp;
      }
    }
  }

  // Merge overlapping intervals
  vector<vector<int>> merged_intervals = {};
  vector<int> prev_interval = intervals[0];
  for (int i = 1; i <= n - 1; i++) {
    if (intervals[i][0] <= prev_interval[1]) {
      if (intervals[i][1] > prev_interval[1]) {
        prev_interval[1] = intervals[i][1];
      }
    } else {
      merged_intervals.push_back(prev_interval);
      prev_interval = intervals[i];
    }
  }
  merged_intervals.push_back(prev_interval);
  
  return merged_intervals;
}

// P2
vector<int> sortCategoriesCount(vector<int> labels)
{
  int n = labels.size();
  int counters[3] = {0, 0, 0};
  for (int i = 0; i <= n - 1; i++) {
    switch (labels[i])
    {
    case 0:
      counters[0]++;
      break;
    case 1:
      counters[1]++;
      break;
    case 2:
      counters[2]++;
      break;
    default:
      break;
    }
  }

  vector<int> sorted = {};
  for (int i = 0; i <= n - 1; i++) {
    if (i < counters[0]) {
      sorted.push_back(0);
    } else if (i < counters[0] + counters[1]) {
      sorted.push_back(1);
    } else if (i < counters[0] + counters[1] + counters[2]) {
      sorted.push_back(2);
    }
  }

  return sorted;
}

vector<int> sortCategoriesDutch(vector<int> labels)
{
  int n = labels.size();
  int low = 0;
  int mid = 0;
  int high = n - 1;

  for (int i = 0; i <= n - 1; i++) {
    if (labels[mid] == 0) {
      int temp = labels[mid];
      labels[mid] = labels[low];
      labels[low] = temp;
      low++;
      mid++;
    } else if (labels[mid] == 1) {
      mid++;
    } else if (labels[mid] == 2) {
      int temp = labels[mid];
      labels[mid] = labels[high];
      labels[high] = temp;
      high--;
    }
  }

  return labels;
}

// P3
string largestNumber(vector<int> vect)
{
  int n = vect.size();
  for (int i = 0; i <= n - 2; i++) {
    for (int j = 0; j <= n - i - 2; j++) {
      int digits1 = floor(log10(vect[j])) + 1;
      int digits2 = floor(log10(vect[j + 1])) + 1;
      int num1 = (vect[j] * pow(10, digits2)) + vect[j + 1];
      int num2 = (vect[j + 1] * pow(10, digits1)) + vect[j];
      if (num1 < num2) {
        int temp = vect[j];
        vect[j] = vect[j + 1];
        vect[j + 1] = temp;
      }
    }
  }

  string order = "";
  for (int i = 0; i <= n - 1; i++) {
    order += to_string(vect[i]);
  }

  return order;
}

// P4
vector<vector<string>> groupAnagrams(vector<string> words)
{
  int n = words.size();
  map<string, vector<string>> g = {};
  vector<vector<string>> groups = {};
  vector<string> keys = {};
  for (int i = 0; i <= n - 1; i++){
    string key = words[i];
    sort(key.begin(), key.end());

    if (g.find(key) != g.end()) {
      g[key].push_back(words[i]);
    } else {
      g[key] = {words[i]};
      keys.push_back(key);
    }
  }
  for (string k : keys) {
    groups.push_back(g[k]);
  }
  return groups;
}

// P5
bool checkAvailability(vector<vector<int>> intervals)
{
  int n = intervals.size();
  for (int i = 0; i <= n-2; i++) {
    for (int j = 0; j <= n - i - 2; j++) {
      if (intervals[j][0] > intervals[j + 1][0] || (intervals[j][0] == intervals[j + 1][0] && intervals[j][1] > intervals[j + 1][1])) {
        vector<int> temp = intervals[j];
        intervals[j] = intervals[j + 1];
        intervals[j + 1] = temp;
      }
    }
  }
  for (int i = 1; i <= n - 1; i++) {
    if (intervals[i][0] < intervals[i - 1][1]) {
      return false;
    }
  }
  return true;
}

// P6
vector<vector<int>> nearestPoints(vector<vector<int>> points, int k)
{
  int n = points.size();
  vector<vector<double>> pdist = {};
  for (int i = 0; i <= n - 1; i++) {
    pdist.push_back({static_cast<double>(i),sqrt(pow(points[i][0],2) + pow(points[i][1],2))});
  }
  
  for (int i = 0; i <= n - 2; i++) {
    for (int j = 0; j <= n - i - 2; j++) {
      if (pdist[j][1] > pdist[j + 1][1]) {
        vector<double> temp = pdist[j];
        pdist[j] = pdist[j + 1];
        pdist[j + 1] = temp;
      }
    }
  }

  vector<vector<int>> result = {};
  for (int i = 0; i <= k - 1; i++) {
    result.push_back(points[static_cast<int>(pdist[i][0])]);
  }
  return result;
}

// P7
vector<int> frequentValues(vector<int> I, int k)
{
  int n = I.size();
  map<int, int> counters = {};
  for (int i = 0; i <= n - 1; i++) {
    if (counters.find(I[i]) != counters.end()) {
      counters[I[i]]++;
    } else {
      counters[I[i]] = 1;
    }
  }

  vector<int> values = {};
  for (int i = 0; i <= k - 1; i++) {
    vector<int> max = {0, 0};
    for (auto [n, f] : counters) {
      if (max[1] < f || (max[1] == f && max[0] > n)) {
        max = {n, f};
      }
    }
    counters.erase(max[0]);
    values.push_back(max[0]);
  }

  return values;
}

// P8
vector<int> mergeSorted(vector<vector<int>> M)
{
  int n = M.size();
  vector<int> sorted = {};
  vector<int> sizes = {};
  for (int i = 0; i <= n - 1; i++) {
    sizes.push_back(M[i].size());
  }
  
  vector<int> pointers(n, 0);
  while (sizes != pointers) {
    int min = NULL;
    int index = 0;
    for (int i = 0; i <= n - 1; i++) {
      if (pointers[i] < sizes[i]) {
        if (min == NULL or min >= M[i][pointers[i]]) {
          min = M[i][pointers[i]];
          index = i;
        }
      }
    }
    sorted.push_back(min);
    pointers[index]++;
  }

  return sorted;
}

// P9
int kLargestElement (vector<int> A, int k)
{
  int n = A.size();
  if (k > n) {
    return NULL;
  }
  for (int i = 0; i <= n - 2; i++) {
    for (int j = 0; j <= n - i - 2; j++) {
      if (A[j] > A[j + 1]) {
        int temp = A[j];
        A[j] = A[j + 1];
        A[j + 1] = temp;
      }
    }
  }
  return A[n - k];
}

// P10
int countInversions(vector<int> A)
{
  int n = A.size();
  int count = 0;
  for (int i = 0; i <= n - 2; i++) {
    for (int j = i + 1; j <= n - 1; j++) {
      if (A[i] > A[j]) {
        count++;
      }
    }
  }
  return count;
}

void testCases() {
  // P1
  #pragma region 
  vector<vector<int>> case1_1 = {{1,3}, {15,18}, {8,10}, {2,6}};
  vector<vector<int>> ans1_1 = {{1,6}, {8,10}, {15,18}};
  assert(mergeIntervals(case1_1) == ans1_1);

  vector<vector<int>> case1_2 = {{1,7}, {7,10}, {2,4}};
  vector<vector<int>> ans1_2 = {{1,10}};
  assert(mergeIntervals(case1_2) == ans1_2);

  vector<vector<int>> case1_3 = {{1,5}};
  vector<vector<int>> ans1_3 = {{1,5}};
  assert(mergeIntervals(case1_3) == ans1_3);

  cout << "Problem 1 Test Cases: Passed" << endl;
  #pragma endregion

  // P2 - Counter
  #pragma region 
  vector<int> case2_1 = {0,1,2,1,2,0,0,1,2,0};
  vector<int> ans2_1 = {0,0,0,0,1,1,1,2,2,2};
  assert(sortCategoriesCount(case2_1) == ans2_1);

  vector<int> case2_2 = {1};
  vector<int> ans2_2 = {1};
  assert(sortCategoriesCount(case2_2) == ans2_2);

  // P2 - Dutch National Flag
  vector<int> case2_3 = {0,1,2,1,2,0,0,1,2,0};
  vector<int> ans2_3 = {0,0,0,0,1,1,1,2,2,2};
  assert(sortCategoriesDutch(case2_3) == ans2_3);

  vector<int> case2_4 = {1};
  vector<int> ans2_4 = {1};
  assert(sortCategoriesDutch(case2_4) == ans2_4);

  cout << "Problem 2 Test Cases: Passed" << endl;
  #pragma endregion

  // P3
  #pragma region 
  vector<int> case3_1 = {16,2,40,9,10};
  string ans3_1 = "94021610";
  assert(largestNumber(case3_1) == ans3_1);

  vector<int> case3_2 = {};
  string ans3_2 = "";
  assert(largestNumber(case3_1) == ans3_1);

  cout << "Problem 3 Test Cases: Passed" << endl;
  #pragma endregion
  
  // P4
  #pragma region 
  vector<string> case4_1 = {"eat","tea","tan","ate","nat","bat"};
  vector<vector<string>> ans4_1 = {{"eat","tea","ate"},{"tan","nat"}, {"bat"}};
  assert(groupAnagrams(case4_1) == ans4_1);

  vector<string> case4_2 = {""};
  vector<vector<string>> ans4_2 = {{""}};
  assert(groupAnagrams(case4_2) == ans4_2);

  vector<string> case4_3 = {"abc", "def", "ghi"};
  vector<vector<string>> ans4_3 = {{"abc"},{"def"},{"ghi"}};
  assert(groupAnagrams(case4_3) == ans4_3);

  cout << "Problem 4 Test Cases: Passed" << endl;

  #pragma endregion

  // P5
  #pragma region 
  vector<vector<int>> case5_1 = {{1,3}, {15,18}, {8,10}, {2,6}};
  bool ans5_1 = false;
  assert(checkAvailability(case5_1) == ans5_1);

  vector<vector<int>> case5_2 = {{1,7}, {7,10}, {10,12}};
  bool ans5_2 = true;
  assert(checkAvailability(case5_2) == ans5_2);

  vector<vector<int>> case5_3 = {{1,5}};
  bool ans5_3 = true;
  assert(checkAvailability(case5_3) == ans5_3);

  cout << "Problem 5 Test Cases: Passed" << endl;
  #pragma endregion

  // P6
  #pragma region 
  vector<vector<int>> case6_1 = {{1,3}, {2,2}, {4,2}};
  int k6_1 = 2;
  vector<vector<int>> ans6_1 = {{2,2},{1,3}};
  assert(nearestPoints(case6_1, k6_1) == ans6_1);

  vector<vector<int>> case6_2 = {{1,1}};
  int k6_2 = 1;
  vector<vector<int>> ans6_2 = {{1,1}};
  assert(nearestPoints(case6_2, k6_2) == ans6_2);

  vector<vector<int>> case6_3 = {{0,1}, {1,0}, {1,-1}};
  int k6_3 = 2;
  vector<vector<int>> ans6_3 = {{0,1},{1,0}};
  assert(nearestPoints(case6_3, k6_3) == ans6_3);

  cout << "Problem 6 Test Cases: Passed" << endl;
  #pragma endregion

  // P7
  #pragma region 
  vector<int> case7_1 = {1,4,2,2,1,1,3};
  int k7_1 = 2;
  vector<int> ans7_1 = {1,2};
  assert(frequentValues(case7_1, k7_1) == ans7_1);

  vector<int> case7_2 = {1,1,2,2,3};
  int k7_2 = 2;
  vector<int> ans7_2 = {1,2};
  assert(frequentValues(case7_2, k7_2) == ans7_2);

  vector<int> case7_3 = {1};
  int k7_3 = 1;
  vector<int> ans7_3 = {1};
  assert(frequentValues(case7_3, k7_3) == ans7_3);

  cout << "Problem 7 Test Cases: Passed" << endl;
  #pragma endregion

  // P8
  #pragma region 
  vector<vector<int>> case8_1 = {{1,2,4},{2,3},{4,5,6}};
  vector<int> ans8_1 = {1,2,2,3,4,4,5,6};
  assert(mergeSorted(case8_1) == ans8_1);

  vector<vector<int>> case8_2 = {{1,2,3},{}};
  vector<int> ans8_2 = {1,2,3};
  assert(mergeSorted(case8_2) == ans8_2);

  vector<vector<int>> case8_3 = {{1,2,3},{4,5,6}};
  vector<int> ans8_3 = {1,2,3,4,5,6};
  assert(mergeSorted(case8_3) == ans8_3);

  cout << "Problem 8 Test Cases: Passed" << endl;

  #pragma endregion

  // P9
  #pragma region 
  vector<int> case9_1 = {6,5,4,3,2,1};
  int k9_1 = 2;
  int ans9_1 = 5;
  assert(kLargestElement(case9_1, k9_1) == ans9_1);

  vector<int> case9_2 = {};
  int k9_2 = 1;
  int ans9_2 = NULL;
  assert(kLargestElement(case9_2, k9_2) == ans9_2);

  vector<int> case9_3 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
  int k9_3 = 6;
  int ans9_3 = 3;
  assert(kLargestElement(case9_3, k9_3) == ans9_3);

  cout << "Problem 9 Test Cases: Passed" << endl;

  #pragma endregion

  // P10
  #pragma region 
  vector<int> case10_1 = {2,4,1,3,5};
  int ans10_1 = 3;
  assert(countInversions(case10_1) == ans10_1);

  vector<int> case10_2 = {};
  int ans10_2 = 0;
  assert(countInversions(case10_2) == ans10_2);

  vector<int> case10_3 = {4,3,2,1};
  int ans10_3 = 6;
  assert(countInversions(case10_3) == ans10_3);

  cout << "Problem 10 Test Cases: Passed" << endl;

  #pragma endregion
}

int main()
{
  testCases();  
  return 0;
}
