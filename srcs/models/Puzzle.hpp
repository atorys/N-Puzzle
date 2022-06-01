//
// Created by Achiote Tory on 5/27/22.
//

#pragma once
#include "vector"
#include "../utility/utility.hpp"

enum moves {
    no = 0,
    up,
    right,
    down,
    left
};

class Puzzle {

	int                     size;
	std::vector<int>        state;
    std::pair<int, int>     zero_node;
    int                     last_move;

    int                     cost;
    int                     heuristic;

    Puzzle*                 parent;

public:
    Puzzle(int, std::vector<int> const&);
    Puzzle(Puzzle const& other, int);

	const std::vector<int>&		get_state() const;
	int							getSize() const;
	int							get_cost() const;
    int                         get_heuristics() const;
    Puzzle*					    get_parent() const;
    void                        set_heuristics(int);

    void    print() const;
    void    print(std::vector<int>) const;

    friend bool operator>(Puzzle const& a, Puzzle const& b) {
        return (a.cost + a.heuristic) > (b.cost + b.heuristic);
    }

    friend bool operator<(Puzzle const& a, Puzzle const& b) {
        return !(a > b);
    }

};


