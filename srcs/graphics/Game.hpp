//
// Created by atory on 03.06.22.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

const int WIDTH = 500;
const int HEIGHT = 350;
const int TILE_SIZE = 16;
const int PADDING = 4;
const char* FONT = "/home/atory/CLionProjects/N-Puzzle/srcs/graphics/resources/Awkward/AwkwardExt.ttf";
const char* FONT_numbers = "/home/atory/CLionProjects/N-Puzzle/srcs/graphics/resources/Awkward/AwkwardExt.ttf";
const char* BOXES =  "/home/atory/CLionProjects/N-Puzzle/srcs/graphics/resources/puzzle_tileset.png";

float SCALE = 4;

enum States {
	Menu,
	Solver
};


class Game {

	sf::RenderWindow	window;
	States				state;

	sf::Font							font;
	sf::Font							font_numbers;
	std::map<std::string, sf::Texture>	textures;
	std::map<std::string, sf::Sprite>	sprites;
	std::vector<sf::Text>				texts;

	Puzzle				default_puzzle;
	Puzzle*				current_puzzle;

  public:
	Game():	window(sf::VideoMode({WIDTH, HEIGHT}), "N-Puzzle"),
													state(States::Menu),
													default_puzzle(3, std::vector<int>{1, 2, 3, 8, 0, 4, 7, 6, 5}),
													current_puzzle(nullptr) {
		window.setFramerateLimit(30);
		window.clear(sf::Color::White);
		font.loadFromFile(FONT);
		font_numbers.loadFromFile(FONT_numbers);
		textures["boxes"].loadFromFile(BOXES);

		sprites["empty_box"].setTexture(textures["boxes"]);
		sprites["heart_box"].setTexture(textures["boxes"]);

		sprites["empty_box"].setTextureRect(sf::IntRect(5 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
		sprites["heart_box"].setTextureRect(sf::IntRect(4 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));


		texts.emplace_back("# START", font, 35);
		texts.emplace_back("# SOLVE", font, 35);
		texts.emplace_back("# GENERATE", font, 35);
		for (int i = 0; i < texts.size(); ++i) {
			texts[i].setFillColor(sf::Color::White);
		}
		current_puzzle = &default_puzzle;
	}

	void	set_puzzle(Puzzle *puzzle) { current_puzzle = puzzle; };
	float 	get_x(float padding, int size) { return (WIDTH  - TILE_SIZE*SCALE*size)/1.3f + padding; }
	float 	get_y(float padding, int size) { return (HEIGHT - TILE_SIZE*SCALE*size)/2.f + padding; }

	void	start() {
		sf::Event event;
		while (window.isOpen()) {

			int percentage = current_puzzle->get_size() * (SCALE * TILE_SIZE) / (HEIGHT / 100);
			while (percentage <= 60 || percentage >= 80) {
				SCALE *= percentage < 60 ? 1.25 : 0.75;
				percentage = current_puzzle->get_size() * (SCALE * TILE_SIZE) / (HEIGHT / 100);
			}

			window.clear(sf::Color::Black);
			if (state == States::Menu) {
				draw_menu();
				draw_puzzle(&default_puzzle);
			}
			if (state == States::Solver) {
				draw_puzzle(current_puzzle);
			}
			while (window.pollEvent(event)) {
				if (current_puzzle) {
					state = Solver;
					int percentage = current_puzzle->get_size() * (SCALE * TILE_SIZE) / (HEIGHT / 100);
					while (percentage <= 60 || percentage >= 80) {
						SCALE *= percentage < 60 ? 1.25 : 0.75;
						percentage = current_puzzle->get_size() * (SCALE * TILE_SIZE) / (HEIGHT / 100);
					}
				}
				if (event.type == sf::Event::Closed) {
					window.close();
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					sf::Vector2i pos = sf::Mouse::getPosition(window);
					int x = (pos.x - get_x(0, current_puzzle->get_size()))/(SCALE * TILE_SIZE);
					int y = (pos.y - get_y(0, current_puzzle->get_size()))/(SCALE * TILE_SIZE);

					Move move = NONE;
					if (current_puzzle->get_space().first == y && current_puzzle->get_space().second == x + 1)
						move = Move::LEFT;
					else if (current_puzzle->get_space().first == y && current_puzzle->get_space().second == x - 1)
						move = Move::RIGHT;
					else if (current_puzzle->get_space().second == x && current_puzzle->get_space().first == y + 1)
						move = Move::UP;
					else if (current_puzzle->get_space().second == x && current_puzzle->get_space().first == y - 1)
						move = Move::DOWN;
					current_puzzle->try_move(move);
//					float speed = 3;
//					sf::Sprite	current = sprites["empty_box"];
//					for (int i = 0; i < SCALE*TILE_SIZE; i += speed) {
//						current.move(speed*	)
//					}
				}
			}
			window.display();
		}
	}

	void 	draw_puzzle(Puzzle *puzzle) {
		sf::Sprite	current = sprites["empty_box"];
		sf::Text	number = {"", font_numbers, TILE_SIZE * 2};
		int			size = puzzle->get_size();
		float		padding_x = 0;
		float		padding_y = 0;

		number.setFillColor(sf::Color::Black);
		for (int i = 0; i < size * size; ++i) {
			if (i && i % size == 0) {
				padding_y += SCALE*TILE_SIZE + 5;
				padding_x = 0;
			}
			if (puzzle->get_sequence()[i]) {
				current.setPosition(get_x(padding_x, size),
									get_y(padding_y, size));
				current.setScale(SCALE, SCALE);
				window.draw(current);
				number.setString(std::to_string(puzzle->get_sequence()[i]));
				number.setPosition(get_x(padding_x, size) + TILE_SIZE*SCALE / 4.5,get_y(padding_y, size));
				if (state != Menu)
					window.draw(number);

			} else if (state == Menu) {
				sf::Sprite additional = sprites["heart_box"];
				additional.setPosition(get_x(padding_y, size),get_y(padding_x, size));
				additional.setScale(SCALE , SCALE);
				window.draw(additional);
			}
			padding_x += SCALE*TILE_SIZE + 5;
		}
	}

	void	draw_menu() {

		float padding_y = HEIGHT / texts.size() / 2;
		float padding_x = (WIDTH  - TILE_SIZE*SCALE*(current_puzzle->get_size())) / 4;
		for (int i = 0; i < texts.size(); ++i) {
			texts[i].setPosition(padding_x, padding_y);
			padding_y += HEIGHT / texts.size() / 2;
			window.draw(texts[i]);
		}

	}
};
