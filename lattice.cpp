//
// Created by omar on 2018-04-11.
//

#include "lattice.h"

Lattice::Lattice(int nx, int ny, float lx, float ly, float max_time) {
    this->nx = nx + 2;
    this->ny = ny + 2;
    this->lx = lx;
    this->ly = ly;
    this->max_time = max_time;

    this->time = 0;
    this->dt = 0.1;
    this->dx = this->lx / this->nx;
    this->dy = this->ly / this->ny;

    this->lattice = Eigen::ArrayXXi(this->nx, this->ny);
    rd = std::make_shared<std::random_device>();
    rng = std::make_shared<std::mt19937>((*rd)());
    random_real = std::make_shared<std::uniform_real_distribution<float>>(0, 1);
}

void Lattice::update() {
    for (int i = 0; i < number_of_particles; i++) {
        int old_x = positions(i, 0);
        int old_y = positions(i, 1);
        lattice(old_x, old_y) = 0;
        Eigen::Array33f new_probs = base_probs.cwiseProduct(constant_field.block<3, 3>(old_x - 1, old_y - 1));
        int direction = get_direction_from_probs(new_probs);
        int dir_plus_x = direction % 3 - 1;
        int dir_plus_y = direction / 3 - 1;
        int new_x = old_x + dir_plus_x;
        int new_y = old_y + dir_plus_y;
        if (lattice(new_x, new_y) == 0) {
            positions(i, 0) = new_x;
            positions(i, 1) = new_y;
            lattice(new_x, new_y) = 1;
        } else {
            lattice(old_x, old_y) = 1;
        }
    }
    time += dt;
}

void Lattice::init_grid(int number_of_particles) {
    std::uniform_int_distribution<int> random_position(0, nx * ny);
    if (number_of_particles > 0.5 * nx * ny) {
        throw std::invalid_argument("Number of particles is too large for grid. Try smaller number");
    }
    positions = Eigen::ArrayXXi(number_of_particles, 2);
    lattice.setZero();
    for (int i = 0; i < number_of_particles; i++) {
        bool found_empty_position = false;
        int new_x, new_y;
        while (!found_empty_position) {
            new_x = random_position(*rng) % nx;
            new_y = random_position(*rng) % ny;
            if (lattice(new_x, new_y) == 0 and constant_field(new_x, new_y) > 0) {
                found_empty_position = true;
                positions(i, 0) = new_x;
                positions(i, 1) = new_y;
                lattice(new_x, new_y) = 1;
            }
        }
    }
    this->number_of_particles = number_of_particles;
}

void Lattice::set_constant_field(float density) {
    constant_field.setOnes(nx, ny);
    constant_field.row(0) = 0;
    constant_field.col(0) = 0;
    constant_field.row(nx - 1) = 0;
    constant_field.col(ny - 1) = 0;
    if (density > 0) {
        std::cout << "Not supported yet" << std::endl;
    }
}

void Lattice::set_probability(int probability_setting) {
    switch (probability_setting) {
        case 0:
            std::cout << "Moving probabilies random" << std::endl;
            base_probs.setRandom();
            base_probs = (base_probs + 1.) / 8;
            break;
        case 1:
            std::cout << "Moving probabilies uniform" << std::endl;
            base_probs.setOnes();
            base_probs = base_probs / 8;
            break;
        case 2:
            std::cout << "Moving probabilies axially" << std::endl;
            base_probs.setOnes();
            base_probs = base_probs / 4;
            base_probs(0, 0) = 0;
            base_probs(2, 2) = 0;
            base_probs(0, 2) = 0;
            base_probs(2, 0) = 0;
            break;
        case 3:
            std::cout << "Moving upwards with a drift" << std::endl;
            base_probs.setZero();
            base_probs(1, 2) = 0.01;
            base_probs(1, 0) = 0.03;
            base_probs(0, 1) = 1;
            base_probs(2, 1) = 0.03;
            break;
        default:
            throw std::invalid_argument("Unrecognized probablity setting");
    }
    base_probs(1, 1) = 0;
    std::cout << base_probs << std::endl;
}


Eigen::ArrayXXi Lattice::get_field() {
    return this->lattice;
}

void Lattice::print() {
    char obs_char = 'X';
    char part_char = 'o';
    char empty_char = '.';

    for (int col = ny - 1; col >= 0; col--) {
        for (int row = 0; row < nx; row++) {
            if (constant_field(row, col) <= -1) {
                std::cout << obs_char;
            } else if (lattice(row, col) == 1) {
                std::cout << part_char;
            } else {
                std::cout << empty_char;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int Lattice::get_direction_from_probs(Eigen::Array33f new_probs) {
    float total_prob = new_probs.sum();
    float rand_num = (*random_real)(*rng) * total_prob;
    for (int direction = 0; direction < new_probs.size(); direction++) {
        rand_num -= new_probs(direction);
        if (rand_num < 0) {
            return direction;
        }
    }
    throw std::invalid_argument("Something went wrong in numerical random number generator. Please check");
    return -1;
}