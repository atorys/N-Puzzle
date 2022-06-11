//
// Created by Achiote Tory on 6/10/22.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "unordered_map"
#include "Assets.hpp"

class Graphics {

	sf::RenderWindow		window;

	std::vector<sf::Sprite>	sprites;
	std::vector<sf::Sprite>	icons;
	std::vector<sf::Text>	numbers;
	std::vector<sf::Text>	texts;

	bool 					solvable;
	int						space_x;
	int						space_y;
	int 					size;

	std::vector<sf::Color>		colors;
	std::vector<std::string>	bars;
	int							bar;

  public:
	Graphics(Puzzle const& puzzle,
			 bool is_solvable):

									window(sf::VideoMode({WIDTH, HEIGHT}), "N-Puzzle"),
									size(puzzle.get_size()),
									solvable(is_solvable),
									bar(0),
									bars({"    EUCLIDEAN >", " < CHEBYSHEV >", " < MANHATTAN   "}),
									colors({{203, 255, 77}, {147,112,219}, {255,215,0}}) {

		window.setFramerateLimit(60);
		window.setMouseCursorVisible(false);

		if (solvable) {
			for (int i = 0; i < 5; ++i) {
				texts.emplace_back("", Assets::getInstance()->get_font(), 45 + 10 * (i < 1) + 15 * (i == 1));
				texts[i].setFillColor(sf::Color::White);
			}
			texts[0].setString(bars[bar]);
			texts[0].setFillColor(colors[bar]);
		} else {
			texts.emplace_back("NOT SOLVABLE ;(", Assets::getInstance()->get_font(), 50);
			texts[0].setFillColor(sf::Color::Red);
		}

		int percentage;
		while ((percentage = size * (SCALE * TILE_SIZE) / (WIDTH / 100)) <= 60 || percentage >= 70) {
			SCALE *= percentage < 60 ? 1.25 : 0.75;
		}

		set_puzzle(puzzle, SearchAlgorithm::Solution{0,0,0});
		icons.emplace_back(Assets::getInstance()->get_icons(), sf::IntRect(1 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		icons.emplace_back(Assets::getInstance()->get_icons(), sf::IntRect(0, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE));

		for (auto &icon : icons) {
			icon.setScale(1.8, 1.8);
			icon.setPosition(get_x(0), get_y(HEIGHT / 2.5) + 75);
		}
	}

	sf::RenderWindow&	get_window() { return window; }
	std::string const&	get_selected_bar() { return bars[bar]; }

	void	display(States state, int& steps, SearchAlgorithm::Solution const& solution) {
		if (state == GO && solvable) {
			if (steps > 0)
				move(std::get<2>(solution)[std::get<2>(solution).size() - steps], steps);
			else {
				draw_puzzle(0, state);
			}
		}
		else
			draw_puzzle(steps > 0 ? steps : std::get<2>(solution).size(), state);
		window.display();
		window.clear(sf::Color{0,25,45});
	};

	int		select() {
		++bar;
		if (bar == bars.size())
			bar = 0;
		texts[0].setString(bars[bar]);
		texts[0].setFillColor(colors[bar]);
		return bar;
	}

	void	set_puzzle(Puzzle const& puzzle, SearchAlgorithm::Solution const& solution) {

		for (int i = 0; i < size * size; ++i) {
			sprites.emplace_back(sf::Sprite{Assets::getInstance()->get_texture(),
											sf::IntRect(5 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE)});
			numbers.emplace_back(sf::Text{std::to_string(puzzle.get_sequence()[i]),
										  Assets::getInstance()->get_font(), TILE_SIZE * 3});
			numbers[i].setFillColor(sf::Color::Black);
		}

		set_positions(sprites, 0);
		set_positions(numbers, TILE_SIZE*SCALE / 4.5);

		float padding_y = get_y(HEIGHT / 2.5) + 40;
		float padding_x = get_x(0);

		texts[0].setPosition(padding_x, 15);
		for (int i = 1; i < texts.size(); ++i) {
			texts[i].setPosition(padding_x, padding_y);
			padding_y += 30 + (i == 1) * 30;
		}
		if (solvable)
			reset_puzzle(puzzle, solution);
	}

	void	reset_puzzle(Puzzle const& puzzle, SearchAlgorithm::Solution const& solution) {

		space_x = puzzle.get_space().first;
		space_y = puzzle.get_space().second;

		for (int i = 0; i < size * size; ++i) {
			sprites[i].setScale(SCALE, SCALE);
			numbers[i].setString(std::to_string(puzzle.get_sequence()[i]));
			numbers[i].setCharacterSize(TILE_SIZE * 3);
		}

		sprites[space_x * size + space_y].setScale(0, 0);
		numbers[space_x * size + space_y].setCharacterSize(0);

		auto[time, count, move] = solution;
		texts[1].setString("  ?");
		texts[2].setString(std::string("TIME = ") + (time ? std::to_string(time) : "?") + " S");
		texts[3].setString(std::string("STEPS = " + (move.size() ? std::to_string(move.size()) : "?")));
		texts[4].setString("STATES = " + (count ? std::to_string(count) : "?"));
	}

	float 	get_x(float padding) { return (WIDTH  - TILE_SIZE*SCALE*size)/2.f + padding - 5; }

	float 	get_y(float padding) { return (HEIGHT - TILE_SIZE*SCALE*size)/3.5f + padding; }

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
									get_y(padding_y) - k / size);
			padding_x += SCALE*TILE_SIZE + PADDING;
		}
	}

	void 	draw_puzzle(int step, States state) {

		window.draw(icons[state]);

		for (int i = 0; i < sprites.size(); ++i) {
			window.draw(sprites[i]);
			window.draw(numbers[i]);
		}

		texts[1].setString("  " + (step == 0 && state == GO ? "0" : step == 0 ? "" : std::to_string(step)));
		for (int i = 0; i < texts.size(); ++i) {
			window.draw(texts[i]);
		}
	}

	void move(Move dir, int& step) {
		int dx = 0;
		int dy = 0;
		float speed = 7;

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

			window.clear(sf::Color{0,25,45});
			draw_puzzle(step, GO);
			window.display();
			i += speed;
		}

		sprites[(space_x + dy) * size + space_y + dx].setPosition(pos_1);
		numbers[(space_x + dy) * size + space_y + dx].setPosition(pos_2);

		std::swap(sprites[(space_x + dy) * size + space_y + dx], sprites[space_x * size + space_y]);
		std::swap(numbers[(space_x + dy) * size + space_y + dx], numbers[space_x * size + space_y]);

		space_x += dy;
		space_y += dx;

		for (int i = 0; i < 3; ++i) {
			window.clear(sf::Color{0, 25, 45});
			draw_puzzle(step, GO);
			window.display();
		}
	}
};
