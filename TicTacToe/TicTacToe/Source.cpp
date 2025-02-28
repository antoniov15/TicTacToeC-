#include <iostream>
#include <limits>

#include "TicTacToe.h"

// Function to clear the input buffer after invalid input
void clearInputBuffer() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Function to get a valid integer input form user within a specified range
int getValidInput(int min, int max) {
    int input;

    while (true) {
        std::cin >> input;
        if (std::cin.fail() || input < min || input > max) {
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
            clearInputBuffer();
        }
        else {
            break;
        }
    }
    return input;
}

int main() {
    TicTacToe game;
    int row, col;
	int gameMode;
    int difficulty = 3;
    char playAgain = 'y';
    int boardSize = 3;

    std::cout << "=================================\n";
    std::cout << "       TIC TAC TOE GAME         \n";
    std::cout << "=================================\n\n";

    while (playAgain == 'y' || playAgain == 'Y') {
        // Board size selection
        std::cout << "Choose board size:\n";
        std::cout << "1. 3x3 (Classic)\n";
        std::cout << "2. 4x4\n";
        std::cout << "3. 5x5\n";
        std::cout << "Enter your choice (1-3): ";
        int sizeChoice = getValidInput(1, 3);

        // Set the board size
        switch (sizeChoice) {
        case 1: boardSize = 3; break;
        case 2: boardSize = 4; break;
        case 3: boardSize = 5; break;
        default: boardSize = 3;
        }
        game.setBoardSize(boardSize);
        
        // Reset game for a new round
        game.resetGame();

        // Game mode selection
        std::cout << "Choose game mode:\n";
        std::cout << "1. Player vs Player\n";
        std::cout << "2. Player vs AI\n";
        std::cout << "Enter your choice (1 or 2): ";
        gameMode = getValidInput(1, 2);

        // If AI mode, set difficulty
        if (gameMode == 2) {
            std::cout << "Choose AI difficulty:\n";
            std::cout << "1. Easy\n";
            std::cout << "2. Medium\n";
            std::cout << "3. Hard\n";
            std::cout << "Enter your choice (1-3): ";
            difficulty = getValidInput(1, 3);
            game.setDifficulty(difficulty);
        }

        std::cout << "\nGame starts! Enter row and column (0-" << boardSize - 1 << ") to make a move.\n";

        // Main game loop
        while (!game.isGameOver()) {
            game.displayBoard();

            if (gameMode == 1 || game.getCurrentPlayer() == 'X') {
                // Human player's turn
                std::cout << "Player " << game.getCurrentPlayer() << "'s turn.\n";
                std::cout << "Enter row: ";
                row = getValidInput(0, boardSize - 1);
                std::cout << "Enter column: ";
                col = getValidInput(0, boardSize - 1);

                if (!game.makeMove(row, col)) {
                    std::cout << "That position is already taken! Try again.\n";
                }
            }
            else {
                // AI's turn
                std::cout << "AI is thinking...\n";
                game.aiMove();
            }
        }

        // Display final result
        game.displayStats();

        // Ask if player wants to play again
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playAgain;
    }

    std::cout << "\nThanks for playing Tic Tac Toe!\n";
    return 0;
}