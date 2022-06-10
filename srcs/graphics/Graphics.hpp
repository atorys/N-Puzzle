//
// Created by Achiote Tory on 6/10/22.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "../algorithm/SearchAlgorithm.hpp"
#include "../algorithm/Heuristics.hpp"

#include "unordered_map"

const int WIDTH = 550;
const int HEIGHT = 750;
const int TILE_SIZE = 16;
const int PADDING = 4;
const char* FONT = "/Users/atory/CLionProjects/N-Puzzle/srcs/resources/graphics/Awkward/AwkwardExt.ttf";
const char* BOXES =  "/Users/atory/CLionProjects/N-Puzzle/srcs/resources/graphics/puzzle_tileset.png";

float SCALE = 4;

enum States {
	PAUSE,
	GO
};

class Visualizer {

	sf::RenderWindow	window;

	sf::Font			font;
	sf::Texture			texture;

	std::vector<sf::Sprite>	sprites;
	std::vector<sf::Text>	numbers;
	std::vector<sf::Text>	texts;
	std::pair<int, int>		empty_sprite;
	int 					size;

	SearchAlgorithm												*algorithm;

	Puzzle														puzzle;
	std::unordered_map<std::string, SearchAlgorithm *>			algorithms;
	std::unordered_map<std::string, AStar::HeuristicsFunc>		heuristics;
	std::unordered_map<std::string, SearchAlgorithm::Solution>	solutions;

	std::vector<std::vector<std::string>>	bars;
	int bar;
	std::vector<int> select;

	std::string	current_solution;

  public:
	Visualizer(Puzzle const& p):	window(sf::VideoMode({WIDTH, HEIGHT}), "N-Puzzle"),
									puzzle(p)
	{
		window.setFramerateLimit(30);
		font.loadFromFile(FONT);
		texture.loadFromFile(BOXES);

		bar = 0;
		select = {0, 1};

		bars.emplace_back();
		bars.emplace_back();

		bars[0] = {"A*", "DFS", "BFS"};
		bars[1] = {"NO", "EUCLIDEAN", "CHEBYSHEV", "MANHATTAN"};

		algorithms["A*"] = new AStar();
		algorithms["DFS"] = new DepthFirstSearch();
		algorithms["BFS"] = new DepthFirstSearch();

		heuristics["NO"] = nullptr;
		heuristics["EUCLIDEAN"] = &euclideanDistance;
		heuristics["CHEBYSHEV"] = &chebDistance;
		heuristics["MANHATTAN"] = &chebDistance;

		current_solution = "?";
		solutions[current_solution] = SearchAlgorithm::Solution{false, 0, 0, 0};

		bars[bar][select[bar]] = ("> " + bars[bar][select[bar]]);

		texts.clear();
		for (int i = 0; i < 7; ++i) {
			texts.emplace_back("", font, 40 + 15 * (i < 3) + 20 * (i == 3));
			texts[i].setFillColor(sf::Color::White);
//			texts[i].setStyle(sf::Text::Bold);
		}
		set_puzzle(&puzzle);
	}

	~Visualizer() {
		for (auto algo : algorithms) {
			if (algo.second) {
				delete algo.second;
			}
			algo.second = nullptr;
		}
	}

	void    down() {
		bars[bar][select[bar]] = bars[bar][select[bar]].substr(2);
		texts[bar].setFillColor(sf::Color::White);
		++bar;
		if (bar == bars.size())
			bar = 0;
		bars[bar][select[bar]] = ("> " + bars[bar][select[bar]]);
		texts[bar].setFillColor(sf::Color::Green);
	}

	void    up() {
		bars[bar][select[bar]] = bars[bar][select[bar]].substr(2);
		texts[bar].setFillColor(sf::Color::White);
		--bar;
		if (bar < 0)
			bar = bars.size() - 1;
		bars[bar][select[bar]] = ("> " + bars[bar][select[bar]]);
		texts[bar].setFillColor(sf::Color::Green);
	}

