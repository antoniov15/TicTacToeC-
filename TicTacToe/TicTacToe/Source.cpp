#include <iostream>
#include <limits>

#include "TicTacToe.h"

/*class TicTacToe {
private:
	std::vector<std::vector<char>> board; //tic tac toe board
	char currentPlayer; // X or O
	bool gameOver; // True if game is over
	char aiPlayer; // AI player
	char humanPlayer; // Human player
	int difficulty; // AI difficulty 1=easy, 2=medium, 3=hard

public:
    // Constructor
    TicTacToe() {
        // Initialize 3x3 board with empty spaces
        board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
        currentPlayer = 'X'; // X goes first
        gameOver = false;
        humanPlayer = 'X';
        aiPlayer = 'O';
        difficulty = 3;

		// Seed the random number generator
		srand(time(NULL));
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

    // Set player types
    void setPlayerTypes(char human, char ai) {
        humanPlayer = human;
        aiPlayer = ai;
    }

	void setDifficulty(int level) {
		if (level >= 1 && level <= 3) {
			difficulty = level;
		}
	}
    
    // AI move using minimax algorithm
    void aiMove() {
        if (gameOver) return;

        // Random chance to make the AI sub-optimal based on difficulty level
        int randomChance = rand() % 10; // Random number between 0 and 9

        if (difficulty == 1 && randomChance < 7) {
            // Easy: 70% chance to make a random move
            makeRandomMove();
            return;
        }
        else if (difficulty == 2 && randomChance < 3) {
            // Medium: 30% chance to make a random move
            makeRandomMove();
            return;
        }
        else {
            // Hard: Always optimal (or at lower difficulties when random chance doesn't trigger)			
            makeOptimalMove();
        }
    }

    // Make a random valid move
    void makeRandomMove() {
        std::vector<std::pair<int, int>> availableMoves;

        // Find all available moves
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    availableMoves.push_back(std::make_pair(i, j));
                }
            }
        }

        if (!availableMoves.empty()) {
            // Choose a random move
            int randomIndex = rand() % availableMoves.size();
            int row = availableMoves[randomIndex].first;
            int col = availableMoves[randomIndex].second;

            std::cout << "AI randomly chooses position: " << row << ", " << col << std::endl;
            makeMove(row, col);
        }
    }

    // Make the optimal move using minimax
    void makeOptimalMove() {
        int bestScore = -1000;
        int bestRow = -1;
        int bestCol = -1;

        // Try all possible moves and choose the best one
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    // Make the move
                    board[i][j] = currentPlayer;

                    // Calculate score for this move
                    int score = minimax(board, 0, false);

                    // Undo the move
                    board[i][j] = ' ';

                    // Update best move if better score found
                    if (score > bestScore) {
                        bestScore = score;
                        bestRow = i;
                        bestCol = j;
                    }
                }
            }
        }

        // Make the best move
        std::cout << "AI optimally chooses position: " << bestRow << ", " << bestCol << std::endl;
        makeMove(bestRow, bestCol);
    }

    // Minimax algorithm
    int minimax(std::vector<std::vector<char>>& board, int depth, bool isMaximizing) {
        // Check terminal states
        if (checkWinForPlayer(aiPlayer)) {
            return 10 - depth; // AI wins (higher score for quicker wins)
        }
        if (checkWinForPlayer(humanPlayer)) {
            return depth - 10; // Human wins (lower score)
        }
        if (isBoardFull()) {
            return 0; // Draw
        }

        if (isMaximizing) {
            // AI's turn (maximizing player)
            int bestScore = -1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = aiPlayer;
                        int score = minimax(board, depth + 1, false);
                        board[i][j] = ' ';
                        bestScore = std::max(score, bestScore);
                    }
                }
            }
            return bestScore;
        }
        else {
            // Human's turn (minimizing player)
            int bestScore = 1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = humanPlayer;
                        int score = minimax(board, depth + 1, true);
                        board[i][j] = ' ';
                        bestScore = std::min(score, bestScore);
                    }
                }
            }
            return bestScore;
        }
    }

    // Check if a specific player has won
    bool checkWinForPlayer(char player) {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < 3; i++) {
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
                return true;
            }
        }

        // Check diagonals
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
            return true;
        }
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
            return true;
        }

        return false;
    }

    // Check if the board is full
    bool isBoardFull() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
};*/

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
        return input;
    }
}

int main() {
    TicTacToe game;
    int row, col;
	int gameMode;
    int difficulty = 3;
    char playAgain = 'y';

    std::cout << "=================================\n";
    std::cout << "       TIC TAC TOE GAME         \n";
    std::cout << "=================================\n\n";

    while (playAgain == 'y' || playAgain == 'Y') {
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

        std::cout << "\nGame starts! Enter row and column (0-2) to make a move.\n";

        // Main game loop
        while (!game.isGameOver()) {
            game.displayBoard();

            if (gameMode == 1 || game.getCurrentPlayer() == 'X') {
                // Human player's turn
                std::cout << "Player " << game.getCurrentPlayer() << "'s turn.\n";
                std::cout << "Enter row: ";
                row = getValidInput(0, 2);
                std::cout << "Enter column: ";
                col = getValidInput(0, 2);

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