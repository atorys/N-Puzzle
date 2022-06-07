//
// Created by Achiote Tory on 5/31/22.
//

#pragma once

#include <cmath>
#include "../utility/utility.hpp"
#include "map"

int manhattanDistance(std::vector<int> sequence) {
    return 0;
}

float euclideanDistance(Puzzle const& puzzle, std::map<int, int> goal) {
    float distance = 0;
    for (int i = 0; i < puzzle.get_sequence().size(); ++i) {
        distance += (float)sqrt(((i / puzzle.get_size() - goal[puzzle.get_sequence()[i]] / puzzle.get_size()) * (i / puzzle.get_size() - goal[puzzle.get_sequence()[i]] / puzzle.get_size())) +
                         ((i % puzzle.get_size() - goal[puzzle.get_sequence()[i]] % puzzle.get_size()) * (i % puzzle.get_size() - goal[puzzle.get_sequence()[i]] % puzzle.get_size())));
    }
    return distance;
}

float chebDistance(Puzzle const& puzzle, std::map<int, int> goal) {
    float distance = 0;
    for (int i = 0; i < puzzle.get_sequence().size(); ++i) {
		distance += std::max(std::abs((i/ puzzle.get_size() - goal[puzzle.get_sequence()[i]]/ puzzle.get_size())),
                             std::abs(i % puzzle.get_size() - goal[puzzle.get_sequence()[i]] % puzzle.get_size()));
    }
    return distance;
}

float myDistance(Puzzle const& puzzle, std::map<int, int> goal) {
    float distance = 0;
    for (int i = 0; i < puzzle.get_sequence().size(); ++i) {
        if (i != goal[puzzle.get_sequence()[i]])
            distance++;
    }
    return distance;
}
