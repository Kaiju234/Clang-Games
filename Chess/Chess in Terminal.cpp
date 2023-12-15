#include <iostream>
#include <vector>

using namespace std;

// Define the chess board
char board[8][8];

// function to initialize the board
void initializeBoard() {
    char initialPosition[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = initialPosition[i][j];
        }
    }
}

// Function to display the chess board
void displayBoard() {
    cout << "a b c d e f g h" << endl;
    for (int i = 0; i < 8; ++i) {
        cout << 8 - i << " ";
        for (int j = 0; j < 8; ++j) {
            cout << board[i][j] << " ";
        }
        cout << 8 - i << endl;
    }
    cout << "  a b c d e f g h" << endl;
}

// Function to check if a move is within the bounds of the board
bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) {
    return fromRow >= 0 && fromRow < 8 && fromCol >= 0 && fromCol < 8 &&
        toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8;
}

// Function to move a piece on the board
void movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    if (isValidMove(fromRow, fromCol, toRow, toCol)) {
        board[toRow][toCol] = board[fromRow][fromCol];
        board[fromRow][fromCol] = ' ';
    }
}

// Function to get player input for a move
void getPlayerMove() {
    string move;
    cout << "Enter your move (e.g., 'e2 e4'): ";
    cin >> move;

   // Convert algebraic notation to array indices
    int fromCol = move[0] - 'a';
    int fromRow = 8 - (move[1] - '0');
    int toCol = move[3] - 'a';
    int toRow = 8 - (move[4] - '0');

    // Make the move if it's valid
    if (isValidMove(fromRow, fromCol, toRow, toCol)) {
        movePiece(fromRow, fromCol, toRow, toCol);
    }
    else {
        cout << "Invalid move. Try again." << endl;
        getPlayerMove();
    }
}

int main() {
    initializeBoard();

    while (true) {
        displayBoard();
        getPlayerMove();
    }

    return 0;
}
