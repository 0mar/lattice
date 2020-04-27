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
    this->is_done = false;
    this->init_grid();
}

void Simulation::run() {
    for (int i = 0; i < 100; i++) {
        lattice->count_and_print();
        this->step();
        if (is_done) {
            break;
        }
        sleep(1);
    }
    lattice->print_totals();
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
    bool has_update = false;
    for (unsigned long i = 0; i < agents.size(); i++) {
        agents.at(i)->update(has_update);
    }
    is_done = not has_update;
}



