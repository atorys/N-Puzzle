//
// Created by atory on 03.06.22.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "../algorithm/SearchAlgorithm.hpp"

const int WIDTH = 550;
const int HEIGHT = 700;
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

public:
    Visualizer():	window(sf::VideoMode({WIDTH, HEIGHT}), "N-Puzzle") {
        window.setFramerateLimit(30);
        font.loadFromFile(FONT);
        texture.loadFromFile(BOXES);
    }

    void    start() {

    }

    void	visualize(Puzzle* start_puzzle, SearchAlgorithm::Solution const& solution, double time) {
        sf::Event	event;
        States		state = PAUSE;

        set_puzzle(start_puzzle, solution, time);
        std::vector<Move> moves = std::get<2>(solution);
        int steps = moves.size();

        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (state == GO)
                        state = PAUSE;
                    else if (state == PAUSE) {
                        state = GO;
                        if (steps == 0) {
                            set_puzzle(start_puzzle, solution, time);
                            steps = moves.size();
                        }
                    }
                }
            }

            if (state == GO) {
                if (steps > 0)
                    move(moves[moves.size() - steps], steps);
                else
                    draw_puzzle(0);
            }
            else
                draw_puzzle(steps > 0 ? steps : moves.size());
            window.display();
            window.clear(sf::Color::Black);
        }
    }

private:
    void	set_puzzle(Puzzle *puzzle, SearchAlgorithm::Solution const& solution, double time) {

        size = puzzle->get_size();

        int percentage = size * (SCALE * TILE_SIZE) / (WIDTH / 100);
        while (percentage <= 60 || percentage >= 70) {
            SCALE *= percentage < 60 ? 1.25 : 0.75;
            percentage = size * (SCALE * TILE_SIZE) / (WIDTH / 100);
        }


        set_sprites(puzzle);
        set_numbers(puzzle);

        texts.clear();
        texts.emplace_back("# ", font, 50);
        texts.emplace_back(std::string("TIME = ") + std::to_string(time) + " S", font, 40);
        texts.emplace_back("STEPS = " + std::to_string(std::get<2>(solution).size()) , font, 40);
        texts.emplace_back("STATES = " + std::to_string(std::get<1>(solution)), font, 40);
        for (auto & text : texts) {
            text.setFillColor(sf::Color::White);
//			texts[i].setStyle(sf::Text::);
        }

    }
    float 	get_x(float padding) { return (WIDTH  - TILE_SIZE*SCALE*size)/2.f + padding; }

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

//		float padding_y = sprites.back().getPosition().y + TILE_SIZE*SCALE + 15;
//		float padding_x = sprites.begin()->getPosition().x;
        float padding_y = get_y(HEIGHT / 2);
        float padding_x = get_x(0);

        texts[0].setString("# " + std::to_string(step));
        for (int i = 0; i < texts.size(); ++i) {
            texts[i].setPosition(padding_x, padding_y);
            padding_y += 30 + !i * 40;
            window.draw(texts[i]);
        }
    }

    void move(Move dir, int& step) {
        int dx = 0;
        int dy = 0;
        float speed = 10;

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