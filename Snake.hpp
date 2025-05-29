#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Common.hpp"

class Snake {
public:
    Snake();
    void reset();
    void handleInput(sf::Keyboard::Key key);
    void update();
    void grow();
    void draw(sf::RenderWindow& window) const;

    sf::Vector2i getHeadPosition() const;
    const std::vector<sf::Vector2i>& getSegments() const;
    bool checkSelfCollision() const;
    bool checkWallCollision() const;

private:
    std::vector<sf::Vector2i> segments;
    Direction currentDirection;
    Direction nextDirection; // Buffer next direction to prevent 180 degree turn
    sf::RectangleShape segmentShape;
};

#endif // SNAKE_HPP