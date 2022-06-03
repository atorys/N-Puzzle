//
// Created by atory on 02.06.22.
//

#include<stdio.h>
#include<math.h>
#include "../algorithm/SearchAlgorithm.hpp"
#include "../algorithm/Heuristics.hpp"

#include "Game.hpp"


int main(int ac, char **av) {

	Game n_puzzle;

	Puzzle* puzzle;

	std::pair<int, std::vector<int>> args;
	if ((args = getPuzzle(av[1])).second.empty()) {
		std::cerr << "Wrong file\n";
		exit(EXIT_FAILURE);
	}

	puzzle = new Puzzle(args.first, args.second);

	n_puzzle.set_puzzle(puzzle);
	n_puzzle.start();



//	s_arrow.setTexture(icons);
//	s_arrow.setTextureRect(sf::IntRect(1*16, 4*16, 16, 16));
//
//
//	s_arrow.setPosition(100, 100);
//	t_start.setPosition(120, 100);
//	s_dice.setPosition(20, 20);



}