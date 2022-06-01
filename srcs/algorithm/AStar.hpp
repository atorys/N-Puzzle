//
// Created by Achiote Tory on 5/31/22.
//

#pragma once
#include <queue>
#include <set>
#include "map"
#include "../models/Puzzle.hpp"

typedef int ( *HeuristicsFunc )( Puzzle*, std::map<int, int> );

class AStar {
    HeuristicsFunc      heuristics;

    std::priority_queue< Puzzle, std::vector<Puzzle>, std::greater<Puzzle> >  open_set;
    std::map< std::vector<int>, int >                                   closed_set;

public:

    explicit AStar(HeuristicsFunc);

    void    solve(Puzzle*);
    void    set_strategy(HeuristicsFunc);

};

