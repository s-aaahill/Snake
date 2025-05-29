#include "Food.hpp"
#include <cstdlib> // For rand()

Food::Food() {
    shape.setSize(sf::Vector2f(CELL_SIZE - 1.0f, CELL_SIZE - 1.0f));
    shape.setFillColor(sf::Color::Red);
    // Initial spawn position will be set by Game class or first spawn call
}

void Food::spawn(const std::vector<sf::Vector2i>& snakeSegments) {
    bool onSnake;
    do {
        onSnake = false;
        position.x = rand() % GRID_WIDTH;
        position.y = rand() % GRID_HEIGHT;
        for (const auto& segment : snakeSegments) {
            if (segment == position) {
                onSnake = true;
                break;
            }
        }
    } while (onSnake);
}

void Food::draw(sf::RenderWindow& window) const {
    sf::RectangleShape tempShape = shape; // Make a mutable copy for setPosition
    tempShape.setPosition(static_cast<float>(position.x * CELL_SIZE),
                          static_cast<float>(position.y * CELL_SIZE));
    window.draw(tempShape);
}

sf::Vector2i Food::getPosition() const {
    return position;
}