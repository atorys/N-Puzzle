//
// Created by Achiote Tory on 5/31/22.
//

#pragma once

#include <cmath>
#include "../utility/utility.hpp"
#include "map"

float	manhattanDistance(Puzzle const& puzzle, const std::map<int, int>& goal) {
	float	distance = 0;
	int 	node_x, node_y, goal_x, goal_y;

	for (int i = 0; i < puzzle.get_sequence().size(); ++i) {

		node_x = i / puzzle.size();
		node_y = i % puzzle.size();
		goal_x = goal.at(puzzle.get_sequence()[i]) / puzzle.size();
		goal_y = goal.at(puzzle.get_sequence()[i]) % puzzle.size();

		distance += std::abs(node_x - goal_x) + std::abs(node_y - goal_y);
	}
	return distance;
}

float	euclideanDistance(Puzzle const& puzzle, const std::map<int, int>& goal) {

    float	distance = 0;
	int 	node_x, node_y, goal_x, goal_y;

    for (int i = 0; i < puzzle.get_sequence().size(); ++i) {

		node_x = i / puzzle.size();
		node_y = i % puzzle.size();
		goal_x = goal.at(puzzle.get_sequence()[i]) / puzzle.size();
		goal_y = goal.at(puzzle.get_sequence()[i]) % puzzle.size();

		distance += (float)sqrt(((node_x - goal_x) * (node_x - goal_x)) + ((node_y - goal_y) * (node_y - goal_y)));
    }
    return distance;
}

float	chebDistance(Puzzle const& puzzle, const std::map<int, int>& goal) {

    float	distance = 0;
	int 	node_x, node_y, goal_x, goal_y;

    for (int i = 0; i < puzzle.get_sequence().size(); ++i) {

		node_x = i / puzzle.size();
		node_y = i % puzzle.size();
		goal_x = goal.at(puzzle.get_sequence()[i]) / puzzle.size();
		goal_y = goal.at(puzzle.get_sequence()[i]) % puzzle.size();

		distance += std::max(std::abs(node_x - goal_x),
							 std::abs(node_y - goal_y));
    }
    return distance;
}
