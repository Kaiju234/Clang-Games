#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

class Asteroid {
public:
	int x, y;

    Asteroid(int startX, int startY) : x(startX), y(startY) {}

    void move() {
        y++;
    }
};

class Spaceship {
public:
    int x, y;

    Spaceship(int startX, int startY) : x(startX), y(startY) {}

    void moveLeft() {
        x--;
    }

    void moveRight() {
        x++;
    }
};

int main() {
    const int width = 20;
    const int height = 10;


    Spaceship ship(width / 2, height - 1);
    vector<Asteroid> asteroids;

    srand(time(0));

    while (true) {
        system("CLS"); // Clear the console

        // Move spaceship
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
            case 'a':
                ship.moveLeft();
                break;
            case 'd':
                ship.moveRight();
                break;
            }
        }

        // Move asteroids
        for (size_t i = 0; i < asteroids.size(); i++) {
            asteroids[i].move();
            if (asteroids[i].y == height) {
                asteroids.erase(asteroids.begin() + i);
                i--;
            }
        }

        // Spawn new asteroids
        if (rand() % 10 == 0) {
            asteroids.push_back(Asteroid(rand() % width, 0));
        }

        // Check for collisions
        for (size_t i = 0; i < asteroids.size(); i++) {
            if (asteroids[i].x == ship.x && asteroids[i].y == ship.y) {
                cout << "Game Over!" << endl;
                return 0;
            }
        }

        // Draw the game
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == ship.y && j == ship.x) {
                    cout << "S"; // Spaceship
                }
                else {
                    bool asteroidExists = false;
                    for (size_t k = 0; k < asteroids.size(); k++) {
                        if (asteroids[k].x == j && asteroids[k].y == i) {
                            cout << "A"; // Asteroid
                            asteroidExists = true;
                            break;
                        }
                    }
                    if (!asteroidExists) {
                        cout << " ";
                    }
                }
            }
            cout << endl;
        }

        // Slow down the game loop
        for (int i = 0; i < 10000000; i++) {}

    }

    return 0;
}