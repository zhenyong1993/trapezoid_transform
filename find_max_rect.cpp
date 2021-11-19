#include "find_max_rect.h"

#include <algorithm>
#include <iostream>
#include <stack>

int maximalRectangle(std::vector<std::vector<char>>& matrix)
{
  if (matrix.empty() || matrix[0].empty())
    return 0;
  int res = 0, m = matrix.size(), n = matrix[0].size();
  std::vector<int> height(n, 0), left(n, 0), right(n, n - 1);
  for (int i = 0; i < m; ++i) {
    int cur_left = 0, cur_right = n - 1;
    for (int j = 0; j < n; ++j) {
      if (matrix[i][j] == '1') {
        ++height[j];
        left[j] = std::max(left[j], cur_left);
      } else {
        height[j] = 0;
        left[j] = 0;
        cur_left = j + 1;
      }
    }
    for (int j = n - 1; j >= 0; --j) {
      if (matrix[i][j] == '1') {
        right[j] = std::min(right[j], cur_right);
      } else {
        right[j] = n - 1;
        cur_right = j - 1;
      }
      int area = (right[j] + 1 - left[j]) * height[j];
      std::cout << " " << area;
      res = std::max(res, area);
    }
    int t = 1;
  }
  return res;
}

// int maximalRectangle(std::vector<std::vector<char>>& matrix) {
//     if (matrix.empty() || matrix[0].empty()) return 0;
//     int res = 0, m = matrix.size(), n = matrix[0].size();
//     std::vector<int> height(n + 1, 0);

//     int max_i = -1, max_j = -1, max_cur = -1;

//     for (int i = 0; i < m; ++i) {
//         std::stack<int> s;
//         for (int j = 0; j < n + 1; ++j) {
//             if (j < n) {
//                 height[j] = matrix[i][j] == '1' ? height[j] + 1 : 0;
//             }
//             while (!s.empty() && height[s.top()] >= height[j]) {
//                 int cur = s.top(); s.pop();
//                 // res = std::max(res, height[cur] * (s.empty() ? j : (j -
//                 s.top() - 1))); int curr_area = height[cur] * (s.empty() ? j
//                 : (j - s.top() - 1)); if (res < curr_area) {
//                     res = curr_area;
//                     max_i = i;
//                     max_j = j;
//                     max_cur = cur;
//                 }
//             }
//             s.push(j);
//         }
//     }

//     std::cout << "i: " << max_i << ", j: " << max_j << ", cur: " << max_cur
//     << std::endl; return res;
// }

// https://www.cnblogs.com/ariel-dreamland/p/9159219.html
// int maximalRectangle(std::vector<std::vector<char>>& matrix) {
//     if (matrix.empty() || matrix[0].empty()) return 0;
//     int res = 0, m = matrix.size(), n = matrix[0].size();
//     std::vector<int> height(n + 1, 0);
//     for (int i = 0; i < m; ++i) {
//         std::stack<int> s;
//         for (int j = 0; j < n + 1; ++j) {
//             if (j < n) {
//                 height[j] = matrix[i][j] == '1' ? height[j] + 1 : 0;
//             }
//             while (!s.empty() && height[s.top()] >= height[j]) {
//                 int cur = s.top(); s.pop();
//                 res = std::max(res, height[cur] * (s.empty() ? j : (j -
//                 s.top() - 1)));
//             }
//             s.push(j);
//         }
//     }
//     return res;
// }

// int maximalRectangle(std::vector<std::vector<char>>& matrix) {
//     if (matrix.empty() || matrix[0].empty()) return 0;
//     int res = 0, m = matrix.size(), n = matrix[0].size();
//     std::vector<int> height(n, 0), left(n, 0), right(n, n);
//     for (int i = 0; i < m; ++i) {
//         int cur_left = 0, cur_right = n;
//         for (int j = 0; j < n; ++j) {
//             if (matrix[i][j] == '1') {
//                 ++height[j];
//                 left[j] = std::max(left[j], cur_left);
//             } else {
//                 height[j] = 0;
//                 left[j] = 0;
//                 cur_left = j + 1;
//             }
//         }
//         for (int j = n - 1; j >= 0; --j) {
//             if (matrix[i][j] == '1') {
//                 right[j] = std::min(right[j], cur_right);
//             } else {
//                 right[j] = n;
//                 cur_right = j;
//             }
//             res = std::max(res, (right[j] - left[j]) * height[j]);
//         }
//     }
//     return res;
// }
