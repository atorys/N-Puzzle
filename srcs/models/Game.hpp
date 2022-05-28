//
// Created by atory on 28.05.22.
//

#pragma once
#include "Puzzle.hpp"

class Game {
	Puzzle*	puzzle;

public:
	Game();
	~Game();

	const Puzzle*	getPuzzle() const;
	void			setPuzzle(Puzzle*);
};

