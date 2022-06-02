//
// Created by atory on 28.05.22.
//
#include "utility.hpp"

std::vector<int>	snailSolution(int size) {
	std::vector<int>		solution;
	std::pair<int, int>		xy = {0, 0};
	int x_sign = 0, y_sign = 1, x_steps = 0, y_steps = 0;

	solution.resize(size * size);
	for (int digit = 1, limit = size; digit != size * size; ++digit) {

		solution[xy.first * size + xy.second] = digit;

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
	return solution;
}

std::map<int, int>	get_goal_map(std::vector<int> const& puzzle) {
	std::map<int, int>  goal_state;

	for (int i = 0; i < puzzle.size(); ++i) {
		goal_state[puzzle[i]] = i;
	}

	return goal_state;
}

int     count_inversions(std::vector<int> const& sequence) {
    int count = 0;

    for (int i = 0; i < sequence.size(); ++i) {
        for (int j = i + 1; j < sequence.size(); ++j) {
            if (sequence[i] && sequence[j] && sequence[i] > sequence[j])
                count++;
        }
    }
    return count;
}