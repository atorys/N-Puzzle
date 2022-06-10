//
// Created by Achiote Tory on 6/8/22.
//

#pragma once
#include "Assets.hpp"

enum States {
	PAUSE,
	GO
};

class Menu {

	sf::RenderWindow*		window;

	std::vector<sf::Text>					menu;
	std::vector<std::vector<std::string>>	bars;
	std::vector<int>						state;
	int 									bar;

  public:
	Menu(sf::RenderWindow* w): window(w), bar(0), state({1, 1, 1}) {

		bars.emplace_back();
		bars.emplace_back();
		bars.emplace_back();

		bars[0] = {"ALGORITHM  ", "A*", "DFS"};
		bars[1] = {"HEURISTICS  ", "NO", "EUCLIDEAN", "CHEBYSHEV", "MANHATTAN"};
		bars[2] = {"SOLVE", "", ""};

		menu.emplace_back(bars[0][0], Assets::getInstance()->get_font(), TEXT_SIZE);
		menu.emplace_back(bars[1][0], Assets::getInstance()->get_font(), TEXT_SIZE);
		menu.emplace_back(bars[2][0], Assets::getInstance()->get_font(), TEXT_SIZE);

		for (auto & text : menu) {
			text.setFillColor(sf::Color::White);
			text.setStyle(sf::Text::Bold);
		}

		menu[bar].setString("> " + menu[bar].getString());
		menu[bar].setFillColor(sf::Color::Green);
	}

	void down() {
		menu[bar].setFillColor(sf::Color::White);
		menu[bar].setString(menu[bar].getString().substring(2));
		++bar;
		if (bar == menu.size())
			bar = 0;

		menu[bar].setString("> " + menu[bar].getString());
		menu[bar].setFillColor(sf::Color::Green);
	}

	void up() {
		menu[bar].setFillColor(sf::Color::White);
		menu[bar].setString(menu[bar].getString().substring(2));
		--bar;
		if (bar == -1)
			bar = menu.size() - 1;

		menu[bar].setString("> " + menu[bar].getString());
		menu[bar].setFillColor(sf::Color::Green);
	}

	void swap(States* current) {
		if (bar == 2) {
			*current = (*current == PAUSE) ? GO : PAUSE;
		}
		state[bar]++;
		if (state[bar] == bars[bar].size()) {
			state[bar] = 1 + (bar == 1);
		}
		if (bar == 1 && state[0] == 2)
			state[bar] = 1;

		menu[bar].setString(bars[bar][0] + bars[bar][state[bar]]);
		menu[bar].setString("> " + menu[bar].getString());
		menu[bar].setFillColor(sf::Color::Green);
	}

	void display() {
		float padding_y = 20;
		float padding_x = WIDTH / 8;

		for (int i = 0; i < menu.size(); ++i) {
			menu[i].setPosition(padding_x, padding_y);
			window->draw(menu[i]);
			padding_y += 30;
		}
	}
};

class Solver {
	sf::RenderWindow*		window;

	std::vector<sf::Sprite>	sprites;
	std::vector<sf::Text>	numbers;
	std::vector<sf::Text>	texts;
	int 					space_x;
	int 					space_y;
	int 					size;

  public:
	Solver(sf::RenderWindow* w, Puzzle* puzzle): window(w) {
		set_puzzle(puzzle);
	}

