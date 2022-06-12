//
// Created by Achiote Tory on 5/27/22.
//

#include "Puzzle.hpp"

Puzzle::Puzzle(): m_size(0) {}

Puzzle::Puzzle(int count, std::vector<int> const& sequence):	m_size(count),
																sequence(sequence) {
    for (int i = 0; i < sequence.size(); ++i) {
        if (sequence[i] == 0) {
            space.first = i / m_size;
            space.second = i % m_size;
        }
    }
}


Puzzle::Puzzle(Puzzle const& puzzle):	m_size(puzzle.m_size),
										sequence(puzzle.sequence),
										space(puzzle.space),
										moves(puzzle.moves),
										solvable(puzzle.solvable) {}

Puzzle& Puzzle::operator=(const Puzzle &other) {
	if (this == &other) {
		return *this;
	}
	m_size = other.m_size;
	space = other.space;
	sequence = other.sequence;
	moves = other.moves;
	solvable = other.solvable;
	return *this;
}

bool	Puzzle::try_move(Move dir) {

	int start_index = space.first * m_size + space.second;
	int next_index;

	if (dir == Move::UP && this->space.first - 1 != -1) {
		--space.first;
	} else if (dir == Move::DOWN && space.first + 1 != m_size) {
		++space.first;
	} else if (dir == Move::RIGHT && space.second + 1 != m_size) {
		++space.second;
	} else if (dir == Move::LEFT && space.second - 1 != -1) {
		--space.second;
	}

	next_index = space.first * m_size + space.second;
	if (start_index == next_index) {
		return false;
	}

	std::swap(this->sequence[start_index], this->sequence[next_index]);
	moves.push_back(dir);
	return true;
}


