//
// Created by omar on 2018-04-11.
//

#ifndef LATTICE_LATTICE_H
#define LATTICE_LATTICE_H

#include <Eigen/Dense>
#include <iostream>
#include <random>
#include <memory>
class Lattice {
public:

    Lattice(int nx, int ny, float lx, float ly, float max_time);

    void update();

    Eigen::ArrayXXi get_field();
    void init_grid(int number_of_particles);
    void set_constant_field(float density);

    void set_probability(int probability_setting);
    void print();

private:

    int nx, ny;
    int number_of_particles;
    float lx, ly;
    float max_time;
    float dt, time;
    float dx, dy;
    std::shared_ptr<std::random_device> rd;
    std::shared_ptr<std::mt19937> rng;
    std::shared_ptr<std::uniform_real_distribution<float>> random_real;
    Eigen::ArrayXXi lattice;
    Eigen::ArrayXXi positions;
    Eigen::ArrayXXf constant_field, dynamic_field;
    Eigen::Array33f base_probs;

    int get_direction_from_probs(Eigen::Array33f);
};


#endif //LATTICE_LATTICE_H
