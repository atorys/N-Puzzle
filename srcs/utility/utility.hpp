//
// Created by Achiote Tory on 5/27/22.
//

#pragma once

#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string>            split(std::string &str);
std::pair<int, std::vector<int>>    getPuzzle(char *filename);
std::vector<int>					snailSolution(int size);
void                                print_string(int line, int width, int coeff);