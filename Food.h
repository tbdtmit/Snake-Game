#pragma once


#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

class Snake;


using namespace sf;
using namespace std;

class Food {
public:

    int score;
    Food(int gridSize, Snake sna);
    void generate(Snake sna);
    void render(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    bool foodCollidesWithSnake(Snake sna);
    bool foodCollidesWithSnake();


protected:
    sf::RectangleShape food;
    int gridSize;
    sf::Vector2f position;

};


class superFood : public Food {
public:
    superFood(int gridSize, Snake sna);
    void setPosition(Vector2f vt);
    bool foodCollidesWithSnake(Snake sna);
};
