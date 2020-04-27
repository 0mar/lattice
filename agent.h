//
// Created by omar on 15-4-18.
//

#ifndef LATTICE_AGENT_H
#define LATTICE_AGENT_H


#include <memory>
#include "lattice.h"

class Agent {
public:
    Agent(std::shared_ptr<Lattice> lattice, int id, int pos_x, int pos_y);

    static const int NORMAL = 0;
    static const int SATISFIED = 1;
    static const int DISSATISFIED = 2;
    static const int REJECTING = 3;

    int get_id();

    int get_index();

    int get_status();

    int get_location();

    void update(bool &has_update);

    int get_num_strong_connections(int status);

    int get_num_weak_connections(int status);

    float get_prob_pos();

    float get_prob_neg();

private:
    std::shared_ptr<Lattice> lattice;
    int id;
    int index;
    int status;
    int location;
    int pos_x;
    int pos_y;
    int influence;
    float prob_adopt;
    float prob_reject;
    float prob_none;

    struct Parameters {
        float p_ads;
        float q_interact;
        float q_strong;
        float q_weak;
        float neg_mass;
        float p_satisfied;
    }; // todo wtf how should i do this?

    Parameters params;
};


#endif //LATTICE_AGENT_H
