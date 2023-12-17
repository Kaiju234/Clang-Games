#include <iostream>
#include <conio.h> // For _getch() on Windows

using namespace std;

const int width = 20;
const int height = 10;

int birdX = 4;
int birdY = height / 2;
int score = 0;

bool gameover = false;

int pipeX = width - 1;
int pipeHoleY = height / 2;
const int pipeWidth = 2;

void draw() {
    system("cls"); // Clear the console

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == birdX && i == birdY)
                cout << "O"; // Draw bird
            else if (j == pipeX && (i < pipeHoleY || i >= pipeHoleY + pipeWidth))
                cout << "|"; // Draw pipe
            else
                cout << " ";
        }
        cout << endl;
    }

    cout << "Score: " << score << endl;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case ' ':
            birdY -= 2; // Jump when space key is pressed
            break;
        case 'q':
            gameover = true; // Quit the game when 'q' is pressed
            break;
        }
    }
}

void update() {
    pipeX--;

    if (pipeX == birdX) {
        if (!(birdY >= pipeHoleY && birdY < pipeHoleY + pipeWidth))
            gameover = true; // Game over if bird hits pipe
        else
            score++;
    }

    if (pipeX < 0) {
        pipeX = width - 1;
        pipeHoleY = rand() % (height - pipeWidth);
    }

    birdY++;

    if (birdY >= height || birdY < 0)
        gameover = true; // Game over if bird hits top or bottom
}

int main() {
    while (!gameover) {
        draw();
        input();
        update();
    }

    cout << "Game Over. Your score: " << score << endl;

    return 0;
}
       