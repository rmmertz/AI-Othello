#include "stdafx.h"
#include "Board.h"
#include <iostream>

using namespace std;

Board::Board()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			currentBoard[i][j] = ' ';
			previousBoard[i][j] = ' ';
		}
}

void Board::initBoard()
{
	// initialize both boards
	currentBoard[3][3] = 'B';
	currentBoard[4][4] = 'B';	//Change to W for diagonal testing
	currentBoard[4][3] = 'W';	//Change to B for diagonal testing
	currentBoard[3][4] = 'W';

	previousBoard[3][3] = 'B';
	previousBoard[4][4] = 'B';	//Change to W for diagonal testing
	previousBoard[4][3] = 'W';	//Change to B for diagonal testing
	previousBoard[3][4] = 'W';
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
			cout << "|" << currentBoard[c][r];
		cout << "|";
		cout << endl << "    - - - - - - - - " << endl;	// indicate grid 
	}
	cout << endl;
}

void Board::unmakeMove()
{
	// revert to the previous board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			currentBoard[i][j] = previousBoard[i][j];
		}
	}
}

// mocks/ unnecessary
//void Board::keepMove(char column, int row)
//{
//	AIBestMove.row = row;
//	AIBestMove.column = column;
//}


void Board::makeMove(char color, char column, int row) {

	// Check for skipped move
	if (column == 'S' && row == 1) {
		skipCount++;
		//		if (++skipCount >= 2)						// Increment skip counter and check if two skips happened in a row
		//			gameOver = true;
		return;
	}
	//else. also shouldn't increment skipCount twice.
	skipCount = 0;									// Reset skip counter upon valid move

	// back up the current board before the next move is made
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			previousBoard[i][j] = currentBoard[i][j];	
		}
	}

	int newcol = column - 0x41;	// convert character to numerical
	int newrow = row - 1;	// user enters rows 1-8; program needs 0-7  

	currentBoard[newcol][newrow] = color;	// Flipped col/row for correct placement

	//Flip North
	if (flipNorth) {
		newrow -= 1;

		for (newrow; newrow >= 0; newrow--) {
			if (currentBoard[newcol][newrow] != ' ' && currentBoard[newcol][newrow] != color) {
				if (color == 'W')
					currentBoard[newcol][newrow] = 'W';		// can just be board[c][r] = color
				else
					currentBoard[newcol][newrow] = 'B';
			}
		}
		flipNorth = false;
	}


	//Flip South
	newcol = column - 0x41;	// convert character to numerical
	newrow = row - 1;

	if (flipSouth) {
		newrow += 1;

		for (newrow; newrow <= 7; newrow++) {
			if (currentBoard[newcol][newrow] != ' ' && currentBoard[newcol][newrow] != color) {
				if (color == 'W')
					currentBoard[newcol][newrow] = 'W';
				else
					currentBoard[newcol][newrow] = 'B';
			}
		}
		flipSouth = false;
	}

	//Flip West
	newcol = column - 0x41;	// convert character to numerical
	newrow = row - 1;

	if (flipWest) {
		newcol -= 1;

		for (newcol; newcol >= 0; newcol--) {
			if (currentBoard[newcol][newrow] != ' ' && currentBoard[newcol][newrow] != color) {
				if (color == 'W')
					currentBoard[newcol][newrow] = 'W';
				else
					currentBoard[newcol][newrow] = 'B';
			}
		}
		flipWest = false;
	}

	//Flip East
	newcol = column - 0x41;	// convert character to numerical
	newrow = row - 1;

	if (flipEast) {
		newcol += 1;

		for (newcol; newcol <= 7; newcol++) {
			if (currentBoard[newcol][newrow] != ' ' && currentBoard[newcol][newrow] != color) {
				if (color == 'W')
					currentBoard[newcol][newrow] = 'W';
				else
					currentBoard[newcol][newrow] = 'B';
			}
		}
		flipEast = false;
	}


	//Flip NorthWest
	newcol = column - 0x41;	// convert character to numerical
	newrow = row - 1;

	if (flipNW) {
		newrow -= 1;
		newcol -= 1;

		if (newrow > newcol) {												// Scan using smallest dimensions 
			for (newcol; newcol >= 0; newcol--) {
				if (currentBoard[newcol][newrow] != ' ' && currentBoard[newcol][newrow] != color) {
					if (color == 'W')
						currentBoard[newcol][newrow] = 'W';
					else
						currentBoard[newcol][newrow] = 'B';
				}
				newrow -= 1;
			}
			flipNW = false;
		}

		else {												// Scan using smallest dimensions 
			for (newrow; newrow >= 0; newrow--) {
				if (currentBoard[newcol][newrow] != ' ' && currentBoard[newcol][newrow] != color) {
					if (color == 'W')
						currentBoard[newcol][newrow] = 'W';
					else
						currentBoard[newcol][newrow] = 'B';
				}
				newcol -= 1;
			}
			flipNW = false;
		}
	}

	//Flip NorthEast
	newcol = column - 0x41;	// convert character to numerical
	newrow = row - 1;

	if (flipNE) {
		newrow -= 1;
		newcol += 1;

		if (newrow > newcol) {												// Scan using smallest dimensions 
			for (newcol; newcol <= 7; newcol++) {
				if (currentBoard[newcol][newrow] != ' ' && currentBoard[newcol][newrow] != color) {
					if (color == 'W')
						currentBoard[newcol][newrow] = 'W';
					else
						currentBoard[newcol][newrow] = 'B';
				}
				newrow -= 1;
			}
			flipNE = false;
		}

		else {												// Scan using smallest dimensions 
			for (newrow; newrow >= 0; newrow--) {
				if (currentBoard[newcol][newrow] != ' ' && currentBoard[newcol][newrow] != color) {
					if (color == 'W')
						currentBoard[newcol][newrow] = 'W';
					else
						currentBoard[newcol][newrow] = 'B';
				}
				newcol += 1;
			}
			flipNE = false;
		}
	}

	//Flip SouthEast
	newcol = column - 0x41;	// convert character to numerical
	newrow = row - 1;

	if (flipSE) {
		newrow += 1;
		newcol += 1;

		if (newrow > newcol) {												// Scan using smallest dimensions 
			for (newcol; newcol <= 7; newcol++) {
				if (currentBoard[newcol][newrow] != ' ' && currentBoard[newcol][newrow] != color) {
					if (color == 'W')
						currentBoard[newcol][newrow] = 'W';
					else
						currentBoard[newcol][newrow] = 'B';
				}
				newrow += 1;
			}
			flipSE = false;
		}

		else {												// Scan using smallest dimensions 
			for (newrow; newrow <= 7; newrow++) {
				if (currentBoard[newcol][newrow] != ' ' && currentBoard[newcol][newrow] != color) {
					if (color == 'W')
						currentBoard[newcol][newrow] = 'W';
					else
						currentBoard[newcol][newrow] = 'B';
				}
				newcol += 1;
			}
			flipSE = false;
		}
	}

	//Flip SouthWest
	newcol = column - 0x41;	// convert character to numerical
	newrow = row - 1;

	if (flipSW) {
		newrow += 1;
		newcol -= 1;

		if (newrow > newcol) {												// Scan using smallest dimensions 
			for (newcol; newcol >= 0; newcol--) {
				if (currentBoard[newcol][newrow] != ' ' && currentBoard[newcol][newrow] != color) {
					if (color == 'W')
						currentBoard[newcol][newrow] = 'W';
					else
						currentBoard[newcol][newrow] = 'B';
				}
				newrow += 1;
			}
			flipSW = false;
		}

		else {												// Scan using smallest dimensions 
			for (newrow; newrow <= 7; newrow++) {
				if (currentBoard[newcol][newrow] != ' ' && currentBoard[newcol][newrow] != color) {
					if (color == 'W')
						currentBoard[newcol][newrow] = 'W';
					else
						currentBoard[newcol][newrow] = 'B';
				}
				newcol -= 1;
			}
			flipSW = false;
		}
	}

	//Decrement remaining spaces counter upon valid move
	spacesRemain--;
}

