// MineSweeper Command Line Editon.cpp : This file contains the 'main' function. Program execution begins and ends there \\

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BOARD_SIZE = 11;
const int NUM_MINES = 15; 

// Function to initalize the board with the bombs
void  initializeBoard(vector<vector<char>> &board, vector<vector<bool>> &mineLocations) {
    // Initialize the board with empty cells
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board.push_back(vector<char>(BOARD_SIZE, ' '));
    }


    // Initialize mineLocations with false
    mineLocations.assign(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));
    

    // Randomly place mines on the board
    int minesPlaced = 0;
    while (minesPlaced < NUM_MINES) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;
        if (!mineLocations[row][col]) {
            mineLocations[row][col] = true;
            minesPlaced++;
        }
    }
}


// Create the Function to Spit Out the Board
void printBoard(const vector<vector<char>>& board) {
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to count the number of mines adjacent to a cell
int countAdjacentMines(const vector<vector<bool>>& mineLocations, int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
                if (mineLocations[newRow][newCol]) {
                    count++;
                }
            }
        }
    }
    return count;
}

// Function to reveal a cell 
void revealCell(vector<vector<char>>& board, const vector<vector<bool>>& mineLocations, int row, int col) {
    if (board[row][col] == ' ') {
        int mines = countAdjacentMines(mineLocations, row, col);
        if (mines > 0) {
            board[row][col] = '0' + mines;
        }
        else {
            board[row][col] = '-';
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int newRow = row + i;
                    int newCol = col + j;
                    if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
                        revealCell(board, mineLocations, newRow, newCol);
                    }
                }
            }
        }
    }
}

int main() {
    srand(time(nullptr));

    vector<vector<char>> board;
    vector<vector<bool>> mineLocations;

    initializeBoard(board, mineLocations);

    bool gameover = false;

    while (!gameover) {
        printBoard(board);

        int row, col;
        cout << "Enter row and column (separated by space): ";
        cin >> row >> col;

        if (mineLocations[row][col]) {
            cout << "Game Over! You hit a mine." << endl;
            gameover = true;
        }
        else {
            revealCell(board, mineLocations, row, col);

            // Check if all non-mine cells are revealed
            int unrevealedCells = 0;
            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    if (board[i][j] == ' ') {
                        unrevealedCells++;
                    }
                }
            }

            if (unrevealedCells == NUM_MINES) {
                cout << "Congratulations! You won!" << endl;
                gameover = true;
            }
        }
    }

    printBoard(board);

    return 0;
}

