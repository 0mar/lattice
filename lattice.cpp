//
// Created by omar on 2018-04-11.
//

#include "lattice.h"
//#include <stdexcept>
#include <string>
#include <cmath>

Lattice::Lattice(int nx, int ny, float lx, float ly, float max_time) {
    this->nx = nx+2;
    this->ny = ny+2;
    this->lx = lx;
    this->ly = ly;
    this->max_time = max_time;

    this->time = 0;
    this->dt = 0.1;
    this->dx = this->lx / this->nx;
    this->dy = this->ly / this->ny;

    this->lattice = Eigen::ArrayXXi(this->nx, this->ny);
}

void Lattice::update() {

}

void Lattice::init_grid(int number_of_particles) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> random_position(0,nx*ny);
    if (number_of_particles > 0.5 * nx * ny) {
        throw std::invalid_argument("Number of particles is too large for grid. Try smaller number");
    }
    positions = Eigen::ArrayXXi(number_of_particles,2);
    for (int i = 0; i < number_of_particles; i++) {
        bool found_empty_position = false;
        int new_x, new_y;
        while (!found_empty_position) {
            new_x = random_position(mt) % nx;
            new_y = random_position(mt) % ny;
            if (lattice(new_x,new_y)==0 and constant_field(new_x,new_y) < 1) {
                found_empty_position = true;
            }
            positions(i,0) = new_x;
            positions(i,1) = new_y;
            lattice(new_x,new_y) = 1;
        }
    }
}

void Lattice::set_constant_field(float density) {
    constant_field = Eigen::ArrayXXf(nx,ny);
    constant_field = 0;
    constant_field.row(0) = 1;
    constant_field.col(0) = 1;
    constant_field.row(nx-1) = 1;
    constant_field.col(ny-1) = 1;
    if (density > 0) {
        std::cout << "Not supported yet" << std::endl;
    }
}

void Lattice::set_probability() {
    base_probs.setRandom();
    base_probs = (base_probs + 1.)/8;
    base_probs(1,1)=0;
    std::cout << base_probs << std::endl;
}
Eigen::ArrayXXi Lattice::get_field() {

}

void Lattice::print() {
    char obs_char = 'X';
    char part_char = 'o';
    char empty_char = '.';

    for (int row=0;row < nx;row ++ ) {
        for (int col=0;col < ny;col ++ ) {
            if (constant_field(row,col)>=1) {
                std::cout << obs_char;
            } else if (lattice(row,col)==1) {
                std::cout << part_char;
            } else {
                std::cout << empty_char;
            }
        }
        std::cout << std::endl;
    }
}

