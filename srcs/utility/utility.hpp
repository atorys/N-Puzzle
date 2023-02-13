//
// Created by Achiote Tory on 5/27/22.
//

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

std::vector<std::string>            split(std::string &str);
std::pair<int, std::vector<int>>    getPuzzle(char *filename);
std::vector<int>					snailSolution(int size);

int                                 count_inversions(std::vector<int> const& sequence);
std::map<int, int>					get_goal_map(std::vector<int> const& puzzle);