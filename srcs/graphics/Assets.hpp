//
// Created by Achiote Tory on 6/9/22.
//

#pragma once

#include "iostream"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "../models/Puzzle.hpp"

const int WIDTH = 600;
const int HEIGHT = 800;
const int TEXT_SIZE = 50;
const int TILE_SIZE = 16;
const int PADDING = 4;
float SCALE = 4;
const char* FONT = "/Users/atory/CLionProjects/N-Puzzle/srcs/resources/graphics/Awkward/AwkwardExt.ttf";
const char* BOXES =  "/Users/atory/CLionProjects/N-Puzzle/srcs/resources/graphics/puzzle_tileset.png";
//const char* FONT = "/home/atory/CLionProjects/N-Puzzle/srcs/resources/graphics/Awkward/AwkwardExt.ttf";
//const char* BOXES =  "/home/atory/CLionProjects/N-Puzzle/srcs/resources/graphics/puzzle_tileset.png";

class Visualizer;
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

Assets*	Assets::instance = nullptr;