	void selectt(States *state, int* steps) {
		bars[bar][select[bar]] = bars[bar][select[bar]].substr(2);
		++select[bar];
		if (select[bar] == bars[bar].size())
			select[bar] = 0 + (!select[0]);
		if (select[0]) {
			select[1] = 0;
		} else if (!select[1])
			select[1] = 1;
//		if (bar == 2) {
//			select[bar] = 0;
//			if (*state == GO) {
//				*state = PAUSE;
//				bars[2][0] = "OK";
//			} else {
//				std::string prev_solution = current_solution;
//				current_solution = bars[0][select[0]] + bars[1][select[1]];
//				if (!solutions.count(current_solution)) {
//					algorithm = algorithms[bars[0][select[0]]];
//					if (bars[0][select[0]] == bars[0][0]) {
//						((AStar *) algorithm)->select_heuristics(heuristics[bars[1][select[1]]]);
//					}
//					solutions[current_solution] = algorithm->solve(puzzle);
//					*steps = std::get<3>(solutions[current_solution]).size();
//					set_puzzle(&puzzle);
//				} else if (!*steps || prev_solution != current_solution) {
//					*steps = std::get<3>(solutions[current_solution]).size();
//					set_puzzle(&puzzle);
//				}
//				*state = GO;
//				bars[2][0] = "PAUSE";
//			}
//		}
		bars[bar][select[bar]] = ("> " + bars[bar][select[bar]]);
	}

