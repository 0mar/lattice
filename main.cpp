#include <iostream>
#include <Eigen/Dense>
#include "simulation.h"

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
    Simulation sim = Simulation(100, 100);
    sim.run();
}