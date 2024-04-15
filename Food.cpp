
#include "Food.h"
#include "Snake.h"

using namespace sf;
using namespace std;

bool Food::foodCollidesWithSnake(Snake sna) {
    for (auto segment : sna.getBody())
    {
        if (segment.getGlobalBounds().intersects(food.getGlobalBounds()))
            return true;
    }
    return  0;
}

bool Food::foodCollidesWithSnake() {
    return 0;
}

Food::Food(int gridSize, Snake sna) : gridSize(gridSize) {
    food.setSize(sf::Vector2f(gridSize, gridSize));
    food.setFillColor(sf::Color::Red);
    score = 1;
    generate(sna);
}

void Food::generate(Snake sna) {
    int maxX = 800 / gridSize;
    int maxY = 600 / gridSize;

    do {
        position.x = rand() % maxX * gridSize;
        position.y = rand() % maxY * gridSize;
        food.setPosition(position);
    } while (foodCollidesWithSnake(sna));

}

void Food::render(sf::RenderWindow& window) {
    window.draw(food);
}

sf::Vector2f Food::getPosition() {
    return position;
}

superFood::superFood(int gridSize, Snake sna) : Food(gridSize, sna) {
    score = 5;
}

void superFood::setPosition(Vector2f vt)
{
    position = vt;
    food.setPosition(vt);
}

bool superFood ::foodCollidesWithSnake(Snake sna) {
    Vector2f mv[4] = { Vector2f(0,0),Vector2f(20,0) ,Vector2f(0,20) ,Vector2f(20,20) };

    for (int i = 0; i < 4; i++)
    {
        auto vt = this->getPosition() + mv[i];
        sf::RectangleShape te;
        te.setPosition(vt);
        for (auto segment : sna.getBody())
        {
            if (segment.getGlobalBounds().intersects(te.getGlobalBounds()))
                return true;
        }

    }

    return  0;
}