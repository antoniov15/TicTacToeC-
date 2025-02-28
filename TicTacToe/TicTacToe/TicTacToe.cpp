#include "TicTacToe.h"
#include <iostream>

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

	//Seed the random number generator
	srand(static_cast<unsigned int>(time(NULL)));
}

// Display the game board
void TicTacToe::displayBoard() {
	std::cout << "\n";
	std::cout << "  0 1 2\n";
	for (int i = 0; i < 3; i++) {
		std::cout << i << " ";
		for (int j = 0; j < 3; j++) {
			std::cout << board[i][j];
			if (j < 2) std::cout << "|";
		}
		std::cout << "\n";
		if (i < 2) std::cout << "  -+-+-\n";
	}
	std::cout << "\n";
}

// Make a move
bool TicTacToe::makeMove(int row, int col) {
	// Check if the move is valid
	if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ' || gameOver) {
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