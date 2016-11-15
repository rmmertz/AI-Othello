// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Board.h"

using namespace std;

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
	Board.state = 0;
	Board.gameOver = false;

	// Display rules and challenge for first player slection
	cout << "A-H for rows, 1-8 for columns\nS1 for skip" << endl;
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
			cout << "Enter black move: ";
			cin >> column >> row;
		} while (!Board.isValidMove('B', column, row));

		Board.makeMove('B', column, row);
		Board.display();
	}

	// Primary game loop
	while (!Board.gameOver) {

		// Read move for white player
/*		do {
			cout << "Enter white move: ";
			cin >> column >> row;
		} while (!Board.isValidMove('W', column, row));
		Board.makeMove('W', column, row);
*/
		Board.state = 1;
		Board.aiSearch('W');
		Board.isValidMove(Board.aiBestMoveColor, Board.aiBestMoveCol, Board.aiBestMoveRow);
		Board.makeMove(Board.aiBestMoveColor, Board.aiBestMoveCol, Board.aiBestMoveRow);	// Execute move
		Board.display();									// Redraw board
		Board.state = 0;
		Board.gameOver = Board.endGame();					// Check for endgame condition


															// Read move for black player
		if (!Board.gameOver)
		{
			do {
				cout << "Enter black move: ";
				cin >> column >> row;
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

