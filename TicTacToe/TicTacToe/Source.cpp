#include <iostream>
#include <vector>

class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;
    bool gameOver;

public:
    // Constructor
    TicTacToe() {
        // Initialize 3x3 board with empty spaces
        board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
        currentPlayer = 'X'; // X goes first
        gameOver = false;
    }

    // Display the game board
    void displayBoard() {
        std::cout << "\n";
        for (int i = 0; i < 3; i++) {
            std::cout << " ";
            for (int j = 0; j < 3; j++) {
                std::cout << board[i][j];
                if (j < 2) std::cout << " | ";
            }
            std::cout << "\n";
            if (i < 2) std::cout << "-----------\n";
        }
        std::cout << "\n";
    }

    // Make a move
    bool makeMove(int row, int col) {
        // Check if the move is valid
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ' || gameOver) {
            return false;
        }

        // Make the move
        board[row][col] = currentPlayer;

        // Check for win or draw
        if (checkWin()) {
            displayBoard();
            std::cout << "Player " << currentPlayer << " wins!\n";
            gameOver = true;
        }
        else if (checkDraw()) {
            displayBoard();
            std::cout << "It's a draw!\n";
            gameOver = true;
        }
        else {
            // Switch player
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        return true;
    }

    // Check if current player has won
    bool checkWin() {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) {
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < 3; i++) {
            if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) {
                return true;
            }
        }

        // Check diagonals
        if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) {
            return true;
        }
        if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) {
            return true;
        }

        return false;
    }

    // Check if the game is a draw
    bool checkDraw() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    return false; // If there's an empty space, it's not a draw
                }
            }
        }
        return true; // All spaces filled
    }

    // Check if game is over
    bool isGameOver() {
        return gameOver;
    }

    // Get current player
    char getCurrentPlayer() {
        return currentPlayer;
    }
};

int main() {
    TicTacToe game;
    int row, col;

    std::cout << "Welcome to Tic Tac Toe!\n";
    std::cout << "Enter row (0-2) and column (0-2) to make a move.\n";

    while (!game.isGameOver()) {
        game.displayBoard();
        std::cout << "Player " << game.getCurrentPlayer() << "'s turn. Enter row and column: ";
        std::cin >> row >> col;

        if (!game.makeMove(row, col)) {
            std::cout << "Invalid move! Try again.\n";
        }
    }

    std::cout << "Game over! Thanks for playing!\n";
    return 0;
}