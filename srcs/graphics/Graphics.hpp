//
// Created by Achiote Tory on 6/10/22.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "Assets.hpp"

class Graphics {

	sf::RenderWindow		window;

	std::vector<sf::Sprite>	sprites;
	std::vector<sf::Sprite>	icons;
	std::vector<sf::Text>	numbers;
	std::vector<sf::Text>	texts;

	Puzzle*					puzzle;
	int						Ox;
	int						Oy;
	int 					size;

	std::vector<sf::Color>		colors;
	std::vector<std::string>	bars;

  public:
	Graphics(): window(sf::VideoMode({WIDTH, HEIGHT}), "N-Puzzle"),
				bars({"    EUCLIDEAN >", " < CHEBYSHEV >", " < MANHATTAN   "}),
				colors({{203, 255, 77}, {147,112,219}, {255,215,0}}) {

		window.setFramerateLimit(60);
		window.setMouseCursorVisible(false);
	}

	sf::RenderWindow&		get_window() 						{ return this->window; }
	std::string const&		get_bar(int& selected_bar) const	{ return this->bars[selected_bar]; }
	float 					get_x(float padding) const			{ return (WIDTH  - TILE_SIZE*SCALE*size)/2.f + padding - 5; }
	float 					get_y(float padding) const			{ return (HEIGHT - TILE_SIZE*SCALE*size)/3.5f + padding; }

	void	set_puzzle(Puzzle *p) {
		this->size = p->size();
		this->puzzle = p;

		int percentage;
		while ((percentage = size * (SCALE * TILE_SIZE) / (WIDTH / 100)) <= 60
			   || percentage >= 70) {
			SCALE *= (percentage < 60) ? 1.25 : 0.75;
		}

		if (puzzle->is_solvable()) {
			for (int i = 0; i < 5; ++i) {
				texts.emplace_back("", Assets::getInstance()->get_font(), 45 + 10 * (i < 1) + 15 * (i == 1));
				texts[i].setFillColor(sf::Color::White);
			}
			texts[0].setString(bars[0]);
			texts[0].setFillColor(colors[0]);
		} else {
			texts.emplace_back("NOT SOLVABLE ;(", Assets::getInstance()->get_font(), 50);
			texts[0].setFillColor(sf::Color::Red);
		}

		load(SearchAlgorithm::Solution{0, 0, 0});
	}

	void	display(States& state, int& steps, SearchAlgorithm::Solution const& solution) {
		if (state == GO && puzzle->is_solvable()) {
			if (steps > 0) {
				move(std::get<2>(solution)[std::get<2>(solution).size() - steps], steps);
			} else {
				draw_puzzle(0, state);
			}

		} else {
			draw_puzzle(steps > 0 ? steps : std::get<2>(solution).size(), state);
		}
	};

	void	select(int* bar) {
		++(*bar);
		if (*bar == bars.size()) {
			*bar = 0;
		}
		texts[0].setString(bars[*bar]);
		texts[0].setFillColor(colors[*bar]);
	}

	void	load(SearchAlgorithm::Solution const& solution) {

		icons.emplace_back(Assets::getInstance()->get_icons(),
						   sf::IntRect(1 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		icons.emplace_back(Assets::getInstance()->get_icons(),
						   sf::IntRect(0, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE));

		for (auto &icon : icons) {
			icon.setScale(1.8, 1.8);
			icon.setPosition(get_x(0), get_y(HEIGHT / 2.5) + 75);
		}

		for (int i = 0; i < size * size; ++i) {
			sprites.emplace_back(sf::Sprite{Assets::getInstance()->get_texture(),
											sf::IntRect(5 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE)});
			numbers.emplace_back(sf::Text{std::to_string(puzzle->get_sequence()[i]),
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
		if (puzzle->is_solvable()) {
			reset(solution);
		}
	}

	void	reset(SearchAlgorithm::Solution const& solution) {

		Ox = puzzle->get_space().first;
		Oy = puzzle->get_space().second;

		for (int i = 0; i < size * size; ++i) {
			sprites[i].setScale(SCALE, SCALE);
			numbers[i].setString(std::to_string(puzzle->get_sequence()[i]));
			numbers[i].setCharacterSize(TILE_SIZE * 3);
		}

		sprites[Ox * size + Oy].setScale(0, 0);
		numbers[Ox * size + Oy].setCharacterSize(0);

		auto[time, count, move] = solution;
		texts[2].setString(std::string("TIME = ") + (time ? std::to_string(time) : "?") + " S");
		texts[3].setString(std::string("STEPS = " + (move.size() ? std::to_string(move.size()) : "?")));
		texts[4].setString("STATES = " + (count ? std::to_string(count) : "?"));
	}

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

		window.clear(sf::Color{0, 25, 60});
		window.draw(icons[state]);

		for (int i = 0; i < sprites.size(); ++i) {
			window.draw(sprites[i]);
			window.draw(numbers[i]);
		}

		texts[1].setString("  " + (step == 0 && state == GO ? "0" : step == 0 ? "" : std::to_string(step)));
		for (const auto & text : texts) {
			window.draw(text);
		}
		window.display();
	}

	void move(Move dir, int& step) {
		int dx = 0;
		int dy = 0;
		int speed = 7;

		if (dir == Move::UP) { dx = 0; dy = -1;};
		if (dir == Move::DOWN) { dx = 0; dy = 1;};
		if (dir == Move::RIGHT) { dx = 1; dy = 0; };
		if (dir == Move::LEFT) { dx = -1; dy = 0; };

		sf::Vector2f pos_1 = sprites[Ox * size + Oy].getPosition();
		sf::Vector2f pos_2 = numbers[Ox * size + Oy].getPosition();
		sf::Vector2f pos_3 = sprites[(Ox + dy) * size + Oy + dx].getPosition();
		sf::Vector2f pos_4 = numbers[(Ox + dy) * size + Oy + dx].getPosition();

		sprites[Ox * size + Oy].setPosition(pos_3);
		numbers[Ox * size + Oy].setPosition(pos_4);

		--step;
		for (float i = 0; i < TILE_SIZE*SCALE;) {
			sprites[(Ox + dy) * size + Oy + dx].move(-dx * speed, -dy * speed);
			numbers[(Ox + dy) * size + Oy + dx].move(-dx * speed, -dy * speed);

			draw_puzzle(step, GO);
			i += speed;
		}

		sprites[(Ox + dy) * size + Oy + dx].setPosition(pos_1);
		numbers[(Ox + dy) * size + Oy + dx].setPosition(pos_2);

		std::swap(sprites[(Ox + dy) * size + Oy + dx], sprites[Ox * size + Oy]);
		std::swap(numbers[(Ox + dy) * size + Oy + dx], numbers[Ox * size + Oy]);

		Ox += dy;
		Oy += dx;

		for (int i = 0; i < 5; ++i) {
			draw_puzzle(step, GO);
		}
	}
};
