//
// Created by atory on 28.05.22.
//

#include "Game.hpp"


Game::Game(): puzzle(nullptr) {}

Game::~Game() {
	delete puzzle;
}

const Puzzle*	Game::getPuzzle() const {
	return puzzle;
}

void Game::setPuzzle(Puzzle *o) {
	this->puzzle = o;
}
