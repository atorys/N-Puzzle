//
// Created by atory on 02.06.22.
//

#include<stdio.h>
#include<math.h>
#include "../algorithm/SearchAlgorithm.hpp"
#include "../algorithm/Heuristics.hpp"

#include "Page.hpp"


int main(int ac, char **av) {

	Visualizer n_puzzle;

	Puzzle* puzzle;

	std::pair<int, std::vector<int>> args;
	if ((args = getPuzzle(av[1])).second.empty()) {
		std::cerr << "Wrong file\n";
		exit(EXIT_FAILURE);
	}

	puzzle = new Puzzle(args.first, args.second);
	n_puzzle.on();
}