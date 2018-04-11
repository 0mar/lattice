//
// Created by omar on 2018-04-11.
//

#ifndef LATTICE_LATTICE_H
#define LATTICE_LATTICE_H

#include <Eigen/Dense>
#include <iostream>
#include <random>

class Lattice {
public:

    Lattice(int nx, int ny, float lx, float ly, float max_time);

    void update();

    Eigen::ArrayXXi get_field();
    void init_grid(int number_of_particles);
    void set_constant_field(float density);
    void set_probability();
    void print();

private:

    int nx, ny;
    float lx, ly;
    float max_time;
    float dt, time;
    float dx, dy;
//    std::default_random_engine rng;
//    std::uniform_int_distribution random_int;
//    std::uniform_real_distribution<float> random_real;
    Eigen::ArrayXXi lattice;
    Eigen::ArrayXXi positions;
    Eigen::ArrayXXf constant_field, dynamic_field;
    Eigen::Array33f base_probs;
};


#endif //LATTICE_LATTICE_H
