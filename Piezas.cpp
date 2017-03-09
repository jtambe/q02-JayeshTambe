#include "Piezas.h"
#include <vector>
#include <iostream>
using namespace std;
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 6 rows, 7 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{		

	board.resize( BOARD_ROWS, vector<Piece>( BOARD_COLS , Blank ) );	
	turn = X;
}


Piece Piezas::toggleTurn()
{
	if (turn == X) {turn = O;}	
	else if (turn == O) {turn = X;}
	return turn;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified (or default if overloaded constructor
 * is never called).
**/
void Piezas::reset()
{
	for (int i=0; i<BOARD_ROWS ; i++)
	{		
		for (int j=0; j<BOARD_COLS ; j++)
			{
				board[i][j] = Blank;
			}
	}

}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
	Piece result = turn;
	// invalid column
	if(column > BOARD_COLS-1) //call this with invalid column
	{
		toggleTurn();
		return Invalid;
	}
	
	// is column full case
	if(board[0][column] != Blank) // call dropPiece more than thrice
	{
		toggleTurn();
		return Blank;
	}

	//cout << "here in droppiece" << endl;
	// general case
	for(int i =BOARD_ROWS-1; i >=0 ;i--) 
	{
		if(board[i][column] ==  Blank)
		{
			board[i][column] = turn;			
			result = turn;
			toggleTurn();
			//return result;
		}
	}
	return result;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{	
	if(row < 0 || row > BOARD_ROWS-1 || column < 0 || column > BOARD_COLS-1) // call with invalid input
	{
		return Invalid;
	}
	else
	{
		return board[row][column];
	}

}

// myfunction for making testing easy
Piece Piezas::placePiece(int row, int column, char c)
{
	if(row < 0 || row > BOARD_ROWS-1 || column < 0 || column > BOARD_COLS-1) // call with invalid input
	{
		return Invalid;
	}
	else // call with fixed input
	{
		if(c == 'x') {board[row][column] = X;}
		if(c == 'o') {board[row][column] = O;}
		return board[row][column];
	}

}





/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
	bool isGameOver = true;

	for (int i=0; i<BOARD_ROWS ; i++)
	{		
		for (int j=0; j<BOARD_COLS ; j++)
			{
				if(board[i][j] == Blank)
				{
					isGameOver = false;   // call it while board has some blank pieces
				}
			}
	}

	if(isGameOver == false)
	{
		return Invalid;
	}

	int maxXcount = 0;
	int maxOcount = 0;

	int xcount =0; int ocount = 0;

	// check max count within rows
	for (int i=0; i<BOARD_ROWS ; i++)
	{		
		for (int j=0; j<BOARD_COLS ; j++)
		{
			if(board[i][j] == X)
			{
				ocount =0;
				xcount++;
				if(maxXcount < xcount)
				{
					maxXcount = xcount;
				}
			}
			else if(board[i][j] == O)
			{
				xcount =0;
				ocount++;
				if(maxOcount < ocount)
				{
					maxOcount = ocount;
				}
			}

		}
		xcount =0;  ocount = 0;
	}

	//cout << "maxXcount: " << maxXcount << endl;
	//cout << "maxOcount: " << maxOcount << endl;

	xcount =0;  ocount = 0;
	// check maxcount within columns
	for (int i=0; i<BOARD_COLS ; i++) // 0 - 3
	{
		for (int j=0; j<BOARD_ROWS ; j++) // 0 - 2
		{
			if(board[j][i] == X)
			{
				ocount =0;
				xcount++;
				if(maxXcount < xcount)
				{
					maxXcount = xcount;
				}
			}
			else if(board[j][i] == O)
			{
				xcount =0;
				ocount++;
				if(maxOcount < ocount)
				{
					maxOcount = ocount;
				}
			}
		}
		xcount =0;  ocount = 0;
	}

	//cout << "maxXcount: " << maxXcount << endl;
	//cout << "maxOcount: " << maxOcount << endl;
	
	if(maxXcount > maxOcount){ return X;} // call it after placing x as winner
	if(maxXcount < maxOcount){ return O;} // call it after placing o as winner 
	else {return Blank;} // manage equal entries

}


// int main()
// {
// 	// Piezas p;
// 	// //cout << p.pieceAt(0,5) << endl;;


// 	// //p.reset();
// 	// for (int i =0; i<BOARD_ROWS ;i++)
// 	// {		
// 	// 	for (int j=0; j<BOARD_COLS ;j++)
// 	// 		{
// 	// 			cout << p.pieceAt(i,j) << '\t';
// 	// 		}
// 	// 		cout << endl;
// 	// }

// 	// cout << p.toggleTurn() << endl;


// 	Piezas p;


// 	p.placePiece(0,0, 'o');
// 	p.placePiece(1,0, 'o');
// 	p.placePiece(2,0, 'o');

// 	p.placePiece(0,1, 'o');
// 	p.placePiece(1,1, 'o');
// 	p.placePiece(2,1, 'o');
	

// 	p.placePiece(0,2, 'o');
// 	p.placePiece(1,2, 'o');
// 	p.placePiece(2,2, 'o');


// 	p.placePiece(0,3, 'o');
// 	p.placePiece(1,3, 'x');
// 	p.placePiece(2,3, 'x');


// 	for (int i =0; i<BOARD_ROWS ;i++)
// 	{		
// 		for (int j=0; j<BOARD_COLS ;j++)
// 			{
// 				cout << p.pieceAt(i,j) << '\t';
// 			}
// 			cout << endl;
// 	}

// 	cout << p.gameState() << endl;



// 	// cout << "new test" << endl;
// 	// p.dropPiece(2);
// 	// p.dropPiece(2);
// 	// p.dropPiece(2);
// 	// cout << p.pieceAt(2,2) << endl;
// 	// cout << p.pieceAt(1,2) << endl;
// 	// cout << p.pieceAt(0,2) << endl;

// 	// p.placePiece(0,0, 'x');
// 	// p.placePiece(0,1, 'x');
// 	// p.placePiece(0,2, 'x');
// 	// p.placePiece(0,3, 'x');
	
// 	// p.placePiece(1,0, 'o');
// 	// p.placePiece(1,1, 'o');
// 	// p.placePiece(1,2, 'o');
// 	// p.placePiece(1,3, 'o');


// 	// p.placePiece(2,0, 'x');
// 	// p.placePiece(2,1, 'x');
// 	// p.placePiece(2,2, 'x');
// 	// p.placePiece(2,3, 'x');
	
// 	// cout << "winner: " << p.gameState() << endl;

// 	//cout << "success" << endl;

// }