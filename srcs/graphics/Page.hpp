//
// Created by Achiote Tory on 6/8/22.
//

#pragma once
#include "iostream"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "../models/Puzzle.hpp"

const int WIDTH = 1000;
const int HEIGHT = 600;
const int TEXT_SIZE = 50;
const int TILE_SIZE = 16;
const int PADDING = 4;
float SCALE = 4;
//const char* FONT = "/Users/atory/CLionProjects/N-Puzzle/srcs/resources/graphics/Awkward/AwkwardExt.ttf";
//const char* BOXES =  "/Users/atory/CLionProjects/N-Puzzle/srcs/resources/graphics/puzzle_tileset.png";
const char* FONT = "/home/atory/CLionProjects/N-Puzzle/srcs/resources/graphics/Awkward/AwkwardExt.ttf";
const char* BOXES =  "/home/atory/CLionProjects/N-Puzzle/srcs/resources/graphics/puzzle_tileset.png";

class Assets {

	static Assets*	instance;
	sf::Texture	texture;
	sf::Font	font;

	Assets() {
		if (!font.loadFromFile(FONT)
			|| !texture.loadFromFile(BOXES)) {
			std::cerr << "[ couldn't load assert ]\n";
		}
	}

  public:
	static Assets*	getInstance() {
		return !instance ? new Assets() : instance;
	};
//	~Assets() { delete instance; };
	~Assets();

	sf::Texture const&	get_texture() const { return texture; }
	sf::Font const&		get_font() const	{ return font; }
};

Assets*	Assets::instance = 0;

class Menu {

	sf::RenderWindow*		window;

	std::vector<sf::Text>	menu_bars;
	int 					controller;

  public:
	Menu(sf::RenderWindow* w): window(w) {
		controller = 0;
		menu_bars.emplace_back("HEURISTICS 1", Assets::getInstance()->get_font(), TEXT_SIZE);
		menu_bars.emplace_back("HEURISTICS 2", Assets::getInstance()->get_font(), TEXT_SIZE);
		menu_bars.emplace_back("HEURISTICS 3", Assets::getInstance()->get_font(), TEXT_SIZE);

		for (auto & text : menu_bars) {
			text.setFillColor(sf::Color::White);
			text.setStyle(sf::Text::Bold);
		}

		menu_bars[controller].setString("> " + menu_bars[controller].getString());
		menu_bars[controller].setFillColor(sf::Color::Yellow);
	}

	void down() {
		menu_bars[controller].setFillColor(sf::Color::White);
		menu_bars[controller].setString(menu_bars[controller].getString().substring(2));
		++controller;
		if (controller == menu_bars.size())
			controller = 0;

		menu_bars[controller].setString("> " + menu_bars[controller].getString());
		menu_bars[controller].setFillColor(sf::Color::Yellow);
	}

	void up() {
		menu_bars[controller].setFillColor(sf::Color::White);
		menu_bars[controller].setString(menu_bars[controller].getString().substring(2));
		--controller;
		if (controller == -1)
			controller = menu_bars.size() - 1;

		menu_bars[controller].setString("> " + menu_bars[controller].getString());
		menu_bars[controller].setFillColor(sf::Color::Yellow);
	}

	void display() {
		float padding_y = HEIGHT / 3;
		float padding_x = WIDTH / 10;

		for (int i = 0; i < menu_bars.size(); ++i) {
			padding_y += 40;
			menu_bars[i].setPosition(padding_x, padding_y);
			window->draw(menu_bars[i]);
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

		int percentage = size * (SCALE * TILE_SIZE) / (HEIGHT / 100);
		while (percentage <= 50 || percentage >= 60) {
			SCALE *= percentage < 50 ? 1.25 : 0.75;
			percentage = size * (SCALE * TILE_SIZE) / (HEIGHT / 100);
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
//	float 	get_x(float padding) { return (WIDTH  - TILE_SIZE*SCALE*size)/1.75f + padding; }
	float 	get_x(float padding) { return (WIDTH)/1.8f + padding; }

	float 	get_y(float padding) { return (HEIGHT - TILE_SIZE*SCALE*size)/4.f + padding; }

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



	void 	display(int step) {
		for (int i = 0; i < sprites.size(); ++i) {
			window->draw(sprites[i]);
			window->draw(numbers[i]);
		}
	}

};

class Screen {

    sf::RenderWindow	window;
	Menu				menu;
	Solver				solver;

  public:
	Screen(std::string const& title,
		   unsigned int width,
		   unsigned int height,
		   Puzzle* puzzle):
									window(sf::VideoMode({width, height}), title),
									menu(&window),
									solver(&window, puzzle){

		window.setFramerateLimit(60);
		window.setMouseCursorVisible(false);


	}

	void display() {
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
						;
				}
			}
			menu.display();
			solver.display(0);
			window.display();
			window.clear(sf::Color::Black);
		}
	}
};

class Visualizer {
	Screen		screen;

  public:
	Visualizer(Puzzle* puzzle): screen("N-Puzzle", WIDTH, HEIGHT, puzzle) {
	}

	void	on() {
		screen.display();
	}
};