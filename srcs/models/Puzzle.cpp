//
// Created by Achiote Tory on 5/27/22.
//

#include "Puzzle.hpp"

Puzzle::Puzzle(int count, std::vector<int> const& state): size(count),
													state(state),
                                                    last_move(no),
                                                    cost(0),
                                                    heuristic(0),
                                                    parent(nullptr) {
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] == 0) {
            zero_node.first = i / size;
            zero_node.second = i % size;
        }
    }
}


Puzzle::Puzzle(Puzzle const& puzzle, int move):  size(puzzle.getSize()),
                                                state(puzzle.state),
                                                zero_node(puzzle.zero_node),
                                                last_move(move),
                                                cost(puzzle.cost + 1),
                                                parent((Puzzle *)&puzzle) {
    state = puzzle.state;
    int first = this->zero_node.first * this->size + this->zero_node.second;
    int second;
    if (move == up && this->zero_node.first - 1 != -1) {
        this->zero_node.first--;
    } else if (move == down &&  this->zero_node.first + 1 !=  this->size) {
        this->zero_node.first++;
    } else if (move == right &&  this->zero_node.second + 1 != puzzle.size) {
        this->zero_node.second++;
    } else if (move == left && this->zero_node.second - 1 != -1) {
        this->zero_node.second--;
    }
    second = this->zero_node.first * this->size + this->zero_node.second;

    int tmp = puzzle.state[first];
    this->state[first] = this->state[second];
    this->state[second] = tmp;
}

void Puzzle::print() const {
	Puzzle::print(this->state);
}

void Puzzle::set_heuristics(int h) {
    this->heuristic = h;
}

int Puzzle::get_heuristics() const {
    return this->heuristic;
}

const std::vector<int> &Puzzle::get_state() const {
    return state;
}

int Puzzle::getSize() const {
    return size;
}
int Puzzle::get_cost() const {
    return cost;
}

Puzzle *Puzzle::get_parent() const {
    return this->parent;
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

