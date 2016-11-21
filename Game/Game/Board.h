#pragma once
class Board
{
public:
	Board();	// constructor
	~Board();	// destructor
private:
	char currentBoard[8][8];	// current state of the board
	char previousBoard[8][8];	// previous state of the board (backs up the last move)
	bool flipNorth, flipSouth, flipWest, flipEast, flipNW, flipNE, flipSW, flipSE;
	int spacesRemain, skipCount;
public:
	void initBoard();
	void display();
	void makeMove(char color, char column, int row);
	void unmakeMove();
	//void keepMove(char column, int row);
	bool isValidMove(char color, char column, int row);
	//int minimax(int level, int depth);
	//int SEF(char color);
	char scoreGame();
	bool endGame();
	//struct {		// saves best move found by minimax search
	//	int row;	
	//	char column;
	//} AIBestMove;
};