	void	set_puzzle(Puzzle *puzzle) {

		size = puzzle->get_size();
		space_x = puzzle->get_space().first;
		space_y = puzzle->get_space().second;

		int percentage = size * (SCALE * TILE_SIZE) / (WIDTH / 100);
		while (percentage <= 50 || percentage >= 60) {
			SCALE *= percentage < 50 ? 1.25 : 0.75;
			percentage = size * (SCALE * TILE_SIZE) / (WIDTH / 100);
		}

		numbers.clear();
		sprites.clear();
		for (int i = 0; i < size * size; ++i) {
			numbers.emplace_back(sf::Text{std::to_string(puzzle->get_sequence()[i]), Assets::getInstance()->get_font(), TEXT_SIZE});
			sprites.emplace_back(sf::Sprite{Assets::getInstance()->get_texture(),
											sf::IntRect(5 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE)});
			numbers[i].setFillColor(sf::Color::Black);
			sprites[i].setScale(SCALE, SCALE);
		}
		sprites[space_x * size + space_y].setScale(0, 0);
		numbers[space_x * size + space_y].setScale(0, 0);

		set_positions(sprites, 0);
		set_positions(numbers, TILE_SIZE*SCALE / 4.5);

	}
	float 	get_x(float padding) { return (WIDTH  - TILE_SIZE*SCALE*size)/2.f + padding; }
//	float 	get_x(float padding) { return (WIDTH)/1.8f + padding; }

	float 	get_y(float padding) { return (HEIGHT - TILE_SIZE*SCALE*size)/2.5f + padding; }

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

	void move(Move dir, int& step) {
		int dx = 0;
		int dy = 0;
		float speed = TILE_SIZE;

		if (dir == Move::UP) { dx = 0; dy = -1;};
		if (dir == Move::DOWN) { dx = 0; dy = 1;};
		if (dir == Move::RIGHT) { dx = 1; dy = 0; };
		if (dir == Move::LEFT) { dx = -1; dy = 0; };

		sf::Vector2f pos_1 = sprites[space_x * size + space_y].getPosition();
		sf::Vector2f pos_2 = numbers[space_x * size + space_y].getPosition();
		sf::Vector2f pos_3 = sprites[(space_x + dy) * size + space_y + dx].getPosition();
		sf::Vector2f pos_4 = numbers[(space_x + dy) * size + space_y + dx].getPosition();

		sprites[space_x * size + space_y].setPosition(pos_3);
		numbers[space_x * size + space_y].setPosition(pos_4);

		--step;
		for (float i = 0; i < TILE_SIZE*SCALE;) {
			sprites[(space_x + dy) * size + space_y + dx].move(-1 * dx * speed, -1 * dy * speed);
			numbers[(space_x + dy) * size + space_y + dx].move(-1 * dx * speed, -1 * dy * speed);

			window->clear(sf::Color::Black);
			display(step);
			window->display();
			i += speed;
		}

		sprites[(space_x + dy) * size + space_y + dx].setPosition(pos_1);
		numbers[(space_x + dy) * size + space_y + dx].setPosition(pos_2);

		std::swap(sprites[(space_x + dy) * size + space_y + dx], sprites[space_x * size + space_y]);
		std::swap(numbers[(space_x + dy) * size + space_y + dx], numbers[space_x * size + space_y]);

		space_x += dy;
		space_y += dx;

		window->clear(sf::Color::Black);
		display(step);
		window->display();
	}

	void 	display(int step) {
		for (int i = 0; i < sprites.size(); ++i) {
			window->draw(sprites[i]);
			window->draw(numbers[i]);
		}
	}

};

class Visualizer {

	sf::RenderWindow	window;
	Menu				menu;
	Solver				solver;
	States				state;
	SearchAlgorithm		*algorithm;

  public:
	Visualizer(std::string const& title,
			   unsigned int width,
			   unsigned int height,
			   Puzzle* puzzle):
								window(sf::VideoMode({width, height}), title),
								menu(&window),
								solver(&window, puzzle) {

		window.setFramerateLimit(60);
		window.setMouseCursorVisible(false);
		state = PAUSE;
	}

	void on() {
		sf::Event	event;

		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					window.close();
				}
				if (event.type == sf::Event::KeyPressed) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						menu.up();
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						menu.down();
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
						menu.swap(&state);
				}
			}
			display();
		}
	}

	void display() {
		menu.display();
		solver.display(0);
		if (state == GO) {

		}
		window.display();
		window.clear(sf::Color::Black);
	};
};