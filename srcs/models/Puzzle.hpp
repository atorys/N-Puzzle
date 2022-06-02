//
// Created by Achiote Tory on 5/27/22.
//

#pragma once
#include "vector"
#include "../utility/utility.hpp"

enum Move {
	up,
	right,
	down,
	left,
	none
};

class Puzzle {

	int                     size;
	std::vector<int>        sequence;
    std::pair<int, int>     space;
	std::vector<Move>		moves;

public:
	Puzzle(){};
    Puzzle(int, std::vector<int> const&);
    Puzzle(Puzzle const& other);
	Puzzle&	operator=(Puzzle const& other);

	const std::vector<int>&		get_sequence() const;
	int							getSize() const;
	int							get_cost() const;
	std::pair<int, int> const&	get_space() const;
	std::vector<Move>		    get_moves() const;

	bool 	try_move(Move);
    void    print() const;
    void    print(std::vector<int>) const;
};
