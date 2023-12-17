#include <iostream>
#include <vector>

const int BOARD_SIZE = 8;

enum class Piece { EMPTY, RED, BLACK, RED_KING, BLACK_KING };

struct Move {
    int fromRow, fromCol;
    int toRow, toCol;
};

class CheckersGame {
private:
    std::vector<std::vector<Piece>> board;

public:
    CheckersGame() : board(BOARD_SIZE, std::vector<Piece>(BOARD_SIZE, Piece::EMPTY)) {
        // Initialize the starting positions of pieces
        initializeBoard();
    }

    void initializeBoard() {
        // Initialize the pieces on the board
        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                if ((row + col) % 2 == 1 && row < 3) {
                    board[row][col] = Piece::BLACK;
                }
                else if ((row + col) % 2 == 1 && row > BOARD_SIZE - 4) {
                    board[row][col] = Piece::RED;
                }
            }
        }
    }

    void printBoard() const {
        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                switch (board[row][col]) {
                case Piece::EMPTY:
                    std::cout << "- ";
                    break;
                case Piece::RED:
                    std::cout << "R ";
                    break;
                case Piece::BLACK:
                    std::cout << "B ";
                    break;
                case Piece::RED_KING:
                    std::cout << "RK ";
                    break;
                case Piece::BLACK_KING:
                    std::cout << "BK ";
                    break;
                }
            }
            std::cout << std::endl;
        }
    }

    bool isMoveValid(const Move& move) const {
        // Implement the rules for valid moves
        // For simplicity, consider only basic moves without capturing
        return true;
    }

    void makeMove(const Move& move) {
        // Implement the logic to update the board based on the move
        // For simplicity, consider only basic moves without capturing
        Piece piece = board[move.fromRow][move.fromCol];
        board[move.fromRow][move.fromCol] = Piece::EMPTY;
        board[move.toRow][move.toCol] = piece;
    }
};

int main() {
    CheckersGame game;

    // Example: Print the initial board
    game.printBoard();

    // Example: Make a move (you need to implement move validation)
    Move exampleMove = { 2, 1, 3, 0 };
    if (game.isMoveValid(exampleMove)) {
        game.makeMove(exampleMove);
    }
    else {
        std::cout << "Invalid move!" << std::endl;
    }

    // Example: Print the board after the move
    game.printBoard();

    return 0;
}
