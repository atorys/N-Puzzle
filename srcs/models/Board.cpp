//
// Created by Achiote Tory on 5/27/22.
//
#include "Board.hpp"

#include "../utility/utility.hpp"
#include "iostream"

Board::Board(int count, std::vector<int>& in_board): initial_state(in_board), size(count) {
	goal_state.resize(size * size);
	std::pair<int, int> xy = {0, 0};
	int x_sign = 0, y_sign = 1, x_steps = 0, y_steps = 0;

	for (int digit = 1, limit = size; digit != size * size; ++digit) {

		goal_state[xy.first * size + xy.second] = digit;

		x_steps += x_sign != 0;
		y_steps += y_sign != 0;

		if (limit == x_steps) {
			y_sign = x_sign * -1;
			x_sign = x_steps = 0;
		}
		if (limit == y_steps) {
			x_sign = y_sign;
			y_sign = y_steps = 0;
			--limit;
		}

		xy.first += x_sign;
		xy.second += y_sign;
	}
}

void Board::print() const {
    Board::print(this->initial_state);
}
void Board::print(std::vector<int> state) const {
    int coeff = 5;
    int width = size * coeff++ + (size - 1) + 2;
    print_string(0, width, coeff);
    for (int i = 0; i < size; ++i) {
        if (i) {
            print_string(1, width, coeff);
        }
        for (int j = 0; j < size; ++j) {
            std::cout << "║ "; std::cout.width(2);
			std::cout << (state[size * i + j] == 0 ? " " : std::to_string(state[size * i + j]))  << "  ";
        }
        std::cout << "║\n";
    }
    print_string(2, width, coeff);
}

std::vector<int> const& Board::get_goal_state() const {
	return goal_state;
}
