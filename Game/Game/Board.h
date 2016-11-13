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
	void makeMove(char color, char row, int column);
	bool isValidMove(char row, int column);
};

