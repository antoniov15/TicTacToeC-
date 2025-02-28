#include "TicTacToe.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

TicTacToe::TicTacToe() {
	// Initialize 3x3 board with empty spaces
	board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
	currentPlayer = 'X'; // X goes first
	gameOver = false;
	humanPlayer = 'X';
	aiPlayer = 'O';
	difficulty = 3;
	playerWins = 0;
	aiWins = 0;
	draws = 0;
	boardSize = 3;
	winLength = 3;

	// Initialize board with empty spaces
	board = std::vector<std::vector<char>>(boardSize, std::vector<char>(boardSize, ' '));

	//Seed the random number generator
	srand(static_cast<unsigned int>(time(NULL)));
}

TicTacToe::TicTacToe(int size) {
	currentPlayer = 'X'; // X goes first
	gameOver = false;
	humanPlayer = 'X';
	aiPlayer = 'O';
	difficulty = 3;
	playerWins = 0;
	aiWins = 0;
	draws = 0;

	// Set board size
	setBoardSize(size);

	// Seed the random number generator
	srand(static_cast<unsigned int>(time(NULL)));
}

// Display the game board
void TicTacToe::displayBoard() {
	std::cout << "\n";

	// Print column numbers
	std::cout << "  ";
	for (int j = 0; j < boardSize; j++) {
		std::cout << "  " << j << " ";
	}
	std::cout << " (columns)\n";

	// Print top border
	std::cout << "  +";
	for (int j = 0; j < boardSize; j++) {
		std::cout << "---";
		if (j < boardSize - 1) std::cout << "+";
	}
	std::cout << "+\n";

	// Print board
	for (int i = 0; i < boardSize; i++) {
		// Print row number
		std::cout << i << " ";

		// Print row contents
		for (int j = 0; j < boardSize; j++) {
			std::cout << "| " << board[i][j] << " ";
		}
		std::cout << "|\n";

		// Print row separator (except after the last row)
		if (i < boardSize - 1) {
			std::cout << "  +";
			for (int j = 0; j < boardSize; j++) {
				std::cout << "---";
				if (j < boardSize - 1) std::cout << "+";
			}
			std::cout << "+\n";
		}
	}

	// Print bottom border
	std::cout << "  +";
	for (int j = 0; j < boardSize; j++) {
		std::cout << "---";
		if (j < boardSize - 1) std::cout << "+";
	}
	std::cout << "+\n";

	std::cout << "(rows)\n\n";
}

// Make a move
bool TicTacToe::makeMove(int row, int col) {
	//row--;
	//col--;
	
	// Check if the move is valid
	if (row < 0 || row >= boardSize || col < 0 || col >= boardSize || board[row][col] != ' ' || gameOver) {		
		return false;
	}

	// Make the move
	board[row][col] = currentPlayer;

	// Check for win or draw
	if (checkWin()) {
		displayBoard();
		if (currentPlayer == humanPlayer) {
			playerWins++;
			std::cout << "Player " << currentPlayer << " wins!\n";

		}
		else {
			aiWins++;
			std::cout << "AI wins!\n";
		}
		gameOver = true;
	}
	else if (checkDraw()) {
		displayBoard();
		draws++;
		std::cout << "It's a draw!\n";
		gameOver = true;
	}
	else {
		// Switch player
		currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
	}

	return true;
}

bool TicTacToe::checkWin() {
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
bool TicTacToe::checkDraw() {
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
bool TicTacToe::isGameOver() {
	return gameOver;
}

// Get current player
char TicTacToe::getCurrentPlayer() {
	return currentPlayer;
}

// Set player types
void TicTacToe::setPlayerTypes(char human, char ai) {
	humanPlayer = human;
	aiPlayer = ai;
}

// Set AI difficulty
void TicTacToe::setDifficulty(int level) {
	if (level >= 1 && level <= 3) {
		difficulty = level;
	}
}

// AI move using minimax algorithm
void TicTacToe::aiMove() {
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
void TicTacToe::makeRandomMove() {
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
void TicTacToe::makeOptimalMove() {
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
int TicTacToe::minimax(std::vector<std::vector<char>>& board, int depth, bool isMaximizing) {
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
bool TicTacToe::checkWinForPlayer(char player) {
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
bool TicTacToe::isBoardFull() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') {
				return false;
			}
		}
	}
	return true;
}

// Display game statistics
void TicTacToe::displayStats() {
	std::cout << "\n===== GAME STATISTICS =====\n";
	std::cout << "Player wins: " << playerWins << "\n";
	std::cout << "AI wins: " << aiWins << "\n";
	std::cout << "Draws: " << draws << "\n";

	int totalGames = playerWins + aiWins + draws;
	if (totalGames > 0) {
		double winRate = static_cast<double>(playerWins) / totalGames * 100;
		std::cout << "Your win rate: " << winRate << "%\n";
	}
	std::cout << "==========================\n";
}

// Reset the game board for a new game
void TicTacToe::resetGame() {
	// Clear the board
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			board[i][j] = ' ';
		}
	}

	// Reset game state
	currentPlayer = 'X';
	gameOver = false;
}

void TicTacToe::setBoardSize(int size)
{
	// Validate size
	if (size < 3) size = 3;
	if (size > 5) size = 5;

	boardSize = size;

	// Set win length based on bord size
	if (size == 3) {
		winLength = 3;
	}
	else if (size == 4) {
		winLength = 4;
	}
	else {
		winLength = 5;
	}

	// Resize the board
	board.resize(boardSize);
	for (int i = 0; i < boardSize; ++i) {
		board[i].resize(boardSize, ' ');
	}
}

int TicTacToe::getBoardSize() const {
	return boardSize;
}
