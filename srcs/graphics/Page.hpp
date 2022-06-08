//
// Created by Achiote Tory on 6/8/22.
//

#pragma once
#include "iostream"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

const int WIDTH = 1000;
const int HEIGHT = 600;
const int TEXT_SIZE = 50;
const char* FONT = "/Users/atory/CLionProjects/N-Puzzle/srcs/resources/graphics/Awkward/AwkwardExt.ttf";
const char* BOXES =  "/Users/atory/CLionProjects/N-Puzzle/srcs/resources/graphics/puzzle_tileset.png";

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
		menu_bars[controller].setFillColor(sf::Color::Cyan);
	}

	void down() {
		menu_bars[controller].setFillColor(sf::Color::White);
		menu_bars[controller].setString(menu_bars[controller].getString().substring(2));
		++controller;
		if (controller == menu_bars.size())
			controller = 0;

		menu_bars[controller].setString("> " + menu_bars[controller].getString());
		menu_bars[controller].setFillColor(sf::Color::Cyan);
	}

	void up() {
		menu_bars[controller].setFillColor(sf::Color::White);
		menu_bars[controller].setString(menu_bars[controller].getString().substring(2));
		--controller;
		if (controller == -1)
			controller = menu_bars.size() - 1;

		menu_bars[controller].setString("> " + menu_bars[controller].getString());
		menu_bars[controller].setFillColor(sf::Color::Cyan);
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

class Screen {

    sf::RenderWindow	window;
	Menu				menu;

  public:
	Screen(std::string const& title,
		   unsigned int width,
		   unsigned int height):
									window(sf::VideoMode({width, height}), title),
									menu(&window) {

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
			window.display();
			window.clear(sf::Color::Black);
		}
	}
};

class Visualizer {
	Screen		menu;

  public:
	Visualizer(): menu( "N-Puzzle", WIDTH, HEIGHT) {
	}

	void	on() {
		menu.display();
	}
};