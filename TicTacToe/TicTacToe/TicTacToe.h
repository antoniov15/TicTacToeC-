#pragma once

/*TO DO*/

#include <vector>

class TicTacToe {
private:
	std::vector<std::vector<char>> board; // Tic Tac Toe board
	char currentPlayer; // X or O
	bool gameOver; // True if game is over
	char aiPlayer; // AI player
	char humanPlayer; // Human player
	int difficulty; // AI difficulty 1=easy, 2=medium, 3=hard
	int playerWins;
	int aiWins;
	int draws;
	int boardSize; // Size of the board (3, 4 or 5)
	int winLength; // Member of markers in a row needed to win

public:
	/// Constructor
	TicTacToe();

	/// Constructor with boardsize
	TicTacToe(int size);

	/// Methods
	// Display the game board
	void displayBoard();
	
	// Make a move
	bool makeMove(int row, int col);

	// Check for win
	bool checkWin();
	
	// Check if the game is a draw
	bool checkDraw();
	
	// Check if game is over
	bool isGameOver();
	
	// Get current player
	char getCurrentPlayer();
	
	// Set player types
	void setPlayerTypes(char human, char ai);

	// Set AI difficulty
	void setDifficulty(int level);
	
	// AI move using minimax algorithm
	void aiMove();
	
	// Make a random valid move
	void makeRandomMove();
	
	// Make the optimal move using minimax
	void makeOptimalMove();
	
	// Minimax algorithm
	int minimax(std::vector<std::vector<char>>& board, int depth, bool isMaximizing, int depthMax);
	
	int evaluateBoard();

	char getOpponent(char player);

	// Check win for player
	bool checkWinForPlayer(char player);

	// Check if the board is full
	bool isBoardFull();

	// Display game statistics
	void displayStats();

	// Reset the game board for a new game
	void resetGame();

	// Set the board size
	void setBoardSize(int size);

	// Get board size
	int getBoardSize() const;
};