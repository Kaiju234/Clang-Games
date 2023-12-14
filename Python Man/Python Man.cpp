#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <xkeycheck.h>

using namespace std;

const int width = 20;
const int height = 10;

int pymanX, pymanY;
int fruitX, fruitY;
int score;

enum Direction
{
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
Direction dir;

void Setup()
{
	pymanX = width / 2;
	pymanY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	dir = STOP;
}

void Draw()
{
	system("cls");

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#"; // Wall
			if (i == pymanY && j == pymanX)
				cout << "C"; // Python Man
			else if (i == fruitY && j == fruitX)
				cout << "F"; // Fruit
			else
				cout << " ";
			if (j == width - 1)
				cout << "#"; // Wall
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	
	cout << endl;

	cout << "Score:" << score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
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
			dir = STOP;
			break;
		case 27: // ASCII code for escape key
			exit(0);
		}
	}
}

void Logic()
{
	switch (dir)
	{
	case LEFT:
		pymanX--;
		break;
	case RIGHT:
		pymanX++;
		break;
		case UP:
		pymanY--;
		break;
	case DOWN:
		pymanY++;
		break;
	default:
		break;
	}

	if (pymanX < 0)
		pymanX = width - 1;
	else if (pymanX >= width)
		pymanX = 0;

	if (pymanY < 0)
		pymanY = height - 1;
	else if (pymanY >= height)
		pymanY = 0;

	if (pymanX == fruitX && pymanY == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}
}

int main()
{
	Setup();

	while (true)
	{
		Draw();
		Input();
		Logic();
		// Add delay or sleep here for controlling the speed of the game
	}

	return 0;
}