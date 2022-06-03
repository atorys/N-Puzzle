//
// Created by Achiote Tory on 5/27/22.
//

#pragma once
#include "vector"
#include "../utility/utility.hpp"

enum Move {
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NONE
};

class Puzzle {

	int						size;
	std::vector<int>        sequence;
    std::pair<int, int>     space;
	std::vector<Move>		moves;

  public:
	Puzzle();
    Puzzle(int, std::vector<int> const&);
    Puzzle(Puzzle const& other);
	Puzzle&	operator=(Puzzle const& other);

	const std::vector<int>&		get_sequence() const	{ return sequence; };
	int							get_size() const		{ return size; };
	unsigned long				get_cost() const		{ return moves.size(); };
	std::pair<int, int> const&	get_space() const		{ return space; };
	std::vector<Move>		    get_moves() const		{ return moves; };

	bool 	try_move(Move);
    void    print() const;
    void    print(const std::vector<int>&) const;
};

inline bool is_solvable(Puzzle *puzzle, Puzzle *solution) {

	int i_puzzle = count_inversions(puzzle->get_sequence());
	int i_goal = count_inversions(solution->get_sequence());

	if (puzzle->get_size() % 2) {
		return i_goal % 2 == i_puzzle % 2;
	}

	return i_goal % 2 == (i_puzzle + puzzle->get_space().first +
						  solution->get_space().first) % 2;
}
