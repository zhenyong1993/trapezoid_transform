#include <iostream>
#include "find_max_rect.h"

int main()
{
    std::vector<std::vector<char>> matrix;

    // std::vector<char> v1 = {'1', '0', '1', '0', '0'};
    // std::vector<char> v2 = {'1', '0', '1', '1', '1'};
    // std::vector<char> v3 = {'1', '1', '1', '1', '1'};
    // std::vector<char> v4 = {'1', '0', '0', '1', '0'};

    std::vector<char> v1 = {'1', '1', '0', '0', '1'};
    std::vector<char> v2 = {'0', '1', '0', '0', '1'};
    std::vector<char> v3 = {'0', '0', '1', '1', '1'};
    std::vector<char> v4 = {'0', '0', '1', '1', '1'};
    std::vector<char> v5 = {'0', '0', '0', '0', '1'};

    matrix.push_back(v1);
    matrix.push_back(v2);
    matrix.push_back(v3);
    matrix.push_back(v4);
    matrix.push_back(v5);

    std::cout << maximalRectangle(matrix) << std::endl;

    return 0;
}
