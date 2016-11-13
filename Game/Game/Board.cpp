#include "stdafx.h"
#include "Board.h"
#include <iostream>

using namespace std;

Board::Board()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board[i][j] = ' ';
}

void Board::initBoard()
{
	board[3][3] = 'B';
	board[4][4] = 'B';
	board[4][3] = 'W';
	board[3][4] = 'W';
}

void Board::display()
{
	cout << endl << "Game board: " << endl << endl;
	cout << "    A B C D E F G H " << endl;		// indicate board cells
	cout << "    - - - - - - - - " << endl;		// indicate grid 
	for (int r = 0; r < 8; r++)
	{
		cout << " " << r + 1 << " ";
		for (int c = 0; c < 8; c++)
			cout << "|" << board[r][c];
		cout << "|";
		cout << endl << "    - - - - - - - - " << endl;	// indicate grid 
	}
	cout << endl;
} 

void Board::makeMove(char color, char row, int column)
{
	int newrow = row - 0x41;	// convert character to numerical
	board[newrow][column-1] = color;	// user enters columns 1-8; program needs 0-7
	// and flip pieces...
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
