#include <iostream>
#include <vector>
#include <cassert>
#include <math.h>
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

// P4 -- PENDING
vector<vector<string>> groupAnagrams(vector<string> words)
{
  int n = words.size();
  vector<vector<string>> groups = {};
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

}

void testCases() {
  // P1
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

  // P2 - Counter
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

  // P3
  vector<int> case3_1 = {16,2,40,9,10};
  string ans3_1 = "94021610";
  assert(largestNumber(case3_1) == ans3_1);

  vector<int> case3_2 = {};
  string ans3_2 = "";
  assert(largestNumber(case3_1) == ans3_1);

  cout << "Problem 3 Test Cases: Passed" << endl;

  // P5
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

  // P6
}

int main()
{
  testCases();  
  return 0;
}
