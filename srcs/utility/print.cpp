//
// Created by Achiote Tory on 5/27/22.
//
#include "utility.hpp"

const std::string set[3][4] = {
        { "┌", "─", "┬", "┐" },
        { "├", "─", "┼", "┤" },
        { "└", "─", "┴", "┘" }
};

void    print_string(int line, int width, int coeff) {
    for (int i = 0; i < width; ++i) {
        if (i == 0) {
            std::cout << set[line][0];
        } else if (i == width - 1) {
            std::cout << set[line][3] << "\n";
        } else if (i % coeff == 0) {
            std::cout << set[line][2];
        } else {
            std::cout << set[line][1];
        }
    }
}