bool Board::isValidMove(char color, char column, int row) {

	//Check for player skip move 
	if (column == 'S' && row == 1)
		return true;

	int newcol = column - 0x41;							// Convert character to numerical
	int newrow = (row - 1);							// Shift column by 1
	int tempCol, tempRow;

	//Reset flip flags
	flipNorth = false;
	flipSouth = false;
	flipEast = false;
	flipWest = false;
	flipNE = false;
	flipNW = false;
	flipSE = false;
	flipSW = false;

	//Check if rows and columns are within valid range
	if (newrow < 0 || newrow > 7 || newcol < 0 || newcol > 7) {
		return false;
	}
	//Check if space is presently occupied 
	if (currentBoard[newcol][newrow] != ' ') {
		return false;
	}


	// This breaks and returns true at first instance of a valid move. 
	// It does not validate remaining possible moves 

	//Check North
	tempCol = newcol;
	tempRow = newrow - 1;

	if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
		if (currentBoard[tempCol][tempRow] != ' ' && currentBoard[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempRow -= 1;															// Move to next space above opponents piece
			for (tempRow; tempRow >= 0; tempRow--) {								// Scan to upper edge of board for another player piece
				if (currentBoard[tempCol][tempRow] == color) {
					flipNorth = true;
				}
			}
		}
	}

	//Check South 
	tempCol = newcol;
	tempRow = newrow + 1;

	if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
		if (currentBoard[tempCol][tempRow] != ' ' && currentBoard[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempRow += 1;															// Move to next space below opponents piece
			for (tempRow; tempRow <= 7; tempRow++) {								// Scan to lower edge of board for another player piece
				if (currentBoard[tempCol][tempRow] == color) {
					flipSouth = true;
				}
			}
		}
	}

	//Check West
	tempCol = newcol - 1;
	tempRow = newrow;

	if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
		if (currentBoard[tempCol][tempRow] != ' ' && currentBoard[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempCol -= 1;															// Move to next space left of opponents piece
			for (tempCol; tempCol >= 0; tempCol--) {								// Scan to left edge of board for another player piece
				if (currentBoard[tempCol][tempRow] == color) {
					flipWest = true;
				}
			}
		}
	}

	//Check East
	tempCol = newcol + 1;
	tempRow = newrow;

	if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
		if (currentBoard[tempCol][tempRow] != ' ' && currentBoard[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempCol += 1;															// Move to next space right of opponents piece
			for (tempCol; tempCol <= 7; tempCol++) {								// Scan to right edge of board for another player piece
				if (currentBoard[tempCol][tempRow] == color) {
					flipEast = true;
				}
			}
		}
	}

	//Check NorthWest
	tempCol = newcol - 1;
	tempRow = newrow - 1;

	if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
		if (currentBoard[tempCol][tempRow] != ' ' && currentBoard[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempRow -= 1;															// Move up and left one space 
			tempCol -= 1;

			if (tempCol > tempRow) {												// Scan using smallest dimensions 
				for (tempRow; tempRow >= 0; tempRow--) {
					if (currentBoard[tempCol][tempRow] == color) {
						flipNW = true;
					}
					tempCol -= tempCol;
				}
			}
			else {
				for (tempCol; tempCol >= 0; tempCol--) {
					if (currentBoard[tempCol][tempRow] == color) {
						flipNW = true;
					}
					tempRow -= tempRow;
				}
			}
		}
	}

	//Check NorthEast
	tempCol = newcol + 1;
	tempRow = newrow - 1;

	if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
		if (currentBoard[tempCol][tempRow] != ' ' && currentBoard[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempRow -= 1;															// Move up and left one space 
			tempCol += 1;

			if (tempCol > tempRow) {												// Scan using smallest dimensions 
				for (tempRow; tempRow >= 0; tempRow--) {
					if (currentBoard[tempCol][tempRow] == color) {
						flipNE = true;
					}
					tempCol += tempCol;
				}
			}
			else {
				for (tempCol; tempCol <= 7; tempCol++) {
					if (currentBoard[tempCol][tempRow] == color) {
						flipNE = true;
					}
					tempRow -= tempRow;
				}
			}
		}
	}

	//Check SouthEast
	tempCol = newcol + 1;
	tempRow = newrow + 1;

	if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
		if (currentBoard[tempCol][tempRow] != ' ' && currentBoard[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempRow += 1;															// Move up and left one space 
			tempCol += 1;

			if (tempCol > tempRow) {												// Scan using smallest dimensions 
				for (tempRow; tempRow <= 7; tempRow++) {
					if (currentBoard[tempCol][tempRow] == color) {
						flipSE = true;
					}
					tempCol += tempCol;		// Is this right?? Game-ending error occurred when last value of tempCol was 256.
				}
			}
			else {
				for (tempCol; tempCol <= 7; tempCol++) {
					if (currentBoard[tempCol][tempRow] == color) {
						flipSE = true;
					}
					tempRow += tempRow;
				}
			}
		}
	}

	//Check SouthWest
	tempCol = newcol - 1;
	tempRow = newrow + 1;

	if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
		if (currentBoard[tempCol][tempRow] != ' ' && currentBoard[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
			tempRow += 1;															// Move up and left one space 
			tempCol -= 1;

			if (tempCol > tempRow) {												// Scan using smallest dimensions 
				for (tempRow; tempRow <= 7; tempRow++) {
					if (currentBoard[tempCol][tempRow] == color) {
						flipSW = true;
					}
					tempCol -= tempCol;
				}
			}
			else {
				for (tempCol; tempCol >= 0; tempCol--) {
					if (currentBoard[tempCol][tempRow] == color) {
						flipSW = true;
					}
					tempRow += tempRow;
				}
			}
		}
	}

	if (flipNorth || flipSouth || flipEast || flipWest || flipNW || flipNE || flipSW || flipSE) {
		return true;
	}
	else
		return false;
}


bool Board::endGame() {

	// Local counter variables
	int White = 0;
	int Black = 0;

	// Scan board and count White and Black spaces
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			if (currentBoard[i][j] == 'W')
				White++;
			else if (currentBoard[i][j] == 'B')
				Black++;
		}
	}

	if (White == 0|| Black == 0)			// There are zero white or black pieces on the board
		return true;
	else if (skipCount >= 2)				// Two skips have occurred in a row
		return true;
	else if (spacesRemain <= 0)				// The board is completely full
		return true;
	else
		return false;
}

char Board::scoreGame() {

	// Local counter and return variables
	int White = 0;
	int Black = 0;
	char result;

	// Scan board and count White and Black spaces
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			if (currentBoard[i][j] == 'W')
				White++;
			else if (currentBoard[i][j] == 'B')
				Black++;
		}
	}

	if (White > Black)						// White has more spaces than black
		result = 'W';
	else if (White < Black)					// Black has more spaces than white
		result = 'B';
	else                                    // Black and White have the same number of spaces
		result = 'T';
	return result;
}


Board::~Board()
{
	//	delete Board::board;					// Somehow breaks game, commented out for now
}