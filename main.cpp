#include <iostream>
#include <Eigen/Dense>
#include "lattice.h"
#include <unistd.h>

using Eigen::ArrayXXf;

int main() {
//    ArrayXXf m(10, 10);
//    for (int i=0;i<10;i++) {
//        for (int j=0;j<10;j++) {
//            m(i,j) = i/3. + j/7.;
//        }
//    }
//    std::cout << m << std::endl;
//    std::cout << m.block<3,3>(3,4) << std::endl;
//    for (int i=0;i<m.size();i++) {
//        std::cout << m(i) << std::endl;
//    }
    Lattice l = Lattice(200, 20, 2, 2, 4);
    l.set_constant_field(0);
    l.set_probability(3);
    l.init_grid(300);
    for (int i = 0; i < 50; i++) {
        l.print();
        l.update();
        sleep(1);
    }
}