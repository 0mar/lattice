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
    Lattice(int nx, int ny, float max_time);

    void set_at(int pos_x, int pos_y, int val);

    Eigen::ArrayXXi get_field();

    void print();

    float get_random_float();

    int get_connections_in_range(int pos_x, int pos_y, int status, int range);

private:
    int nx, ny;
    std::shared_ptr<std::random_device> rd;
    std::shared_ptr<std::mt19937> rng;
    std::shared_ptr<std::uniform_real_distribution<float>> random_real;
    Eigen::ArrayXXi lattice;

    bool exists(int row, int col);

};


#endif //LATTICE_LATTICE_H
