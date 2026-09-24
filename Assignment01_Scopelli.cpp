#include <iostream>
#include <vector>
#include <cassert>
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

void testCases() {
  // P1
  vector<vector<int>> case1_1 = {{1,3}, {15,18}, {8,10}, {2,6}};
  vector<vector<int>> ans1_1 = {{2,6}, {8,10}, {15,18}};
  assert(mergeIntervals(case1_1) == ans1_1);

  cout << "Problem 1 Test Cases: Passed" << endl;
}

int main()
{
  testCases();
  return 0;
}
