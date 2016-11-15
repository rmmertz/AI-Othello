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



void Board::aiSearch(char color) {
	int moveScore = 0;
	char testColumn;
	int testRow;
	aiBestMoveColor = color;
	aiBestMoveCol = (0x41);
	aiBestMoveRow = (0);
	aiBestMoveScore = moveScore;
	int newcol, newrow;

	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {

			testColumn = (i + 0x41);
			testRow = (j + 1);

//			cout << testColumn << " " << testRow << " " << color << endl;

			if (isValidMove(color, testColumn, testRow)) {


				//Flip North

				newcol = i;
				newrow = j;

				if (flipNorth) {
					newrow -= 1;

					for (newrow; newrow >= 0; newrow--) {
						if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
							moveScore++;
						}
					}
					flipNorth = false;
				}


				//Flip South
				newcol = i;
				newrow = j;

				if (flipSouth) {
					newrow += 1;

					for (newrow; newrow <= 7; newrow++) {
						if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
							moveScore++;
						}
					}
					flipSouth = false;
				}

				//Flip West
				newcol = i;
				newrow = j;

				if (flipWest) {
					newcol -= 1;

					for (newcol; newcol >= 0; newcol--) {
						if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
							moveScore++;
						}
					}
					flipWest = false;
				}

				//Flip East
				newcol = i;
				newrow = j;

				if (flipEast) {
					newcol += 1;

					for (newcol; newcol <= 7; newcol++) {
						if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
							moveScore++;
						}
					}
					flipEast = false;
				}


				//Flip NorthWest
				newcol = i;
				newrow = j;

				if (flipNW) {
					newrow -= 1;
					newcol -= 1;

					if (newrow > newcol) {												// Scan using smallest dimensions 
						for (newcol; newcol >= 0; newcol--) {
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								moveScore++;
							}
							newrow--;
						}
						flipNW = false;
					}

					else {												// Scan using smallest dimensions 
						for (newrow; newrow >= 0; newrow--) {
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								moveScore++;
							}
							newcol--;
						}
						flipNW = false;
					}
				}

				//Flip NorthEast
				newcol = i;
				newrow = j;

				if (flipNE) {
					newrow -= 1;
					newcol += 1;

					if (newrow > newcol) {												// Scan using smallest dimensions 
						for (newcol; newcol <= 7; newcol++) {
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								moveScore++;
							}
							newrow--;
						}
						flipNE = false;
					}

					else {												// Scan using smallest dimensions 
						for (newrow; newrow >= 0; newrow--) {
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								moveScore++;
							}
							newcol++;
						}
						flipNE = false;
					}
				}

				//Flip SouthEast
				newcol = i;
				newrow = j;

				if (flipSE) {
					newrow += 1;
					newcol += 1;

					if (newrow > newcol) {												// Scan using smallest dimensions 
						for (newcol; newcol <= 7; newcol++) {
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								moveScore++;
							}
							newrow++;
						}
						flipSE = false;
					}

					else {												// Scan using smallest dimensions 
						for (newrow; newrow <= 7; newrow++) {
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								moveScore++;
							}
							newcol++;
						}
						flipSE = false;
					}
				}

				//Flip SouthWest
				newcol = i;
				newrow = j;

				if (flipSW) {
					newrow += 1;
					newcol -= 1;

					if (newrow > newcol) {												// Scan using smallest dimensions 
						for (newcol; newcol >= 0; newcol--) {
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								moveScore++;
							}
							newrow++;
						}
						flipSW = false;
					}

					else {												// Scan using smallest dimensions 
						for (newrow; newrow <= 7; newrow++) {
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								moveScore++;
							}
							newcol--;
						}
						flipSW = false;
					}
				}





				if (moveScore > aiBestMoveScore) {

		//			aiBestMoveColor = color;
					aiBestMoveCol = (i + 0x41);
					aiBestMoveRow = (j + 1);
					aiBestMoveScore = moveScore;
//					cout << "Color: " << aiBestMoveColor << endl;
//					cout << "Column: " << aiBestMoveCol << endl;
//					cout << "Row: " << aiBestMoveRow << endl;
				}
			}
		}
	}
	isValidMove(aiBestMoveColor, aiBestMoveCol, aiBestMoveRow);
}




			void Board::makeMove(char color, char column, int row) {

				// Check for skipped move
				if (column == 'S' && row == 1) {
					skipCount++;
					//		if (++skipCount >= 2)						// Increment skip counter and check if two skips happened in a row
					//			gameOver = true;
					return;
				}

				skipCount = 0;									// Reset skip counter upon valid move

				int newcol = column - 0x41;	// convert character to numerical
				int newrow = row - 1;

				board[newcol][newrow] = color;	// user enters columns 1-8; program needs 0-7   (Flipped col/row for correct placement)
												// and flip pieces...

												//Flip North
				if (flipNorth) {
					newrow -= 1;

					for (newrow; newrow >= 0; newrow--) {
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
				newcol = column - 0x41;	// convert character to numerical
				newrow = row - 1;

				if (flipSouth) {
					newrow += 1;

					for (newrow; newrow <= 7; newrow++) {
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
				newcol = column - 0x41;	// convert character to numerical
				newrow = row - 1;

				if (flipWest) {
					newcol -= 1;

					for (newcol; newcol >= 0; newcol--) {
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
				newcol = column - 0x41;	// convert character to numerical
				newrow = row - 1;

				if (flipEast) {
					newcol += 1;

					for (newcol; newcol <= 7; newcol++) {
						if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
							if (color == 'W')
								board[newcol][newrow] = 'W';
							else
								board[newcol][newrow] = 'B';
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
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								if (color == 'W')
									board[newcol][newrow] = 'W';
								else
									board[newcol][newrow] = 'B';
							}
							newrow -= 1;
						}
						flipNW = false;
					}

					else {												// Scan using smallest dimensions 
						for (newrow; newrow >= 0; newrow--) {
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								if (color == 'W')
									board[newcol][newrow] = 'W';
								else
									board[newcol][newrow] = 'B';
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
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								if (color == 'W')
									board[newcol][newrow] = 'W';
								else
									board[newcol][newrow] = 'B';
							}
							newrow -= 1;
						}
						flipNE = false;
					}

					else {												// Scan using smallest dimensions 
						for (newrow; newrow >= 0; newrow--) {
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								if (color == 'W')
									board[newcol][newrow] = 'W';
								else
									board[newcol][newrow] = 'B';
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
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								if (color == 'W')
									board[newcol][newrow] = 'W';
								else
									board[newcol][newrow] = 'B';
							}
							newrow += 1;
						}
						flipSE = false;
					}

					else {												// Scan using smallest dimensions 
						for (newrow; newrow <= 7; newrow++) {
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								if (color == 'W')
									board[newcol][newrow] = 'W';
								else
									board[newcol][newrow] = 'B';
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
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								if (color == 'W')
									board[newcol][newrow] = 'W';
								else
									board[newcol][newrow] = 'B';
							}
							newrow += 1;
						}
						flipSW = false;
					}

					else {												// Scan using smallest dimensions 
						for (newrow; newrow <= 7; newrow++) {
							if (board[newcol][newrow] != ' ' && board[newcol][newrow] != color) {
								if (color == 'W')
									board[newcol][newrow] = 'W';
								else
									board[newcol][newrow] = 'B';
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
					cout << "Invalid Move 1!" << endl;
					return false;
				}
				//Check if space is presently occupied 
				if (board[newcol][newrow] != ' ' && state == 0) {
					cout << "Invalid Move 2!" << endl;
					return false;
				}

/*				cout << "Testing: " << color << " " << column << " " << row << endl;
				cout << "Column: " << newcol << "    Row: " << newrow << endl;
*/
				// This breaks and returns true at first instance of a valid move. 
				// It does not validate remaining possible moves 

				//Check North
				tempCol = newcol;
				tempRow = newrow - 1;

				if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
					if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
						tempRow -= 1;															// Move to next space above opponents piece
						for (tempRow; tempRow >= 0; tempRow--) {								// Scan to upper edge of board for another player piece
							if (board[tempCol][tempRow] == color) {
								flipNorth = true;
							}
						}
					}
				}

				//Check South 
				tempCol = newcol;
				tempRow = newrow + 1;

				if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
					if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
						tempRow += 1;															// Move to next space below opponents piece
						for (tempRow; tempRow <= 7; tempRow++) {								// Scan to lower edge of board for another player piece
							if (board[tempCol][tempRow] == color) {
								flipSouth = true;
							}
						}
					}
				}

				//Check West
				tempCol = newcol - 1;
				tempRow = newrow;

				if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
					if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
						tempCol -= 1;															// Move to next space left of opponents piece
						for (tempCol; tempCol >= 0; tempCol--) {								// Scan to left edge of board for another player piece
							if (board[tempCol][tempRow] == color) {
								flipWest = true;
							}
						}
					}
				}

				//Check East
				tempCol = newcol + 1;
				tempRow = newrow;

				if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
					if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
						tempCol += 1;															// Move to next space right of opponents piece
						for (tempCol; tempCol <= 7; tempCol++) {								// Scan to right edge of board for another player piece
							if (board[tempCol][tempRow] == color) {
								flipEast = true;
							}
						}
					}
				}

				//Check NorthWest
				tempCol = newcol - 1;
				tempRow = newrow - 1;

				if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
					if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
						tempRow -= 1;															// Move up and left one space 
						tempCol -= 1;

						if (tempCol > tempRow) {												// Scan using smallest dimensions 
							for (tempRow; tempRow >= 0; tempRow--) {
								if (board[tempCol][tempRow] == color) {
									flipNW = true;
								}
								tempCol--;
							}
						}
						else {
							for (tempCol; tempCol >= 0; tempCol--) {
								if (board[tempCol][tempRow] == color) {
									flipNW = true;
								}
								tempRow--;
							}
						}
					}
				}

				//Check NorthEast
				tempCol = newcol + 1;
				tempRow = newrow - 1;

				if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
					if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
						tempRow -= 1;															// Move up and left one space 
						tempCol += 1;

						if (tempCol > tempRow) {												// Scan using smallest dimensions 
							for (tempRow; tempRow >= 0; tempRow--) {
								if (board[tempCol][tempRow] == color) {
									flipNE = true;
								}
								tempCol++;
							}
						}
						else {
							for (tempCol; tempCol <= 7; tempCol++) {
								if (board[tempCol][tempRow] == color) {
									flipNE = true;
								}
								tempRow--;
							}
						}
					}
				}

				//Check SouthEast
				tempCol = newcol + 1;
				tempRow = newrow + 1;

				if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
					if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
						tempRow += 1;															// Move up and left one space 
						tempCol += 1;

						if (tempCol > tempRow) {												// Scan using smallest dimensions 
							for (tempRow; tempRow <= 7; tempRow++) {
								if (board[tempCol][tempRow] == color) {
									flipSE = true;
								}
								tempCol++;
							}
						}
						else {
							for (tempCol; tempCol <= 7; tempCol++) {
								if (board[tempCol][tempRow] == color) {
									flipSE = true;
								}
								tempRow++;
							}
						}
					}
				}

				//Check SouthWest
				tempCol = newcol - 1;
				tempRow = newrow + 1;

				if (tempCol >= 0 && tempCol <= 7 && tempRow >= 0 && tempRow <= 7) {				// Check if temp space exists on board 
					if (board[tempCol][tempRow] != ' ' && board[tempCol][tempRow] != color) {	// Check if space is occupied by opponent piece
						tempRow += 1;															// Move up and left one space 
						tempCol -= 1;

						if (tempCol > tempRow) {												// Scan using smallest dimensions 
							for (tempRow; tempRow <= 7; tempRow++) {
								if (board[tempCol][tempRow] == color) {
									flipSW = true;
								}
								tempCol--;
							}
						}
						else {
							for (tempCol; tempCol >= 0; tempCol--) {
								if (board[tempCol][tempRow] == color) {
									flipSW = true;
								}
								tempRow++;
							}
						}
					}
				}

				if (flipNorth || flipSouth || flipEast || flipWest || flipNW || flipNE || flipSW || flipSE) {

/*					cout << "North: " << flipNorth << endl;
					cout << "South: " << flipSouth << endl;
					cout << "East: " << flipEast << endl;
					cout << "West: " << flipWest << endl;
					cout << "NW: " << flipNW << endl;
					cout << "NE: " << flipNE << endl;
					cout << "SW: " << flipSW << endl;
					cout << "SE: " << flipSE << endl;
*/





					return true;
				}
				else
					if (state == 0) 
					cout << "Invalid Move 3!" << endl;
				return false;
			}


			bool Board::endGame() {

				// Local counter variables
				int White = 0;
				int Black = 0;

				// Scan board and count White and Black spaces
				for (int i = 0; i <= 7; i++) {
					for (int j = 0; j <= 7; j++) {
						if (board[i][j] == 'W')
							White++;
						else if (board[i][j] == 'B')
							Black++;
					}
				}

				if (!White || !Black)					// There are zero white or black pieces on the board
					return true;
				else if (skipCount >= 2)				// Two skips have occured in a row
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
						if (board[i][j] == 'W')
							White++;
						else if (board[i][j] == 'B')
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