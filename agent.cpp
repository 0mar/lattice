//
// Created by omar on 15-4-18.
//

#include "agent.h"


Agent::Agent(std::shared_ptr<Lattice> lattice, int id, int pos_x, int pos_y) {
    this->lattice = lattice;
    this->id = id;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->status = this->NORMAL;

    params.p_ads = 0.01;
    params.q_interact = 0.03;
    params.q_strong = 0.03;
    params.q_weak = 0.01;
    params.neg_mass = 1;
    params.p_satisfied = 0.8;
}


void Agent::update() {
    if (status==NORMAL) {
        float prob_neg = get_prob_neg();
        float prob_pos = get_prob_pos();
        float alpha_prob = prob_pos / (prob_pos + prob_neg);
        prob_adopt = (1 - prob_neg) * prob_pos + alpha_prob * prob_neg * prob_pos;
        prob_reject = (1 - prob_pos) * prob_neg + (1 - alpha_prob) * prob_neg * prob_pos;
        prob_none = (1 - prob_pos) * (1 - prob_neg);
        float to_adopt = lattice->get_random_float();
        if (to_adopt < prob_adopt) {
            float to_satisfy = lattice->get_random_float();
            if (to_satisfy < params.p_satisfied) {
                status = SATISFIED;
            } else {
                status = DISSATISFIED;
            }
        } else if (to_adopt < prob_adopt + prob_reject) {
            status = REJECTING;
        }
        lattice->set_at(pos_x, pos_y, status);
    }
}

int Agent::get_id() {
    return id;
}

int Agent::get_index() {
    return index;
}

int Agent::get_status() {
    return status;
}

int Agent::get_num_strong_connections(int status) {
    return this->lattice->get_connections_in_range(pos_x, pos_y, status, 1);
}

int Agent::get_num_weak_connections(int status) {
    return this->lattice->get_connections_in_range(pos_x, pos_y, status, 2);
}

float Agent::get_prob_pos() {
    float strong_part = (float) pow(1 - params.q_strong, get_num_strong_connections(SATISFIED));
    float weak_part = (float) pow(1 - params.q_weak, get_num_weak_connections(SATISFIED));
    return 1 - (1 - params.p_ads) * strong_part * weak_part;
}

float Agent::get_prob_neg() {
    //Todo: not optimal... better to loop once over the area and count all the connections.
    float strong_dis_part = (float) pow(1 - params.neg_mass * params.q_strong,
                                        get_num_strong_connections(DISSATISFIED));
    float weak_dis_part = (float) pow(1 - params.neg_mass * params.q_weak,
                                      get_num_weak_connections(DISSATISFIED));
    float strong_rej_part = (float) pow(1 - params.neg_mass * params.q_strong,
                                        get_num_strong_connections(REJECTING));
    float weak_rej_part = (float) pow(1 - params.neg_mass * params.q_weak,
                                      get_num_weak_connections(REJECTING));
    return 1 - strong_dis_part * weak_dis_part * strong_rej_part * weak_rej_part;
}


int Agent::get_location() {
    return location;
}


