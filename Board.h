/**
 * Board.h - Header file for the Board class
 * Written by: George Fashho [6/9/2022]
 */


#ifndef _BOARD_H
#define _BOARD_H

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;


#include "Pieces.h"
#include "Exceptions.h"

#define NROWS 10
#define NCOLS 20

class Board {
	private: 
        int nRows;
	    int nCols;
	    int row;
	    int col;
	    int playerRow;
	    int playerCol;
	    Piece * pieces[ NROWS ][ NCOLS ];
	    int lastTurnPlayed[ NROWS ][ NCOLS ];
	    int currentTurn;
	    static Board * theBoard;
		Board( ); // PRIVATE constructor, for Singleton pattern
	    
	public: 
		static Board * getBoard( );
		void display( );
		void play( );
		void moveMeTo( int newRow,  int newCol );
		void getPlayerPosition( int & row, int & col );
};

#endif //_BOARD_H
