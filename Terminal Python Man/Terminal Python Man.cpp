// Terminal Python Man.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <conio.h>

using namespace std;

const int width = 20;
const int height = 10;

int PythonmanX, PythonmanY;
int ghoulX, ghoulY;
int foodX, foodY;
bool gameOver;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	PythonmanX = width / 2;
	PythonmanY = height / 2;
	ghoulX = rand() % width;
	ghoulY = rand() % height;
	foodX = rand() % width;
	foodY = rand() % height;
}

void Python() {
	system("cls"); // Erase the Command Line

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#"; // left wall


			if (i == PythonmanY && j == PythonmanX)
				cout << "P"; // Python-Man
			else if (i == ghoulY && j == ghoulX)
				cout << "G"; // Ghoul
			else if (i == foodY && j == foodX)
				cout << "F"; // Food
			else
				cout << " ";

			if (j == width - 1)
				cout << "#"; // right wall

		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
}

void Movement() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}



void Logic() {
	switch (dir) {
	case LEFT:
		PythonmanX--;
		break;
	case RIGHT:
		PythonmanX++;
		break;
	case UP:
		PythonmanY--;
		break;
	case DOWN:
		PythonmanY++;
		break;
	default:
		break;
	}

	if (PythonmanX < 0) PythonmanX = width - 1;
	if (PythonmanX >= width) PythonmanX = 0;
	if (PythonmanY < 0) PythonmanY = height - 1;
	if (PythonmanY >= height) PythonmanY = 0;

	if (PythonmanX == ghoulX && PythonmanY == ghoulY)
		gameOver = true;

	if (PythonmanX == foodX && PythonmanY == foodY) {
		foodX = rand() % width;
		foodY = rand() % height;
	}
}

int main() {
	Setup();
	while (!gameOver) {
		Python();
		Movement();
		Logic();
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
