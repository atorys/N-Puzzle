//
// Created by Achiote Tory on 5/27/22.
//

#pragma once
#include "vector"

class Puzzle {

	int                 size;
	std::vector<int>    current_state;
	std::vector<int>	goal_state;

public:
    Puzzle(int, std::vector<int>&);

	const std::vector<int>&		getCurrentState() const;
	const std::vector<int>&		getGoalState() const;
	int							getSize() const;

    void    print() const;
    void    print(std::vector<int>) const;
};

