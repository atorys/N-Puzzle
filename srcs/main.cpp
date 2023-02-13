//
// Created by atory on 02.06.22.
//


#include "./graphics/Visualizer.hpp"

int main(int ac, char **av) {

	Puzzle 		puzzle;
	Visualizer  n_puzzle;

	if (ac == 2) {

		std::pair<int, std::vector<int>> args;
		if ((args = getPuzzle(av[1])).second.empty()) {
			std::cerr << "Wrong file\n";
			exit(EXIT_FAILURE);
		}

		puzzle = Puzzle(args.first, args.second);
		puzzle.set_solvable(is_solvable(puzzle));
		n_puzzle.display(&puzzle);
	}
}