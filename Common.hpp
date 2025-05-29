#ifndef COMMON_HPP
#define COMMON_HPP

#include <SFML/System/Vector2.hpp>

// Game constants
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 20;
const int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

// Represents the snake's direction of movement
enum class Direction { None, Up, Down, Left, Right };

// Represents the current state of the game
enum class GameState { Playing, GameOver };

#endif // COMMON_HPP