/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
#include <iostream>
using namespace std;
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, constructorCheckPieces)
{
	Piezas p;
	bool allBlank = true;
	for (int i=0; i<BOARD_ROWS ; i++)
	{		
		for (int j=0; j<BOARD_COLS ; j++)
			{
				if(board[i][j] != Blank)
				{
					allBlank = false;
				}
			}
	}
	ASSERT_TRUE(allBlank == true);
}

TEST(PiezasTest, constructorCheckTurn)
{
	Piezas p;	
	ASSERT_TRUE(p.toggleTurn() == O);
}

TEST(PiezasTest, toggleTurnCheck)
{
	Piezas p;
	p.toggleTurn();	
	ASSERT_TRUE(p.toggleTurn() == O);
}

TEST(PiezasTest, resetCheck)
{
	Piezas p;
	p.toggleTurn();	
	p.dropPiece(2);
	p.dropPiece(2);
	p.dropPiece(2);
	p.dropPiece(2);
	p.reset();

	bool allBlank = true;
	for (int i=0; i<BOARD_ROWS ; i++)
	{		
		for (int j=0; j<BOARD_COLS ; j++)
			{
				if(board[i][j] != Blank)
				{
					allBlank = false;
				}
			}
	}
	ASSERT_TRUE(allBlank == true);
}

TEST(PiezasTest, dropPieceInvalidColumn)
{
	Piezas p;		
	ASSERT_TRUE(p.dropPiece(5) == Invalid)
}

TEST(PiezasTest, dropPieceMoreThanThrice)
{
	Piezas p;
	p.dropPiece(2);
	p.dropPiece(2);
	p.dropPiece(2);
	p.dropPiece(2);
	ASSERT_TRUE(p.dropPiece(2) == Blank);
}

TEST(PiezasTest, dropPieceGeneral)
{
	Piezas p;
	p.dropPiece(1);
	p.dropPiece(1);
	p.dropPiece(1);	
	ASSERT_TRUE(p.pieceAt(2,1) == X);
}

TEST(PiezasTest, pieceAtInvalid)
{
	Piezas p;
	p.dropPiece(1);
	p.dropPiece(1);
	p.dropPiece(1);	
	ASSERT_TRUE(p.pieceAt(5,1) == Invalid);
}

TEST(PiezasTest, pieceAtGeneral)
{
	Piezas p;
	p.dropPiece(1);
	p.dropPiece(1);
	p.dropPiece(1);	
	ASSERT_TRUE(p.pieceAt(2,1) == X);
}

TEST(PiezasTest, placePieceX)
{
	Piezas p;
	ASSERT_TRUE(p.pieceAt(2,1,'x') == X);
}

TEST(PiezasTest, placePieceO)
{
	Piezas p;
	ASSERT_TRUE(p.pieceAt(2,1,'o') == O);
}

TEST(PiezasTest, placePieceInvalid)
{
	Piezas p;
	ASSERT_TRUE(p.pieceAt(5,1,'x') == X);
}

TEST(PiezasTest, gameStateNotover)
{
	Piezas p;
	ASSERT_TRUE(p.gameState() == Invalid);
}


TEST(PiezasTest, xWinner)
{
	Piezas p;

	p.placePiece(0,1, 'x');
	p.placePiece(1,1, 'x');
	p.placePiece(2,1, 'x');
	

	p.placePiece(0,2, 'x');
	p.placePiece(1,2, 'x');
	p.placePiece(2,2, 'x');


	p.placePiece(0,3, 'x');
	p.placePiece(1,3, 'x');
	p.placePiece(2,3, 'x');


	p.placePiece(0,4, 'o');
	p.placePiece(1,4, 'o');
	p.placePiece(2,4, 'o');
	

	ASSERT_TRUE(p.gameState() == X);
}

TEST(PiezasTest, oWinner)
{
	Piezas p;

	p.placePiece(0,1, 'x');
	p.placePiece(1,1, 'x');
	p.placePiece(2,1, 'x');
	

	p.placePiece(0,2, 'o');
	p.placePiece(1,2, 'o');
	p.placePiece(2,2, 'o');


	p.placePiece(0,3, 'o');
	p.placePiece(1,3, 'o');
	p.placePiece(2,3, 'o');


	p.placePiece(0,4, 'o');
	p.placePiece(1,4, 'o');
	p.placePiece(2,4, 'o');
	

	ASSERT_TRUE(p.gameState() == O);
}

TEST(PiezasTest, gameTie)
{
	Piezas p;

	p.placePiece(0,1, 'x');
	p.placePiece(1,1, 'x');
	p.placePiece(2,1, 'x');
	

	p.placePiece(0,2, 'x');
	p.placePiece(1,2, 'x');
	p.placePiece(2,2, 'x');


	p.placePiece(0,3, 'o');
	p.placePiece(1,3, 'o');
	p.placePiece(2,3, 'o');


	p.placePiece(0,4, 'o');
	p.placePiece(1,4, 'o');
	p.placePiece(2,4, 'o');
	

	ASSERT_TRUE(p.gameState() == Blank);
}


