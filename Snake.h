#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

class Food;
class superFood;

using namespace sf;
using namespace std;


class Snake {
public:
    int score = 0;
    Snake(int gridSize);
    void move();
    void grow();
    void render(sf::RenderWindow& window);
    bool isCollidingWithItself();
    Vector2f getDirection();

    int getGridSize();

    void setDirection(Vector2f vt) ;

    bool headCollidesWithFood(Food fd);

    bool headCollidesWithFood(superFood fd);

    vector<sf::RectangleShape> getBody() const;

private:
    std::vector<sf::RectangleShape> body;
    int gridSize;
    sf::Vector2f direction;
};