	void on() {
		sf::Event	event;
		States		state = PAUSE;
		int 		steps = 0;

		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					window.close();
				}
				if (event.type == sf::Event::KeyPressed) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && state == PAUSE)
						up();
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && state == PAUSE)
						down();
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && state == PAUSE) {
						selectt(&state, &steps);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						if (state == GO) {
							state = PAUSE;
						} else {
							std::string prev_solution = current_solution;
							current_solution = bars[0][select[0]] + bars[1][select[1]];
							if (!solutions.count(current_solution)) {
								algorithm = algorithms[bars[0][select[0]]];
								if (bars[0][select[0]] == bars[0][0]) {
									((AStar *) algorithm)->select_heuristics(heuristics[bars[1][select[1]]]);
								}
								solutions[current_solution] = algorithm->solve(puzzle);
								steps = std::get<3>(solutions[current_solution]).size();
								set_puzzle(&puzzle);
							} else if (!steps || prev_solution != current_solution) {
								steps = std::get<3>(solutions[current_solution]).size();
								set_puzzle(&puzzle);
							}
							state = GO;
						}
					}
				}
			}
			display(state, steps);
		}
	}

	void display(States state, int& steps) {
		if (state == GO) {
			if (steps > 0)
				move(std::get<3>(solutions[current_solution])[std::get<3>(solutions[current_solution]).size() - steps], steps);
			else
				draw_puzzle(0);
		}
		else
			draw_puzzle(steps > 0 ? steps : std::get<3>(solutions[current_solution]).size());
		window.display();
		window.clear(sf::Color::Black);
	};

  public:

	void	set_puzzle(Puzzle *p) {

		size = p->get_size();

		int percentage = size * (SCALE * TILE_SIZE) / (WIDTH / 100);
		while (percentage <= 60 || percentage >= 70) {
			SCALE *= percentage < 60 ? 1.25 : 0.75;
			percentage = size * (SCALE * TILE_SIZE) / (WIDTH / 100);
		}

		set_sprites(p);
		set_numbers(p);

		auto [solvable, time, count, move] = solutions[current_solution];

		texts[3].setString(std::string("SOLVABLE = ") + (solvable ? "YES" : "?"));
		texts[4].setString(std::string("TIME = ") + (time ? std::to_string(time) : "?") + " S");
		texts[5].setString(std::string("STEPS = " + (move.size() ? std::to_string(move.size()) : "?")));
		texts[6].setString("STATES = " + (count ? std::to_string(count) : "?"));

	}
	float 	get_x(float padding) { return (WIDTH  - TILE_SIZE*SCALE*size)/2.f + padding; }

	float 	get_y(float padding) { return (HEIGHT - TILE_SIZE*SCALE*size)/4.5f + padding; }

	template<class T>
	void 	set_positions(std::vector<T>& instance, float k) {
		float	padding_x = 0;
		float	padding_y = 0;
		for (int i = 0; i < instance.size(); ++i) {

			if (i && i % size == 0) {
				padding_y += SCALE*TILE_SIZE + PADDING;
				padding_x = 0;
			}
			instance[i].setPosition(get_x(padding_x) + k,
									get_y(padding_y));
			padding_x += SCALE*TILE_SIZE + PADDING;
		}
	}
	void	set_sprites(Puzzle *puzzle) {

		sprites.clear();
		for (int i = 0; i < puzzle->get_size() * puzzle->get_size(); ++i) {
			sprites.emplace_back(sf::Sprite{texture,
											sf::IntRect(5 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE)});
			sprites[i].setScale(SCALE, SCALE);
		}
		empty_sprite = puzzle->get_space();
		sprites[empty_sprite.first * puzzle->get_size() + empty_sprite.second].setScale(0, 0);
		set_positions(sprites, 0);
	}

	void	set_numbers(Puzzle *puzzle) {
		std::string 			number;

		numbers.clear();
		for (int i = 0; i < puzzle->get_size() * puzzle->get_size(); ++i) {
			if (!puzzle->get_sequence()[i]) {
				number = "";
			} else {
				number = std::to_string(puzzle->get_sequence()[i]);
			}
			numbers.emplace_back(sf::Text{number, font, TILE_SIZE * 3});
			numbers[i].setFillColor(sf::Color::Black);
		}
		set_positions(numbers, TILE_SIZE*SCALE / 4.5);
	}

	void 	draw_puzzle(int step) {
		for (int i = 0; i < sprites.size(); ++i) {
			window.draw(sprites[i]);
			window.draw(numbers[i]);
		}

		float padding_y = get_y(HEIGHT / 2.5) + 40;
		float padding_x = get_x(0);

		texts[0].setString(bars[0][select[0]]);
		texts[1].setString(bars[1][select[1]]);
		texts[3].setString("# " + std::to_string(step));
		for (int i = 0; i < texts.size(); ++i) {
			texts[i].setPosition(padding_x, padding_y);
			padding_y += 30 + (i == 2) * 20 + (i == 3) * 20;
			window.draw(texts[i]);
		}
	}

	void move(Move dir, int& step) {
		int dx = 0;
		int dy = 0;
		float speed = TILE_SIZE;

		if (dir == Move::UP) { dx = 0; dy = -1;};
		if (dir == Move::DOWN) { dx = 0; dy = 1;};
		if (dir == Move::RIGHT) { dx = 1; dy = 0; };
		if (dir == Move::LEFT) { dx = -1; dy = 0; };

		sf::Vector2f pos_1 = sprites[empty_sprite.first * size + empty_sprite.second].getPosition();
		sf::Vector2f pos_2 = numbers[empty_sprite.first * size + empty_sprite.second].getPosition();
		sf::Vector2f pos_3 = sprites[(empty_sprite.first + dy) * size + empty_sprite.second + dx].getPosition();
		sf::Vector2f pos_4 = numbers[(empty_sprite.first + dy) * size + empty_sprite.second + dx].getPosition();

		sprites[empty_sprite.first * size + empty_sprite.second].setPosition(pos_3);
		numbers[empty_sprite.first * size + empty_sprite.second].setPosition(pos_4);

		--step;
		for (float i = 0; i < TILE_SIZE*SCALE;) {
			sprites[(empty_sprite.first + dy) * size + empty_sprite.second + dx].move(-1 * dx * speed, -1 * dy * speed);
			numbers[(empty_sprite.first + dy) * size + empty_sprite.second + dx].move(-1 * dx * speed, -1 * dy * speed);

			window.clear(sf::Color::Black);
			draw_puzzle(step);
			window.display();
			i += speed;
		}

		sprites[(empty_sprite.first + dy) * size + empty_sprite.second + dx].setPosition(pos_1);
		numbers[(empty_sprite.first + dy) * size + empty_sprite.second + dx].setPosition(pos_2);

		std::swap(sprites[(empty_sprite.first + dy) * size + empty_sprite.second + dx], sprites[empty_sprite.first * size + empty_sprite.second]);
		std::swap(numbers[(empty_sprite.first + dy) * size + empty_sprite.second + dx], numbers[empty_sprite.first * size + empty_sprite.second]);

		empty_sprite.first += dy;
		empty_sprite.second += dx;

		window.clear(sf::Color::Black);
		draw_puzzle(step);
		window.display();
	}

};
