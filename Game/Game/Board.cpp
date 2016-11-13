#include "stdafx.h"
#include "Board.h"
#include <iostream>

using namespace std;

Board::Board()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board[i][j] = ' ';

	// then
	board[4][4] = 'B';
	board[5][5] = 'B';
	board[5][4] = 'W';
	board[4][5] = 'W';

	display();
}

void Board::display()
{
	cout << endl << "Game board: " << endl;
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
			cout << board[r][c] << "|";
		cout << endl << " - - - - - - - - " << endl;	// indicate grid 
	}
	cout << endl;
} 

void Board::makeMove(char color, char row, int column)
{
	int newrow = row - '0';
	board[newrow][column] = color;
	// flip pieces
}

bool Board::isValidMove(char row, int column)
{
	return (row >= 'A' && row <= 'H'
		&& column >= 1 && column <= 8);
}

Board::~Board()
{
	delete[] board;
}
