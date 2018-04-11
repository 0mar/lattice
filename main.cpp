#include <iostream>
#include <Eigen/Dense>
#include "lattice.h"

using Eigen::MatrixXd;

int main() {
//    MatrixXd m(2, 2);
//    m(0, 0) = 3;
//    m(1, 0) = 2.5;
//    m(0, 1) = -1;
//    m(1, 1) = m(1, 0) + m(0, 1);
    //std::cout << m << std::endl;
    Lattice l = Lattice(5, 5, 2, 2, 4);
    l.init_grid(5);
}