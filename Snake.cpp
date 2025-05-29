#include "Snake.hpp"

Snake::Snake() : currentDirection(Direction::Right), nextDirection(Direction::Right) {
    segmentShape.setSize(sf::Vector2f(CELL_SIZE - 1.0f, CELL_SIZE - 1.0f));
    segmentShape.setFillColor(sf::Color::Green);
    reset();
}

void Snake::reset() {
    segments.clear();
    segments.push_back({GRID_WIDTH / 2, GRID_HEIGHT / 2});
    segments.push_back({GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2});
    segments.push_back({GRID_WIDTH / 2 - 2, GRID_HEIGHT / 2});
    currentDirection = Direction::Right;
    nextDirection = Direction::Right;
}

void Snake::handleInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Up && currentDirection != Direction::Down) {
        nextDirection = Direction::Up;
    } else if (key == sf::Keyboard::Down && currentDirection != Direction::Up) {
        nextDirection = Direction::Down;
    } else if (key == sf::Keyboard::Left && currentDirection != Direction::Right) {
        nextDirection = Direction::Left;
    } else if (key == sf::Keyboard::Right && currentDirection != Direction::Left) {
        nextDirection = Direction::Right;
    }
}

void Snake::update() {
    if (segments.empty()) return;

    currentDirection = nextDirection; // Apply the buffered direction change

    sf::Vector2i newHead = segments.front();
    switch (currentDirection) {
        case Direction::Up:    newHead.y--; break;
        case Direction::Down:  newHead.y++; break;
        case Direction::Left:  newHead.x--; break;
        case Direction::Right: newHead.x++; break;
        case Direction::None:  return; // Should not happen in normal play
    }

    segments.insert(segments.begin(), newHead);
    // Growth is handled by not popping tail, so just pop tail here for movement
    segments.pop_back();
}

void Snake::grow() {
    if (segments.empty()) return;
    // To grow, we effectively re-add the segment that would have been popped.
    // The update() method always pops, so if we grow, we add one extra at the tail.
    // A simpler way is to just not pop_back() in update() if growth happens.
    // For this structure, let's assume growth means adding to tail based on last tail direction.
    // However, the common method is: move (add head, pop tail), then if food eaten, re-add tail.
    // So, update() always moves (adds head, pops tail). If food eaten, call grow() which
    // adds a segment at the previous tail's position.
    // Let's modify: update() adds head. grow() adds another segment. If not growing, update() pops.
    // For simplicity matching the single file: update adds head, if not growing, it also pops tail.
    // grow() will simply prevent the pop_back for one frame.
    // To implement grow correctly with current `update()`:
    // `update()` adds head. If `grow()` was called, it will effectively make the snake longer.
    // The logic should be: move snake, check food. If food, don't pop tail.
    // Here, we'll just add a segment to the tail. It's simpler for this structure.
    segments.push_back(segments.back()); // Duplicate the last segment to grow
}


void Snake::draw(sf::RenderWindow& window) const {
    for (const auto& segment : segments) {
        sf::RectangleShape shape = segmentShape; // Copy base shape
        shape.setPosition(static_cast<float>(segment.x * CELL_SIZE),
                          static_cast<float>(segment.y * CELL_SIZE));
        window.draw(shape);
    }
}

sf::Vector2i Snake::getHeadPosition() const {
    if (segments.empty()) return {-1, -1}; // Should not happen
    return segments.front();
}

const std::vector<sf::Vector2i>& Snake::getSegments() const {
    return segments;
}

bool Snake::checkSelfCollision() const {
    if (segments.size() < 2) return false;
    sf::Vector2i head = segments.front();
    for (size_t i = 1; i < segments.size(); ++i) {
        if (segments[i] == head) {
            return true;
        }
    }
    return false;
}

bool Snake::checkWallCollision() const {
    if (segments.empty()) return false;
    sf::Vector2i head = segments.front();
    return (head.x < 0 || head.x >= GRID_WIDTH ||
            head.y < 0 || head.y >= GRID_HEIGHT);
}