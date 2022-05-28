//
// Created by Achiote Tory on 5/27/22.
//

#include "Puzzle.hpp"
#include "../utility/utility.hpp"
#include "iostream"

Puzzle::Puzzle(int count, std::vector<int>& state): size(count),
													current_state(state),
													goal_state(snailSolution(size)) {}

void Puzzle::print() const {
	Puzzle::print(this->current_state);
}

void Puzzle::print(std::vector<int> state) const {
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

const std::vector<int> &Puzzle::getCurrentState() const {
	return current_state;
}


const std::vector<int> &Puzzle::getGoalState() const {
	return goal_state;
}

int Puzzle::getSize() const {
	return size;
}

