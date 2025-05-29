#ifndef FOOD_HPP
#define FOOD_HPP

#include <SFML/Graphics.hpp>
#include "Common.hpp"
#include <vector> // For Snake segments in spawn

class Food {
public:
    Food();
    void spawn(const std::vector<sf::Vector2i>& snakeSegments);
    void draw(sf::RenderWindow& window) const;
    sf::Vector2i getPosition() const;

private:
    sf::Vector2i position;
    sf::RectangleShape shape;
};

#endif // FOOD_HPP