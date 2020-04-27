//
// Created by omar on 15-4-18.
//

#ifndef LATTICE_SIMULATION_H
#define LATTICE_SIMULATION_H


#include "lattice.h"
#include "agent.h"

class Simulation {

public:
    Simulation(int nx,int ny);

    void run();

private:
    std::shared_ptr<Lattice> lattice;
    void init_grid();
    int nx;
    int ny;
    bool is_done;
    std::vector<std::shared_ptr<Agent>> agents;
    void step();



};


#endif //LATTICE_SIMULATION_H
