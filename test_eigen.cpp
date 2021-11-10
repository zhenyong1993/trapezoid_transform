#include <iostream>
#include <Eigen/Dense>
 
using namespace Eigen;
// using namespace std;
 
int main()
{
  MatrixXd m = MatrixXd::Random(8, 8);
  std::cout << m << std::endl;
}
