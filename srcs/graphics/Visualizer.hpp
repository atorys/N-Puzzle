//
// Created by atory on 03.06.22.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "SearchAlgorithm.hpp"
#include "Heuristics.hpp"
#include "Graphics.hpp"

class Visualizer {

	SearchAlgorithm												*algorithm;
	Graphics													graphics;

	Puzzle*														puzzle;
	std::vector<AStar::HeuristicsFunc>							heuristics;
	std::map<std::string, SearchAlgorithm::Solution>			solutions;

	std::string													current_solution;

  public:
	Visualizer():	algorithm(new AStar()),
					graphics(),
					puzzle(nullptr),
					heuristics({&euclideanDistance, &chebDistance, &manhattanDistance}) {}

	~Visualizer() {
		delete algorithm;
	}

	void	display(Puzzle *p) {
		sf::Event	event;
		States		state = PAUSE;
		int 		steps = 0, selected_bar = 0;

		set_puzzle(p);
		while (graphics.get_window().isOpen()) {
			while (graphics.get_window().pollEvent(event)) {
				if (event.type == sf::Event::Closed
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					graphics.get_window().close();

				} else if (event.type == sf::Event::KeyPressed && puzzle->is_solvable()) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && state == PAUSE) {
						graphics.select(&selected_bar);

					} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						update(&state, &steps, selected_bar);
					}
				}
			}
			graphics.display(state, steps, solutions[current_solution]);
		}
	}

  private:

	void	set_puzzle(Puzzle *p) {
		this->puzzle = p;
		graphics.set_puzzle(puzzle);
	}

	void	update(States *state, int *steps, int& bar) {

		std::string prev_solution = current_solution;
		current_solution = graphics.get_bar(bar);

		if (*state == PAUSE
			&& !solutions.count(current_solution)) {

			((AStar *) algorithm)->select_heuristics(heuristics[bar]);
			solutions[current_solution] = algorithm->solve(*puzzle);
			*steps = std::get<2>(solutions[current_solution]).size();
			graphics.reset(solutions[current_solution]);

		} else if (!(*steps) || prev_solution != current_solution) {
			*steps = std::get<2>(solutions[current_solution]).size();
			graphics.reset(solutions[current_solution]);

		}
		*state = (*state == PAUSE) ? GO : PAUSE;
	}
};
