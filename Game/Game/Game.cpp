// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Board.h"

using namespace std;

int minimax(Board, int, int);
int SEF(Board, char);

int main()
{
	// Declarations
	char WhoStarts;
	char column;
	char winner;
	int row;                
	Board Board;

	// Initializations
	Board.initBoard();
	Board.spacesRemain = 60;
	Board.skipCount = 0;
	Board.gameOver = false;

	// Display rules and challenge for first player slection
	cout << "A-H for rows, 1-8 for columns" << endl << "S1 for skip" << endl;
	cout << "Who begins? W or B: ";
	cin >> WhoStarts;

	// Check for valid player selection 
	while (WhoStarts != 'B' && WhoStarts != 'W') {
		cout << "\nInvalid Selection \nWho begins? W or B: ";
		cin >> WhoStarts;
	}

	// Initial board display
	Board.display();

	// Special case for first player = black
	if (WhoStarts == 'B') {
		do {
			/**** Testing SEF *****/
			cout << "Current SEF score (# of moves) for black: " << SEF(Board, 'B') << endl;
			/*********/
			cout << "Enter black move: ";
			cin >> column >> row;
			if (!Board.isValidMove('B', column, row))
				cout << "Invalid move!" << endl;
		} while (!Board.isValidMove('B', column, row));

		Board.makeMove('B', column, row);
		Board.display();
	}

	// Primary game loop
	while (!Board.gameOver) {

		// Read move for white player
		do {
			/**** Testing SEF *****/
			cout << "Current SEF score (# of moves) for white: " << SEF(Board, 'W') << endl;
			/*********/
			cout << "Enter white move: ";
			cin >> column >> row;
			if (!Board.isValidMove('W', column, row))
				cout << "Invalid move!" << endl;
		} while (!Board.isValidMove('W', column, row));

		Board.makeMove('W', column, row);					// Execute move
		Board.display();									// Redraw board
		Board.gameOver = Board.endGame();					// Check for endgame condition

		// Read move for black player
		if (!Board.gameOver)
		{
			do {
				/**** Testing SEF *****/
				cout << "Current SEF score (# of moves) for black: " << SEF(Board, 'B') << endl;
				/*********/
				cout << "Enter black move: ";
				cin >> column >> row;
				if (!Board.isValidMove('B', column, row))
					cout << "Invalid move!" << endl;
			} while (!Board.isValidMove('B', column, row));

			Board.makeMove('B', column, row);				// Execute move
			Board.display();								// Redraw board
			Board.gameOver = Board.endGame();				// Check for endgame condition
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
				cout << " Valid move: " << i << j << endl;		// TODO for test
			}
		}
	}

	return numValidMoves;
}

int minimax(Board Board, int level, int depth)
{
	int value, Rvalue;
	char leafColor;
	if (depth % 2 == 0)		// developed the game tree ending at white
		leafColor = 'W';
	else			// developed the game tree ending at black
		leafColor = 'B';

	if (level == depth)
		return SEF(Board, leafColor);
	else if (level % 2 == 0)		// maximizing level: white move
	{
		value = -61;
		for (char i = 'A'; i <= 'H'; i++)	// i: columns
		{
			for (int j = 1; j < 9; j++)		// j: rows
			{
				Board.makeMove('W', i, j);
				Rvalue = minimax(Board, level + 1, depth);
				if (Rvalue > value)
				{
					value = Rvalue;
					//Board.keepMove(i, j);	// column, row
				}
				Board.unmakeMove();
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
				Board.makeMove('B', i, j);
				Rvalue = minimax(Board, level + 1, depth);
				if (Rvalue < value)
				{
					value = Rvalue;
					Board.AIBestMove.column = i;
					Board.AIBestMove.row = j;
				}
				Board.unmakeMove();
			}
		}
	}

	return value;
}