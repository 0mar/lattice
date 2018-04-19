#include <iostream>
#include <Eigen/Dense>
#include "simulation.h"

using Eigen::ArrayXXf;

int main(int argc, char **argv) {
    int nx = 100;
    int ny = 100;
    if (argc==3) {
        nx = (int)strtol(argv[1],nullptr,0);
        ny = (int)strtol(argv[2],nullptr,0);
    }
    std::cout << nx << ny << std::endl;
    Simulation sim = Simulation(nx, ny);
    sim.run();
}
