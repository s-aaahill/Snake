Snake Game
A simple GUI-based Snake game built using SFML in C++.

🎮 Gameplay
Control the snake using arrow keys.

Eat the food to grow longer.

Avoid colliding with the walls or yourself.
GitHub

🛠️ Installation
Prerequisites
C++ compiler (e.g., g++)

SFML library

On Ubuntu
Install SFML:

bash
Copy
Edit
sudo apt update
sudo apt install libsfml-dev
Clone the repository:

bash
Copy
Edit
git clone https://github.com/s-aaahill/Snake.git
cd Snake
Compile the game:

bash
Copy
Edit
g++ -o snake main.cpp Game.cpp Snake.cpp Food.cpp -lsfml-graphics -lsfml-window -lsfml-system
Run the game:

bash
Copy
Edit
./snake
📁 Project Structure
main.cpp – Entry point of the application.

Game.hpp/cpp – Manages game logic and loop.

Snake.hpp/cpp – Handles snake behavior and rendering.

Food.hpp/cpp – Manages food generation and rendering.

Common.hpp – Contains shared constants and configurations.
GitHub

🚀 Features
Smooth snake movement.

Random food placement.

Collision detection for walls and self.

Score tracking (if implemented).

🧩 Future Enhancements
Add a scoring system.

Implement different difficulty levels.

Introduce sound effects.

Create a start menu and game over screen.
YouTube
+2
GitHub Docs
+2
GitHub Docs
+2
GitHub Docs
+2
YouTube
+2
YouTube
+2
