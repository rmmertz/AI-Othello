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

	board[newcol][newrow] = color;	// user enters columns 1-8; program needs 0-7   (Flipped col/row for correct placement)
	// and flip pieces...

	//Flip North
	if (flipNorth) {
		newrow -= 1;

		for (newrow; newrow >= 1; newrow--) {
			if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
				if (color == 'W')
					board[newcol][newrow] = 'W';
				else
					board[newcol][newrow] = 'B';
			}
		}
		flipNorth = false;
	} 

	//Flip South
	if (flipSouth) {
		newrow += 1;

		for (newrow; newrow <= 8; newrow++) {
			if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
				if (color == 'W')
					board[newcol][newrow] = 'W';
				else
					board[newcol][newrow] = 'B';
			}
		}
		flipSouth = false;
	}

	//Flip West
	if (flipWest) {
		newcol -= 1;

		for (newcol; newcol >= 1; newcol--) {
			if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
				if (color == 'W')
					board[newcol][newrow] = 'W';
				else
					board[newcol][newrow] = 'B';
			}
		}
		flipWest = false;
	}

	//Flip East
	if (flipEast) {
		newcol += 1;

		for (newcol; newcol <= 8; newcol++) {
			if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
				if (color == 'W')
					board[newcol][newrow] = 'W';
				else
					board[newcol][newrow] = 'B';
			}
		}
		flipEast = false;
	}


	//Flip NorthEast



}






bool Board::isValidMove(char color, char column, int row)
{
	int newcol = column - 0x41;							// Convert character to numerical
	int newrow = (row - 1);							// Shift column by 1
	int tempCol, tempRow;

	//Reset flip flags
	flipNorth = false;
	flipSouth = false;
	flipEast = false;
	flipWest = false;


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
					flipNorth = true;
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
			for (tempRow; tempRow <= 8; tempRow++) {								// Scan to lower edge of board for another player piece
				if (board[tempCol][tempRow] == color) {
					flipSouth = true;
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
					flipWest = true;
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
			for (tempCol; tempCol <= 8; tempCol++) {								// Scan to right edge of board for another player piece
				if (board[tempCol][tempRow] == color) {
					flipEast = true;
				}
			}
		}
	}

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
						return true;
					}
				tempCol -= tempCol;
				}
			}
			else {
				for (tempCol; tempCol >= 1; tempCol--) {
					if (board[tempCol][tempRow] == color) {
						return true;
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
						return true;
					}
					tempCol += tempCol;
				}
			}
			else {
				for (tempCol; tempCol <= 8; tempCol++) {
					if (board[tempCol][tempRow] == color) {
						return true;
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
				for (tempRow; tempRow <= 8; tempRow++) {
					if (board[tempCol][tempRow] == color) {
						return true;
					}
					tempCol += tempCol;
				}
			}
			else {
				for (tempCol; tempCol <= 8; tempCol++) {
					if (board[tempCol][tempRow] == color) {
						return true;
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
				for (tempRow; tempRow <= 8; tempRow++) {
					if (board[tempCol][tempRow] == color) {
						return true;
					}
					tempCol -= tempCol;
				}
			}
			else {
				for (tempCol; tempCol >= 1; tempCol--) {
					if (board[tempCol][tempRow] == color) {
						return true;
					}
					tempRow += tempRow;
				}
			}
		}
	}  

	if (flipNorth || flipSouth || flipEast || flipWest) {
		return true;
	}
	else
		return false;
}

Board::~Board()
{
	delete[] board;
}
