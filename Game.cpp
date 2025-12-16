#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Snake Game"),
      snake(),
      food(),
      gameState(GameState::Playing),
      TimePerFrame(sf::seconds(0.15f)), // Snake speed
      timeSinceLastUpdate(sf::Time::Zero)
{
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Error: Could not load font 'arial.ttf'. "
                  << "Ensure it's in the working directory.\n";
        // Game can continue, but text won't show
    }
    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setStyle(sf::Text::Bold);
    // Center text
    sf::FloatRect textBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                           textBounds.top + textBounds.height / 2.0f);
    gameOverText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

    restartText.setFont(font);
    restartText.setString("Press Enter or Click to Restart");
    restartText.setCharacterSize(30);
    restartText.setFillColor(sf::Color::White);
    sf::FloatRect restartBounds = restartText.getLocalBounds();
    restartText.setOrigin(restartBounds.left + restartBounds.width / 2.0f,
                          restartBounds.top + restartBounds.height / 2.0f);
    restartText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 60.0f);

    resetGame(); // Initial setup
}

void Game::resetGame() {
    snake.reset();
    food.spawn(snake.getSegments());
    gameState = GameState::Playing;
    timeSinceLastUpdate = sf::Time::Zero;
    gameClock.restart(); // Restart clock for new game
}


void Game::run() {
    while (window.isOpen()) {
        sf::Time elapsedTime = gameClock.restart();
        timeSinceLastUpdate += elapsedTime;

        processEvents();

        // Fixed time step update
        while (timeSinceLastUpdate >= TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            if (gameState == GameState::Playing) {
                update(TimePerFrame); // Pass fixed delta time, though snake update is discrete
            }
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (gameState == GameState::Playing) {
                snake.handleInput(event.key.code);
            } else if (gameState == GameState::GameOver) {
                if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
                    resetGame();
                }
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (gameState == GameState::GameOver && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                if (restartText.getGlobalBounds().contains(mousePosF)) {
                    resetGame();
                }
            }
        }
    }
}

void Game::update(sf::Time /*dt*/) { // dt might be unused if logic is purely step-based
    // Original single file version called snake.pop_back() unless food was eaten.
    // New structure: snake.update() always moves head and pops tail.
    // If food is eaten, snake.grow() adds a segment.

    sf::Vector2i oldHeadPos = snake.getHeadPosition(); // Store before move
    snake.update(); // Moves snake (adds new head, removes old tail)

    // Check for food collision
    if (snake.getHeadPosition() == food.getPosition()) {
        // Snake effectively grew because update moved head and popped tail,
        // then grow adds a new segment where the tail was.
        // The original logic was: add head. if food: spawn new food. else: pop tail.
        // To match that:
        // 1. snake.update() should only add head, not pop tail.
        // 2. Here, check food. If not eaten, then pop tail from snake.
        // Let's adjust Snake::update and Snake::grow to fit this better.

        // ---- Revised logic for Snake class for cleaner food handling ----
        // Snake::update() will now just calculate new head and insert it.
        // Snake::trimTail() will pop the tail.
        // Snake::grow() would make the next trimTail() not happen.

        // For current Snake.cpp:
        // snake.update() already moves (adds head, pops tail).
        // So if food is eaten, we need to "undo" the pop_back or add one segment.
        snake.grow(); // This adds a segment at the tail.
        food.spawn(snake.getSegments());
    }


    // Check for collisions
    if (snake.checkSelfCollision() || snake.checkWallCollision()) {
        gameState = GameState::GameOver;
    }
}

void Game::render() {
    window.clear(sf::Color(30, 30, 30));

    snake.draw(window);
    food.draw(window);

    if (gameState == GameState::GameOver) {
        window.draw(gameOverText);
        window.draw(restartText);
    }

    window.display();
}