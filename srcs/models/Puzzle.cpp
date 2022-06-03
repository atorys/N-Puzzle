//
// Created by Achiote Tory on 5/27/22.
//

#include "Puzzle.hpp"

Puzzle::Puzzle(): size(0) {}

Puzzle::Puzzle(int count, std::vector<int> const& sequence):	size(count),
																sequence(sequence) {
    for (int i = 0; i < sequence.size(); ++i) {
        if (sequence[i] == 0) {
            space.first = i / size;
            space.second = i % size;
        }
    }
}

Puzzle::Puzzle(Puzzle const& puzzle):	size(puzzle.size),
										sequence(puzzle.sequence),
										space(puzzle.space),
										moves(puzzle.moves) {
}

Puzzle& Puzzle::operator=(const Puzzle &other) {
	if (this == &other) {
		return *this;
	}
	size = other.size;
	space = other.space;
	sequence = other.sequence;
	moves = other.moves;
	return *this;
}

void Puzzle::print() const {
	Puzzle::print(this->sequence);
}

void Puzzle::print(const std::vector<int>& state) const {
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

bool	Puzzle::try_move(Move dir) {

	int start_index = space.first * size + space.second;
	int next_index;

	if (dir == Move::UP && this->space.first - 1 != -1) {
		--space.first;
	} else if (dir == Move::DOWN && space.first + 1 != size) {
		++space.first;
	} else if (dir == Move::RIGHT && space.second + 1 != size) {
		++space.second;
	} else if (dir == Move::LEFT && space.second - 1 != -1) {
		--space.second;
	}

	next_index = space.first * size + space.second;
	if (start_index == next_index) {
		return false;
	}

	std::swap(this->sequence[start_index], this->sequence[next_index]);
	moves.push_back(dir);
	return true;
}


