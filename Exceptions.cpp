/**
 * Exceptions.cp - Source code file for the Exception class and all its subclasses.
 * Written by: George Fashho [6/9/2022]
 */

#include "Exceptions.h"
#include "Board.h"
#include "Pieces.h"

// First the methods for Exception itself

Exception::Exception( string s ) {

    description = s;
}

string Exception::getDescription( ) {

    return description;
}

// Then the subclasses

InvalidMove::InvalidMove( string s ) : Exception( s ) { // Checks for if the piece moves more than one space

}

SpaceUnavailable::SpaceUnavailable(string s1, string s) : Exception(s1) { //is thrown when robot or player runs
                                                                            // into a barrier or out of bounds
}

Collision::Collision(string s1, string s, int r, int c) : Exception(s1) {//is thrown when 2 pieces collide
                                                                            // with each other
    getLocation(r,c);
}

void Collision::getLocation( int & r, int & c ) { //getting the location of new board piece

}

