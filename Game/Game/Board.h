#pragma once
class Board
{
public:
	Board();	 // constructor
	~Board();	// destructor
private:
	char board [8][8];
public:
	void initBoard();
	void display();
	void makeMove(char color, char column, int row);
	bool isValidMove(char color, char column, int row);
	bool flipNorth, flipSouth, flipWest, flipEast = false;
};

