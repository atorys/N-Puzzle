//
// Created by Achiote Tory on 5/27/22.
//

#include "Puzzle.hpp"

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
	} else {
		size = other.size;
		space = other.space;
		sequence = other.sequence;
		moves = other.moves;
		return *this;
	}
}

void Puzzle::print() const {
	Puzzle::print(this->sequence);
}

const std::vector<int> &Puzzle::get_sequence() const {
    return sequence;
}

int Puzzle::getSize() const {
    return size;
}
int Puzzle::get_cost() const {
    return moves.size();
}

void Puzzle::print(std::vector<int> sequence) const {
	int coeff = 5;
	int width = size * coeff++ + (size - 1) + 2;
	print_string(0, width, coeff);
	for (int i = 0; i < size; ++i) {
		if (i) {
			print_string(1, width, coeff);
		}
		for (int j = 0; j < size; ++j) {
			std::cout << "║ "; std::cout.width(2);
			std::cout << (sequence[size * i + j] == 0 ? " " : std::to_string(sequence[size * i + j]))  << "  ";
		}
		std::cout << "║\n";
	}
	print_string(2, width, coeff);
}

bool	Puzzle::try_move(Move dir) {

	int first = space.first * size + space.second;
	int second;
	if (dir == up && this->space.first - 1 != -1) {
		space.first--;
	} else if (dir == down && space.first + 1 != size) {
		space.first++;
	} else if (dir == right && space.second + 1 != size) {
		space.second++;
	} else if (dir == left && space.second - 1 != -1) {
		space.second--;
	}
	second = space.first * size + space.second;
	if (first == second) {
		return false;
	} else {
		std::swap(this->sequence[first], this->sequence[second]);
		moves.push_back(dir);
		return true;
	}
}

std::vector<Move> Puzzle::get_moves() const {
	return this->moves;
}

std::pair<int, int> const& Puzzle::get_space() const {
	return this->space;
}


