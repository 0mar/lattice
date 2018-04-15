//
// Created by omar on 15-4-18.
//

#include "simulation.h"
#include <memory>
#include <unistd.h>

Simulation::Simulation(int nx, int ny) {
    this->nx = nx;
    this->ny = ny;
    this->lattice = std::make_shared<Lattice>(nx, ny, 100);

    this->init_grid();
}

void Simulation::run() {
    for (int i = 0; i < 100; i++) {
        lattice->print();
        this->step();
        sleep(1);
    }
}

void Simulation::init_grid() {
    int agent_id = 0;
    lattice->get_field().fill(0);
    for (int row = 0; row < nx; row++) {
        for (int col = 0; col < ny; col++) {
            auto agent = std::make_shared<Agent>(this->lattice, agent_id, row, col);
            agents.push_back(agent);
            agent_id++;
        }
    }
}


void Simulation::step() {
    for (unsigned long i = 0; i < agents.size(); i++) {
        agents.at(i)->update();
    }
}



