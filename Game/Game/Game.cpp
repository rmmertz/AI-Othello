// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Board.h"

using namespace std;

int minimax(Board, int, int, char *, int *);
int SEF(Board, char);

int main()
{
	// Declarations
	//char WhoStarts;
	int numValidBlackMoves;
	int whiteRow;
	char whiteColumn;
	char winner;
	int blackRow;
	char blackColumn;
	int depth;		// lookahead depth
	bool gameOver = false;
	Board Board;

	// Initializations
	Board.initBoard();

	// Display rules and challenge for first player slection
	cout << "A-H for rows, 1-8 for columns" << endl << "S1 for skip" << endl;
	//cout << "Who begins? W or B: ";
	//cin >> WhoStarts;

	// Check for valid player selection 
	//while (WhoStarts != 'B' && WhoStarts != 'W' && WhoStarts != 'w' && WhoStarts != 'b') {
	//	cout << "\nInvalid Selection \nWho begins? W or B: ";
	//	cin >> WhoStarts;
	//}		// TODO for testig

	cout << "Enter an integer for lookahead depth: ";
	cin >> depth;

	// Initial board display
	Board.display();

	// Special case for first player = black
	//if (WhoStarts == 'B' || WhoStarts == 'b') {
		do {
			cout << "Enter black move: ";
			cin >> blackColumn >> blackRow;
			//toupper(blackColumn);
			if (!Board.isValidMove('B', blackColumn, blackRow))
				cout << "Invalid move!" << endl;
		} while (!Board.isValidMove('B', blackColumn, blackRow));

		Board.makeMove('B', blackColumn, blackRow);
		Board.display();
	//}		// TODO for testig

	// Primary game loop
	while (!gameOver) {

		// Examine game tree and make move for white player
		cout << "Highest SEF score is " << minimax(Board, 0, depth, &whiteColumn, &whiteRow) << endl;
		cout << "Highest-scoring move for white is " << whiteColumn << whiteRow << endl;
		
		cout << "Making move for white" << endl;
		if (Board.isValidMove('W', whiteColumn, whiteRow)) {	// Check if minimax returned move is actually valid
			Board.makeMove('W', whiteColumn, whiteRow);			// Execute move
		}
		else
			cout << "ERROR: Invalid move attempted by White" << endl;

		Board.display();									// Redraw board
		gameOver = Board.endGame();							// Check for endgame condition

		// Read move for black player
		if (!gameOver)
		{
			numValidBlackMoves = 0;	// initialize counter
			// scan quickly for ANY valid moves: time saver
			for (char i = 'A'; i <= 'H'; i++)	// i: columns
			{
				for (int j = 1; j < 9; j++)		// j: rows
				{
					if (Board.isValidMove('B', i, j))
					{
						numValidBlackMoves++;
						break;	// stop: found a valid move
					}
				}
			}
			do {
				if (numValidBlackMoves == 0)
					cout << "No valid moves: you must enter S1 " << endl;
				else
					cout << "Enter black move: ";
				cin >> blackColumn >> blackRow;
				//toupper(blackColumn);
				if (!Board.isValidMove('B', blackColumn, blackRow))
					cout << "Invalid move!" << endl;
			} while (!Board.isValidMove('B', blackColumn, blackRow));

			Board.makeMove('B', blackColumn, blackRow);				// Execute move
			Board.display();								// Redraw board
			gameOver = Board.endGame();				// Check for endgame condition
		}
	} // End game loop


	// Score game
	cout << "Game Over" << endl;
	winner = Board.scoreGame();

	if (winner == 'T')
		cout << "Game was a Tie" << endl;
	else if (winner == 'W')
		cout << "Winner is: White" << endl;
	else
		cout << "Winner is: Black" << endl;

	system("PAUSE");										// Wait to close window
	return 0;
}


int SEF(Board Board, char color)
{
	int numValidMoves = 0;

	for (char i = 'A'; i <= 'H'; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			if (Board.isValidMove(color, i, j))
			{ 
				++numValidMoves;
				//cout << " Valid move: " << i << j << endl;		// TODO for test
			}
		}
	}

	return numValidMoves;
}

int minimax(Board Board, int level, int depth, char *column, int *row)
{
	char tempMoveColumn;
	int tempMoveRow, moveCounter;
	int value, Rvalue;
	char leafColor;
	if (depth % 2 == 0)		// developed the game tree ending at white
		leafColor = 'W';
	else			// developed the game tree ending at black
		leafColor = 'B';

	tempMoveColumn = 'S';
	tempMoveRow = 1;
	moveCounter = 1;

	if (level == depth)
	{
		//cout << "AIBestMove " << Board.AIBestMove.column << Board.AIBestMove.row << " saved again" << endl;
		return SEF(Board, leafColor);
	}
	else if (level % 2 == 0)		// maximizing level: white move
	{
		value = -61;
		for (char i = 'A'; i <= 'H'; i++)	// i: columns
		{
			for (int j = 1; j < 9; j++)		// j: rows
			{
				if(Board.isValidMove('W', i, j))
				{ 
					tempMoveColumn = i;
					tempMoveRow = j;
					Board.makeMove('W', i, j);
					//cout << "Minimax: made white move " << i << j << endl;	// TODO testing
					Rvalue = minimax(Board, level + 1, depth, &*column, &*row);
					if (Rvalue > value)
					{
						if (moveCounter <= 1) {
							tempMoveColumn = i;
							tempMoveRow = j;
							moveCounter++;
						}
						value = Rvalue;
						*column = i;	// save the white move
						*row = j;
						//Board.AIBestMove.column = i;	// save the white move
						//Board.AIBestMove.row = j;
						//cout << "AIBestMove " << Board.AIBestMove.column << Board.AIBestMove.row << " saved" << endl;
					}
					Board.unmakeMove();
					//cout << "Minimax: unmade white move " << i << j << endl;		// TODO testing
				}
			}
		}
	}
	else		// minimizing level: black move
	{
		value = 61;
		for (char i = 'A'; i <= 'H'; i++)	// i: columns
		{
			for (int j = 1; j < 9; j++)		// j: rows
			{
				if (Board.isValidMove('B', i, j))
				{
					Board.makeMove('B', i, j);
					//cout << "Minimax: made black move " << i << j << endl;	// TODO testing
					Rvalue = minimax(Board, level + 1, depth, &*column, &*row);
					if (Rvalue < value)
					{
						value = Rvalue;
					}
					Board.unmakeMove();
					//cout << "Minimax: unmade black move " << i << j << endl;		// TODO testing
				}
			}
		}
	}
	//cout << "AIBestMove " << Board.AIBestMove.column << Board.AIBestMove.row << " saved last" << endl;
	*column = tempMoveColumn;
	*row = tempMoveRow;
	
	return value;
}