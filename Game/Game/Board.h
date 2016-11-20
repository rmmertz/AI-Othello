#pragma once
class Board
{
public:
	Board();	// constructor
	~Board();	// destructor
private:
	char currentBoard[8][8];	// current state of the board
	char previousBoard[8][8];	// previous state of the board (backs up the last move)
public:
	void initBoard();
	void display();
	void makeMove(char color, char column, int row);
	void unmakeMove();
	//void keepMove(char column, int row);
	bool isValidMove(char color, char column, int row);
	char scoreGame();
	bool endGame();
	bool flipNorth, flipSouth, flipWest, flipEast, flipNW, flipNE, flipSW, flipSE;
	bool gameOver;
	int spacesRemain, skipCount;
	struct {		// saves best move found by minimax search
		int row;	
		char column;
	} AIBestMove;
};
