# Snake Game

A simple GUI-based Snake game built using [SFML](https://www.sfml-dev.org/) in C++.

## 🎮 Gameplay

- Control the snake using arrow keys.
- Eat the food to grow longer.
- Avoid colliding with the walls or yourself.
- **Restart**: Press `Enter`, `Space`, or click the text to restart after Game Over.

## 🛠️ Installation

### Prerequisites

- C++ compiler (e.g., `g++`)
- SFML library

### On Ubuntu/Fedora

1. **Install SFML:**

   ```bash
   sudo apt update
   sudo apt install libsfml-dev
   //sudo dnf install SFML-devel

2. **Clone the repository:**

   ```bash
   git clone https://github.com/s-aaahill/Snake.git
   cd Snake
   ```

3. **Compile the game:**

   ```bash
   g++ -o snake main.cpp Game.cpp Snake.cpp Food.cpp -lsfml-graphics -lsfml-window -lsfml-system
   ```

4. **Run the game:**

   ```bash
   ./snake
   ```
## 📁 Project Structure

* `main.cpp` – Entry point of the application.
* `Game.hpp/cpp` – Manages game logic and loop.
* `Snake.hpp/cpp` – Handles snake behavior and rendering.
* `Food.hpp/cpp` – Manages food generation and rendering.
* `Common.hpp` – Contains shared constants and configurations.

## 🚀 Features

* Smooth snake movement.
* Random food placement.
- Collision detection for walls and self.
- Game Over screen with restart option.
* Score tracking (if implemented).

## 🧩 Future Enhancements

* Add a scoring system.
* Implement different difficulty levels.
* Introduce sound effects.
* Create a start menu.
