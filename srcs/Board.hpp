//
// Created by Achiote Tory on 5/27/22.
//

#pragma once
#include "vector"

class Board {

    std::vector<int>    initial_config;
    int                 tiles_count;

public:
    Board(int, std::vector<int>&);

    void    print() const;
};

