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
	char row;
	int column;
	bool gameOver;

	Board Board;
	Board.initBoard();
	Board.display();

	// initializations
	gameOver = 0;

	cout << "A-H for rows, 1-8 for columns \n";
	cout << "Who begins? W or B: ";
	cin >> WhoStarts;

	if (WhoStarts == 'B')
	{ 		
		cout << "Enter black move: ";
		cin >> row >> column;
		Board.makeMove('B', row, column);
		Board.display();
	}

	while (!gameOver)
	{
		// read moves
		cout << "Enter white move: ";
		cin >> row >> column;
		if (Board.isValidMove(row, column))
			Board.makeMove('W', row, column);
		else
			cout << "Invalid move" << endl;
		Board.display();

		if(!gameOver)
		{
			cout << "Enter black move: ";
			cin >> row >> column;
			if (Board.isValidMove(row, column))
				Board.makeMove('B', row, column);
			else
				cout << "Invalid move" << endl;
			Board.display();
		}

		// if winner or draw
			// gameOver = 1;
	}
 
    return 0;
}


