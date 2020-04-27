//
// Created by omar on 2018-04-11.
//

#include "lattice.h"

Lattice::Lattice(int nx, int ny, float max_time) {
    this->nx = nx;
    this->ny = ny;

    this->lattice = Eigen::ArrayXXi(this->nx, this->ny);
    rd = std::make_shared<std::random_device>();
    rng = std::make_shared<std::mt19937>((*rd)());
    random_real = std::make_shared<std::uniform_real_distribution<float>>(0, 1);

    for (int i = 0; i < 4; i++) {
        totals[i] = std::vector<int>(); // Todo: Necessary line?
    }
}

int Lattice::get_connections_in_range(int pos_x, int pos_y, int status, int range) {
    int num_connections = 0;
    for (int row = pos_x - range; row < pos_x + range + 1; row++) {
        for (int col = pos_y - range; col < pos_y + range + 1; col++) {
            if (exists(row, col) and lattice(row, col) == status and not(row == pos_x and col == pos_y)) {
                num_connections++;
            }
        }
    }
    return num_connections;
}


bool Lattice::exists(int row, int col) {
    return row >= 0 and row < nx and col >= 0 and col < ny;
}


void Lattice::set_at(int pos_x, int pos_y, int val) {
    if (exists(pos_x, pos_y)) {
        lattice(pos_x, pos_y) = val;
    } else {
        throw std::invalid_argument("No such element exist on the lattice");
    }

}

Eigen::ArrayXXi Lattice::get_field() {
    return this->lattice;
}

float Lattice::get_random_float() {
    return (*random_real)(*rng);
}

void Lattice::count_and_print() {
    int normal = 0;
    int satisfied = 1;
    int dissatisfied = 2;
    int rejecting = 3;
    char char_array[4] = {'.', 'o', 'x', 'r'};
    int stat_array[4] = {0, 0, 0, 0};
    for (int col = ny - 1; col >= 0; col--) {
        for (int row = 0; row < nx; row++) {
            std::cout << char_array[lattice(row, col)];
            stat_array[lattice(row, col)]++;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < 4; i++) {
        totals[i].push_back(stat_array[i]);
        std::cout << stat_array[i] << std::endl;
    }
}

void Lattice::count() {
    int stat_array[4] = {0, 0, 0, 0};
    for (int col = ny - 1; col >= 0; col--) {
        for (int row = 0; row < nx; row++) {
            stat_array[lattice(row, col)]++;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < 4; i++) {
        totals[i].push_back(stat_array[i]);
    }
}

void Lattice::print_totals() {
    std::string names[4] = {"normal", "satisfied", "dissatisfied", "rejecting"};
    std::ofstream count_file;
    count_file.open("totals.py");
    count_file << "import numpy as np" << std::endl << "import matplotlib.pyplot as plt" << std::endl;

    for (int i = 0; i < 4; i++) {
        count_file << names[i] << " = [";
        for (int count: totals[i]) {
            count_file << count * 1. / (nx * ny) << ", ";
        }
        count_file << "]" << std::endl;
    }
    count_file << "all = [";
    for (std::string name:names) {
        count_file << name << ", ";
    }
    count_file << "]" << std::endl;
    count_file << "for list in all:" << std::endl << "\tplt.plot(np.array(list))" << std::endl;
    count_file << "plt.legend([";
    for (std::string name:names) {
        count_file << "'" << name << "', ";
    }
    count_file << "])" << std::endl;
    count_file << "plt.show()" << std::endl;
}