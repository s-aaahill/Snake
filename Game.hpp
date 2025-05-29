#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "Snake.hpp"
#include "Food.hpp"
#include "Common.hpp"
#include <iostream> // For error output

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time dt);
    void render();
    void resetGame();

    sf::RenderWindow window;
    Snake snake;
    Food food;
    GameState gameState;

    sf::Font font;
    sf::Text gameOverText;

    sf::Clock gameClock;
    sf::Time timeSinceLastUpdate;
    const sf::Time TimePerFrame;
};

#endif // GAME_HPP