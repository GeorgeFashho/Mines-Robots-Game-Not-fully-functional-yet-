/**
 * Pieces.h - Header file for the Piece class and all its subclasses.
 * Written by: George Fashho [6/9/2022]
 */


#ifndef _PIECES_H
#define _PIECES_H

// First the Piece class itself

class Piece {
	public:  
		virtual char display( ) = 0;
    	virtual void move( int r, int c );
        virtual bool isMine( );

        virtual bool isBarrier( );
    	virtual bool isSpace( );

    ~Piece();
};

// Then all the subclasses

class Player: public Piece {
		virtual char display( );
    	virtual void move( int r, int c );
};


class Robot: public Piece {
		static int nRobots;
		virtual char display( ) ;
    	virtual void move( int r, int c );
};


class Mine: public Piece {
		virtual char display( );
        virtual bool isMine( );

};

class Brick: public Piece {
		virtual char display( );
    	virtual bool isBarrier( );
};

class Space: public Piece {
		virtual char display( );
    	virtual bool isSpace( );
};

#endif //_PIECES_H
