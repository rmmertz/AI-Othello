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
	board[4][4] = 'B';	//Change to W for diagonal testing
	board[4][3] = 'W';	//Change to B for diagonal testing
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
			cout << "|" << board[c][r];
		cout << "|";
		cout << endl << "    - - - - - - - - " << endl;	// indicate grid 
	}
	cout << endl;
} 

void Board::makeMove(char color, char column, int row)
{
	int newcol = column - 0x41;	// convert character to numerical
	int newrow = row - 1;

	board[newcol][row - 1] = color;	// user enters columns 1-8; program needs 0-7   (Flipped col/row for correct placement)
	// and flip pieces...

/*	if (flipNorth) {
		//Flip North
		int tempCol = newcol;
		int tempRow = newrow - 1;

		for (tempRow; tempRow >= 1; tempRow--) {
			if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {
				if (color = 'W')
					board[tempCol][tempRow] = 'W';
				else
					board[tempCol][tempRow] = 'B';
			}
			else
				tempRow = 0;
		}
		flipNorth = 0;
	} */
}

bool Board::isValidMove(char color, char column, int row)
{
	int newcol = column - 0x41;							// Convert character to numerical
	int newrow = (row - 1);							// Shift column by 1
	int tempCol, tempRow;
	bool retVal = false;

	//Check if rows and columns are within valid range
	if (newrow < 0 || newrow > 7 || newcol < 0 || newcol > 7) {
		cout << "Invalid Move!" << endl;
		return false;
	}
	//Check if space is presently occupied 
	if (board[newcol][newrow] != ' ') {
		cout << "Invalid Move!" << endl;
		return false;
	}


	// This breaks and returns true at first instance of a valid move. 
	// It does not validate remaining possible moves 

	//Check North
	tempCol = newcol;						
	tempRow = newrow - 1;

	if (tempCol >= 2 && tempCol <= 7 && tempRow >= 2 && tempRow <= 7) {				// Check if temp space exists on board 
		if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempRow -= 1;															// Move to next space above opponents piece
			for (tempRow; tempRow >= 1; tempRow--) {								// Scan to upper edge of board for another player piece
				if (board[tempCol][tempRow] == color) {
					flipNorth = 1;
					retVal = true;
				}
			}
		}
	}

	//Check South 
	tempCol = newcol;							
	tempRow = newrow + 1;

	if (tempCol >= 2 && tempCol <= 7 && tempRow >= 2 && tempRow <= 7) {				// Check if temp space exists on board 
		if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempRow += 1;															// Move to next space below opponents piece
			for (tempRow; tempRow >= 1; tempRow++) {								// Scan to lower edge of board for another player piece
				if (board[tempCol][tempRow] == color) {
					retVal = true;
				}
			}
		}
	}

	//Check West
	tempCol = newcol - 1;										
	tempRow = newrow;

	if (tempCol >= 2 && tempCol <= 7 && tempRow >= 2 && tempRow <= 7) {				// Check if temp space exists on board 
		if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempCol -= 1;															// Move to next space left of opponents piece
			for (tempCol; tempCol >= 1; tempCol--) {								// Scan to left edge of board for another player piece
				if (board[tempCol][tempRow] == color) {
					retVal = true;
				}
			}
		}
	}

	//Check East
	tempCol = newcol + 1;									
	tempRow = newrow;

	if (tempCol >= 2 && tempCol <= 7 && tempRow >= 2 && tempRow <= 7) {				// Check if temp space exists on board 
		if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempCol += 1;															// Move to next space right of opponents piece
			for (tempCol; tempCol >= 1; tempCol++) {								// Scan to right edge of board for another player piece
				if (board[tempCol][tempRow] == color) {
					retVal = true;
				}
			}
		}
	}
/*
	//Check NorthWest
	tempCol = newcol - 1;
	tempRow = newrow - 1;

	if (tempCol >= 2 && tempCol <= 7 && tempRow >= 2 && tempRow <= 7) {				// Check if temp space exists on board 
		if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempRow -= 1;															// Move up and left one space 
			tempCol -= 1;

			if (tempCol > tempRow) {												// Scan using smallest dimensions 
				for (tempRow; tempRow >= 1; tempRow--) {			
					if (board[tempCol][tempRow] == color) {
						retVal = true;
					}
				tempCol -= tempCol;
				}
			}
			else {
				for (tempCol; tempCol >= 1; tempCol--) {
					if (board[tempCol][tempRow] == color) {
						retVal = true;
					}
				tempRow -= tempRow;
				}
			}
		}
	}
	
	//Check NorthEast
	tempCol = newcol + 1;
	tempRow = newrow - 1;

	if (tempCol >= 2 && tempCol <= 7 && tempRow >= 2 && tempRow <= 7) {				// Check if temp space exists on board 
		if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempRow -= 1;															// Move up and left one space 
			tempCol += 1;

			if (tempCol > tempRow) {												// Scan using smallest dimensions 
				for (tempRow; tempRow >= 1; tempRow--) {
					if (board[tempCol][tempRow] == color) {
						retVal = true;
					}
					tempCol += tempCol;
				}
			}
			else {
				for (tempCol; tempCol >= 1; tempCol++) {
					if (board[tempCol][tempRow] == color) {
						retVal = true;
					}
					tempRow -= tempRow;
				}
			}
		}
	}
	
	//Check SouthEast
	tempCol = newcol + 1;
	tempRow = newrow + 1;

	if (tempCol >= 2 && tempCol <= 7 && tempRow >= 2 && tempRow <= 7) {				// Check if temp space exists on board 
		if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempRow += 1;															// Move up and left one space 
			tempCol += 1;

			if (tempCol > tempRow) {												// Scan using smallest dimensions 
				for (tempRow; tempRow >= 1; tempRow++) {
					if (board[tempCol][tempRow] == color) {
						retVal = true;
					}
					tempCol += tempCol;
				}
			}
			else {
				for (tempCol; tempCol >= 1; tempCol++) {
					if (board[tempCol][tempRow] == color) {
						retVal = true;
					}
					tempRow += tempRow;
				}
			}
		}
	}
	
	//Check SouthWest
	tempCol = newcol - 1;
	tempRow = newrow + 1;

	if (tempCol >= 2 && tempCol <= 7 && tempRow >= 2 && tempRow <= 7) {				// Check if temp space exists on board 
		if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempRow += 1;															// Move up and left one space 
			tempCol -= 1;

			if (tempCol > tempRow) {												// Scan using smallest dimensions 
				for (tempRow; tempRow >= 1; tempRow++) {
					if (board[tempCol][tempRow] == color) {
						retVal = true;
					}
					tempCol -= tempCol;
				}
			}
			else {
				for (tempCol; tempCol >= 1; tempCol--) {
					if (board[tempCol][tempRow] == color) {
						retVal = true;
					}
					tempRow += tempRow;
				}
			}
		}
	}  */
	return retVal;
}

Board::~Board()
{
	delete[] board;
}
