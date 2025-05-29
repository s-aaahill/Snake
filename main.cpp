#include "Game.hpp"
#include <cstdlib> // For srand()
#include <ctime>   // For time()

int main() {
    // Initialize random seed
    srand(static_cast<unsigned int>(time(NULL)));

    Game game;
    game.run();

    return 0;
}