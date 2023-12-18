#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BOARD_SIZE = 10;

class Ship {
public:
    Ship(int size) : size(size), hits(0) {}

    int getSize() const {
        return size;
    }

    bool isSunk() const {
        return hits == size;
    }

    void hit() {
        ++hits;
    }

private:
    int size;
    int hits;
};

class Player {
public:
    Player(const string& name) : name(name), board(BOARD_SIZE, vector<char>(BOARD_SIZE, ' ')), score(0) {}

    const string& getName() const {
        return name;
    }

    void placeShips() {
        for (int i = 1; i <= 5; ++i) {
            placeShip(i);
        }
    }

    void attack(Player& opponent) {
        int x, y;
        cout << name << ", enter attack coordinates (row and column): ";
        cin >> x >> y;

        if (isValidMove(x, y)) {
            char result = opponent.receiveAttack(x, y);
            displayAttackResult(x, y, result);
        }
        else {
            cout << "Invalid move. Try again." << endl;
            attack(opponent); // Recursive call until a valid move is entered
        }
    }

    void displayBoard() const {
        cout << " " << "0123456789" << endl;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            cout << i;
            for (int j = 0; j < BOARD_SIZE; ++j) {
                cout << board[i][j];
            }
            cout << endl;
        }
    }

    int getScore() const {
        return score;
    }

private:
    void placeShip(int size) {
        int x, y;
        char orientation;

        cout << name << ", place a ship of size " << size << " (row, column, orientation - H or V): ";
        cin >> x >> y >> orientation;

        if (isValidPlacement(x, y, size, orientation)) {
            if (orientation == 'H') {
                for (int i = 0; i < size; ++i) {
                    board[x][y + i] = 'S';
                }
            }
            else {
                for (int i = 0; i < size; ++i) {
                    board[x + i][y] = 'S';
                }
            }
        }
        else {
            cout << "Invalid placement. Try again." << endl;
            placeShip(size); // Recursive call until a valid placement is entered
        }
    }

    bool isValidPlacement(int x, int y, int size, char orientation) const {
        if (orientation == 'H') {
            return y + size <= BOARD_SIZE && allSpacesEmpty(x, y, size, orientation);
        }
        else {
            return x + size <= BOARD_SIZE && allSpacesEmpty(x, y, size, orientation);
        }
    }

    bool allSpacesEmpty(int x, int y, int size, char orientation) const {
        if (orientation == 'H') {
            for (int i = 0; i < size; ++i) {
                if (board[x][y + i] != ' ') {
                    return false;
                }
            }
        }
        else {
            for (int i = 0; i < size; ++i) {
                if (board[x + i][y] != ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    char receiveAttack(int x, int y) {
        if (board[x][y] == 'S') {
            board[x][y] = 'X';
            score++;
            return 'X'; // Hit
        }
        else {
            board[x][y] = 'O';
            return 'O'; // Miss
        }
    }

    bool isValidMove(int x, int y) const {
        return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && board[x][y] == ' ';
    }

    void displayAttackResult(int x, int y, char result) const {
        cout << "Result of the attack at (" << x << ", " << y << "): ";
        if (result == 'X') {
            cout << "Hit!" << endl;
        }
        else {
            cout << "Miss!" << endl;
        }
    }

    string name;
    vector<vector<char>> board;
    int score;
};

class BattleshipGame {
public:
    void run() {
        cout << "Welcome to Battleship Game!" << endl;

        // Set up players
        Player player1("Player 1");
        Player player2("Player 2");

        // Place ships on the board
        player1.placeShips();
        player2.placeShips();

        // Game loop
        while (true) {
            cout << endl << "Player 1's turn:" << endl;
            player1.attack(player2);
            player2.displayBoard();
            if (gameOver(player2)) {
                cout << "Player 1 wins!" << endl;
                break;
            }

            cout << endl << "Player 2's turn:" << endl;
            player2.attack(player1);
            player1.displayBoard();
            if (gameOver(player1)) {
                cout << "Player 2 wins!" << endl;
                break;
            }
        }
    }

private:
    bool gameOver(const Player& player) const {
        return player.getScore() == 17; // All ships are sunk
    }
};

int main() {
    BattleshipGame game;
    game.run();

    return 0;
}
