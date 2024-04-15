#pragma once

#include <SFML/Audio.hpp>
#include "Snake.h"
#include "Food.h"
#include <fstream>

class Snake;
class Food;
class superFood;

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void draw();
    void handleInput();
    void draw_score();
    void gamePlay();
    bool back();
    void write_score(int sc);
    int get_score();
    void lauch();
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text title;
    sf::Text startOption;
    sf::Text exitOption;
    sf::Text highScore;
    sf::CircleShape square;
    int selectedOption;


};