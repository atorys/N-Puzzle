//
// Created by atory on 02.06.22.
//


#include "Visualizer.hpp"


int main(int ac, char **av) {

	Puzzle 		puzzle;
	Visualizer  n_puzzle;

	std::pair<int, std::vector<int>> args;
	if ((args = getPuzzle(av[1])).second.empty()) {
		std::cerr << "Wrong file\n";
		exit(EXIT_FAILURE);
	}

	puzzle = Puzzle(args.first, args.second);
	puzzle.set_solvable(is_solvable(puzzle,
									 Puzzle(puzzle.size(), snailSolution(puzzle.size()))));
	n_puzzle.display(puzzle);
}