/**
 * Pieces.cpp - Source code file for the Piece class and all its subclasses.
 * Written by: George Fashho [6/9/2022]
 */


#include "Pieces.h"
#include "Exceptions.h"
#include "Board.h"
#include <cstdlib>
#include <iostream>
#include <string>


 int Robot::nRobots = 4;

/*Piece Class Methods*/

void Piece::move( int r, int c ) {

	return; // Do-nothing method
}
Piece::~Piece() = default;

bool Piece::isBarrier() {
	return false; // for most Pieces
}

bool Piece::isSpace() {
	return false; // for most Pieces
}

bool Piece::isMine() { //for most Pieces
    return false;
}

/*Player Class methods*/

char Player::display( ) { //Displays player piece
    cout<<"A";
}

/* Player movement:
 *
 * @Param int r = current player row
 * @param int c = current player col
 *
 * cin<< userInput : Takes a keyboard input and checks if it is valid
 * Player Row & Col get updated depending on move chosen
 * Then calls moveMeTo() to attempt the move
 */
void Player::move( int r, int c ) { // Reads in keyboard input

    int tempc = c;
    int tempr = r;

    char userInput;

    while (true) {
        cout << "\n   Please enter a letter from the following to move one space: \n"
             << "         A: Left | D: Right | W: Up | X: Down | \n"
             << "Q/E/Z/C diagonally in respective to previous letters | S: Stand Still\n";

        cin >> userInput;

        if ((char) toupper(userInput) == 'A') {
            tempc -= 1;
            break;

        } else if ((char) toupper(userInput) == 'D') {
            tempc += 1;
            break;

        } else if ((char) toupper(userInput) == 'W') {
            tempr -= 1;
            break;

        } else if ((char) toupper(userInput) == 'X') {
            tempr += 1;
            break;

        } else if ((char) toupper(userInput) == 'Q') {
            tempr -= 1;
            tempc -= 1;
            break;

        } else if ((char) toupper(userInput) == 'E') {
            tempr -= 1;
            tempc += 1;
            break;

        } else if ((char) toupper(userInput) == 'Z') {
            tempr += 1;
            tempc -= 1;
            break;

        } else if ((char) toupper(userInput) == 'C') {
            tempr += 1;
            tempc += 1;
            break;

        } else if ((char) toupper(userInput) == 'S') {
            tempr = r;
            tempc = c;
            break;
        } else {
            cout << "Invalid key please try again";
            continue;
        }
    }
    Board::getBoard()->moveMeTo(tempr, tempc);
}

/* Then the Robot class methods */
char Robot::display( ) {
    cout<<"R";
}

/*Basic robot AI
 * Finds the position of the player and moves one space
 * closer to them */
void Robot::move( int r, int c ){

    int playerRow = 0;
    int playerCol = 0;
    int robotRow = r;
    int robotCol = c;

    Board::getBoard()->getPlayerPosition(playerRow,playerCol); //getting player pos

    /*basic algorithm to move robot depending on its location in respect
     * to the player*/
    if(r == playerRow){
        if(c>playerCol && c<NCOLS-2){
            robotCol--;
        }
        else{
            robotCol++;
        }
    }
    else if(c == playerCol){
        if(r>playerRow && r<NROWS -2){
            robotRow--;
        }
        else
            robotRow++;
    }
    else if(r<playerRow && r>0){
        robotRow++;
        if(c<playerCol && c>0){
            robotCol++;
        }
        else{
            robotCol--;
        }
    }
    else if(r>playerRow && r<NROWS-2) {
        robotRow--;
        if(c<playerCol && c<NCOLS-2){
            robotCol++;
        }
        else{
            robotCol--;
        }
    }

    Board::getBoard()->moveMeTo(robotRow, robotCol); // calling moveMeTo to move the robot
}



/*The Mine class method*/

char Mine::display( ) { //displays a mine piece
    cout<<"*";
}

bool Mine::isMine() { //checking weather a piece is a mine or not
    return true;
}

/* The Brick class methods */

char Brick::display( ) { //displays a brick wall pieace
	cout<<"#";
}

bool Brick::isBarrier() { // checking if a piece is a wall no not
    return true;
}

/* The Space class methods */

char Space::display( ) {
    cout<<" ";
}

bool Space::isSpace() { // Checking if a piece is a space
    return true;
}


