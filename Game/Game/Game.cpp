// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Board.h"

using namespace std;

int main()
{
	// declarations
	char WhoStarts;
	char column;
	char winner;
	int row;
	bool gameOver;

	Board Board;
	Board.initBoard();


	// initializations
	gameOver = false;

	cout << "A-H for rows, 1-8 for columns\nS1 for skip" << endl;
	cout << "Who begins? W or B: ";
	cin >> WhoStarts;

	//Check for valid player selection 
	while (WhoStarts != 'B' && WhoStarts != 'W') {
		cout << "\nInvalid Selection \nWho begins? W or B: ";
		cin >> WhoStarts;
	}


	Board.display();

	if (WhoStarts == 'B')
	{ 		
		do {
			cout << "Enter black move: ";
			cin >> column >> row;
		} while (!Board.isValidMove('B', column, row));

		Board.makeMove('B', column, row);
		Board.display();

		}


	while (!gameOver)
	{

		// read moves
		do {
			cout << "Enter white move: ";
			cin >> column >> row;
		} while (!Board.isValidMove('W', column, row));

		Board.makeMove('W', column, row);
		Board.display();
//		gameOver = Board.endGame();

		if(!gameOver)
		{
			do {
				cout << "Enter black move: ";
				cin >> column >> row;
			} while (!Board.isValidMove('B', column, row));

			Board.makeMove('B', column, row);
			Board.display();
//			gameOver = Board.endGame();
		}
	}

/*
	//Score game
	cout << "Game Over" << endl;
	winner = Board.scoreGame();

	if (winner == 'T')
		cout << "Game was a Tie" << endl;
	else if (winner == 'W')
		cout << "Winner is: White" << endl;
	else
		cout << "Winner is: Black" << endl;
*/
    return 0;
}


