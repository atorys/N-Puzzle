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

	Puzzle														puzzle;
	bool 														solvable;
	std::vector<AStar::HeuristicsFunc>							heuristics;
	std::unordered_map<std::string, SearchAlgorithm::Solution>	solutions;

	std::string													current_solution;

  public:
	Visualizer(Puzzle const& p,
			   bool is_solvable):	algorithm(new AStar()),
									puzzle(p),
									solvable(is_solvable),
									graphics(p, is_solvable),
									heuristics({&euclideanDistance, &chebDistance, &chebDistance}) {}

	~Visualizer() {
		delete algorithm;
	}

	void display() {
		sf::Event	event;
		States		state = PAUSE;
		int 		steps = 0, bar = 0;

		while (graphics.get_window().isOpen()) {
			while (graphics.get_window().pollEvent(event)) {
				if (event.type == sf::Event::Closed
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					graphics.get_window().close();

				} else if (event.type == sf::Event::KeyPressed && solvable) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && state == PAUSE) {
						bar = graphics.select();

					} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						update(&state, &steps, bar);
					}
				}
			}
			graphics.display(state, steps, solutions[current_solution]);
		}
	}

  private:
	void	update(States *state, int *steps, int bar) {

		std::string prev_solution = current_solution;
		current_solution = graphics.get_selected_bar();

		if (*state == PAUSE
			&& !solutions.count(current_solution)) {

			((AStar *) algorithm)->select_heuristics(heuristics[bar]);
			solutions[current_solution] = algorithm->solve(puzzle);
			*steps = std::get<2>(solutions[current_solution]).size();
			graphics.reset_puzzle(puzzle, solutions[current_solution]);

		} else if (!steps || prev_solution != current_solution) {
			*steps = std::get<2>(solutions[current_solution]).size();
			graphics.reset_puzzle(puzzle, solutions[current_solution]);

		}
		*state = (*state == PAUSE) ? GO : PAUSE;
	}
};
