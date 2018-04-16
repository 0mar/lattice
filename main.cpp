#include <iostream>
#include <Eigen/Dense>
#include "simulation.h"

using Eigen::ArrayXXf;

int main() {
    Simulation sim = Simulation(100, 100);
    sim.run();
}