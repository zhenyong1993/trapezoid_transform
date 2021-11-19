#include "find_max_rect.h"
#include <iostream>

int main()
{
  std::vector<std::vector<char>> matrix;

  std::vector<char> v1 = {'1', '1', '0', '0', '1'};
  std::vector<char> v2 = {'0', '1', '0', '0', '1'};
  std::vector<char> v3 = {'0', '0', '1', '1', '1'};
  std::vector<char> v4 = {'0', '0', '1', '1', '1'};
  std::vector<char> v5 = {'0', '0', '0', '0', '1'};

  matrix.emplace_back(v1);
  matrix.emplace_back(v2);
  matrix.emplace_back(v3);
  matrix.emplace_back(v4);
  matrix.emplace_back(v5);

  std::cout << maximalRectangle(matrix) << std::endl;

  return 0;
}
