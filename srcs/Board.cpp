//
// Created by Achiote Tory on 5/27/22.
//
#include "Board.hpp"

#include "utility/utility.hpp"
#include "iostream"

Board::Board(int count, std::vector<int>& in_board): initial_config(in_board), tiles_count(count) {}

void Board::print() const {
    int coeff = 5;
    int width = tiles_count * coeff++ + (tiles_count - 1) + 2;
    print_string(0, width, coeff);
    for (int i = 0; i < tiles_count; ++i) {
        if (i) {
            print_string(1, width, coeff);
        }
        for (int j = 0; j < tiles_count; ++j) {
            std::cout << "│ "; std::cout.width(2); std::cout << initial_config[tiles_count * i + j] << "  ";
        }
        std::cout << "│\n";
    }
    print_string(2, width, coeff);
}
