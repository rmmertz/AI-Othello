#pragma once
class Board
{
public:
	Board();	 // constructor
	~Board();	// destructor
private:
	char board[8][8];
public:
	char aiBestMoveColor;
	char aiBestMoveCol;
	int aiBestMoveRow;
	int aiBestMoveScore;
	void initBoard();
	void display();
	void makeMove(char color, char column, int row);
	bool isValidMove(char color, char column, int row);
	void aiSearch(char color);
	char scoreGame();
	bool endGame();
	bool flipNorth, flipSouth, flipWest, flipEast, flipNW, flipNE, flipSW, flipSE;
	bool gameOver;
	int spacesRemain, skipCount, state;
};
