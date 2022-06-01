//
// Created by Achiote Tory on 5/31/22.
//

#pragma once

#include <cmath>
#include "../utility/utility.hpp"
#include "map"

int manhattanDistance(std::vector<int> state) {
    return 0;
}

int hammingDistance(Puzzle* puzzle, std::map<int, int> goal) {
    int distance = 0;
    for (int i = 0; i < puzzle->get_state().size(); ++i) {
        distance += sqrt(((i / puzzle->getSize() - goal[puzzle->get_state()[i]] / puzzle->getSize()) * (i / puzzle->getSize() - goal[puzzle->get_state()[i]] / puzzle->getSize())) +
                         ((i % puzzle->getSize() - goal[puzzle->get_state()[i]] % puzzle->getSize()) * (i % puzzle->getSize() - goal[puzzle->get_state()[i]] % puzzle->getSize())));
    }
    return distance;
}

int myDistance(Puzzle* puzzle, std::map<int, int> goal) {
    int distance = 0;
    for (int i = 0; i < puzzle->get_state().size(); ++i) {
        if (i != goal[puzzle->get_state()[i]])
            distance++;
    }
    return distance;
}
