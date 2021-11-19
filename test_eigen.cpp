#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;

int main()
{
  MatrixXd m = MatrixXd::Random(8, 8);
  std::cout << m << std::endl;
}
