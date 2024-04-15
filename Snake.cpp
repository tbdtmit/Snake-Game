#include "Snake.h"
#include "Food.h"


Snake::Snake(int gridSize) : gridSize(gridSize) {
    // Initialize the snake with a single segment at the center of the screen.
    sf::RectangleShape segment(sf::Vector2f(gridSize, gridSize));
    segment.setFillColor(sf::Color::Green);
    segment.setPosition(10 * gridSize, 10 * gridSize);
    body.push_back(segment);

    // Set the initial direction.
    direction.x = gridSize;
    direction.y = 0;



}

void Snake::move() {
    // Move the snake by adding a new segment at the front and removing the tail.
    RectangleShape newSegment = body.front();
    Vector2f headPosition = newSegment.getPosition();
    auto tx = (headPosition + direction).x;
    auto ty = (headPosition + direction).y;

    if (tx > 780) tx = 0;
    if (tx < 0) tx = 780;
    if (ty > 580) ty = 0;
    if (ty < 0) ty = 580;

    newSegment.setPosition(tx, ty);

    body.insert(body.begin(), newSegment);
    body.pop_back();

    //cout << "x = " << tx << endl;
    //cout << "y = " << ty << endl;

}

void Snake::grow() {
    // Add a new segment to the end of the snake.
    sf::RectangleShape newSegment = body.back();
    newSegment.setFillColor(sf::Color::Green);
    move();
    body.push_back(newSegment);
}

void Snake::render(sf::RenderWindow& window) {
    body.front().setFillColor(Color::Cyan);
    for (const auto& segment : body) {
        window.draw(segment);
    }
    body.front().setFillColor(Color::Green);
}

bool Snake::isCollidingWithItself() {
    // Check if the head of the snake collides with any other segment.
    for (size_t i = 1; i < body.size(); i++) {
        if (body[0].getGlobalBounds().intersects(body[i].getGlobalBounds())) {
            cout << "cham diem" << " " << i << endl;
            return true;
        }
    }
    return false;
}

Vector2f Snake :: getDirection()
{
    return direction;
}

int Snake::getGridSize()
{
    return gridSize;
}

void Snake::setDirection(Vector2f vt) 
{
    direction = vt;
}

bool Snake::headCollidesWithFood(Food fd)
{
    sf::RectangleShape newSegment = body.front();
    sf::Vector2f headPosition = newSegment.getPosition();
    auto vt = fd.getPosition();
    if (headPosition == vt)
    {
        return 1;
    }

    else return 0;
}

bool Snake::headCollidesWithFood(superFood fd)
{
    Vector2f mv[4] = { Vector2f(0,0),Vector2f(20,0) ,Vector2f(0,20) ,Vector2f(20,20) };
    sf::RectangleShape newSegment = body.front();
    sf::Vector2f headPosition = newSegment.getPosition();
    auto vt = fd.getPosition();
    for (int i = 0; i < 4; i++)
    {
        if (headPosition == vt + mv[i])
        {
            return 1;
        }
    }


    return 0;
}

vector<sf::RectangleShape> Snake::getBody() const
{
    return body;

}