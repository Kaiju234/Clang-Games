#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool youSuck;
const int width = 20;
const int height = 10;
int x, y, appleX, appleY, score;
int assX[100], assY[100];
int nAss;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
   youSuck = false;
   dir = STOP;
   x = width / 2;
   y = height / 2;
   appleX = rand() % width;
   appleY = rand() % height;
   score = 0;


}



void Draw()
{
    system("cls"); // Clear the console

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#"; // Left wall

            if (i == y && j == x)
                cout << "O"; // Snake head
            else if (i == appleY && j == appleX)
                cout << ""; // Fruit
            else
            {
                bool printAss = false;
                for (int k = 0; k < nAss; k++)
                {
                    if (assX[k] == j && assY[k] == i)
                    {
                        cout << "o"; // Snake tail
                        printAss = true;
                    }
                }
                if (!printAss)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#"; // Right wall
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
            youSuck = true;
            break;
        }
    }
}


void Algorithm()
{ 
    int prevX = assX[0];
    int prevY = assY[0];
    int prev2X, prev2Y;
    assX[0] = x;
    assY[0] = y;

    for (int i = 1; i < nAss; i++)
    {
        prev2X = assX[i];
        prev2Y = assY[i];
        assX[i] = prevX;
        assY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    
    switch (dir)
    
    {

    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;

    
    }

    
if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;

    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;

    for (int i = 0; i < nAss; i++)
        if (assX[i] == x && assY[i] == y)
            youSuck = true;

     if (x == appleX && y == appleY)
    {
        score += 10;
        appleX = rand() % width;
        appleY = rand() % height;
        nAss++;
    }
}


int main()
{
    Setup();
    while (!youSuck)
    {
        Draw();
        Input();
        Algorithm();
        Sleep(10); // sleep(10) for cross-platform compatibility
    }
    return 0;
}

