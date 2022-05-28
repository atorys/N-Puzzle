//
// Created by Achiote Tory on 5/27/22.
//

#pragma once
#include "vector"

class Board {

    std::vector<int>    initial_state;
	std::vector<int>	goal_state;
    int                 size;

public:
    Board(int, std::vector<int>&);

	std::vector<int> const&	get_goal_state() const;

    void    print() const;
    void    print(std::vector<int>) const;
};

