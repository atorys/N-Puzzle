//
// Created by Achiote Tory on 6/9/22.
//

#pragma once

#include "iostream"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "../models/Puzzle.hpp"

const int WIDTH = 550;
const int HEIGHT = 750;
const int TILE_SIZE = 16;
const int PADDING = 7;
float SCALE = 4;
const char* FONT = "/home/io/Documents/N-Puzzle/srcs/resources/graphics/Awkward/AwkwardExt.ttf";
const char* BOXES =  "/home/io/Documents/N-Puzzle/srcs/resources/graphics/puzzle_tileset.png";
const char* ICONS =  "/home/io/Documents/N-Puzzle/srcs/resources/graphics/icons.png";
//const char* FONT = "/home/atory/CLionProjects/N-Puzzle/srcs/resources/graphics/Awkward/AwkwardExt.ttf";
//const char* BOXES =  "/home/atory/CLionProjects/N-Puzzle/srcs/resources/graphics/puzzle_tileset.png";

enum States {
	PAUSE = 0,
	GO
};

class Assets {

	static Assets*	instance;
	sf::Texture		texture;
	sf::Texture		icons;
	sf::Font		font;

	Assets() {
		if (!font.loadFromFile(FONT)
			|| !texture.loadFromFile(BOXES)
			|| !icons.loadFromFile(ICONS)) {
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
	sf::Texture const&	get_icons() const	{ return icons; }
	sf::Font const&		get_font() const	{ return font; }
};

Assets*	Assets::instance = nullptr;
