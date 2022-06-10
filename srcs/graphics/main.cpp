//
// Created by atory on 02.06.22.
//

#include "../algorithm/SearchAlgorithm.hpp"
#include "../algorithm/Heuristics.hpp"

#include "Graphics.hpp"


int main(int ac, char **av) {


	Puzzle* puzzle;

	std::pair<int, std::vector<int>> args;
	if ((args = getPuzzle(av[1])).second.empty()) {
		std::cerr << "Wrong file\n";
		exit(EXIT_FAILURE);
	}

	puzzle = new Puzzle(args.first, args.second);
	Visualizer  n_puzzle(*puzzle);
	n_puzzle.on();
}