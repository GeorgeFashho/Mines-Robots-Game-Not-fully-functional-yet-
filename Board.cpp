/**
 * Board.cpp - Source code file for the Board class and all its subclasses.
 * Written by: George Fashho [6/9/2022]
 */


#include "Board.h"
#include "Pieces.h"
#include "Exceptions.h"


Board * Board::theBoard = NULL; //pointing the board to NULL

Board::Board( ) {
    /*initializing Board variables*/
    nRows = NROWS;
    nCols = NCOLS;
    playerRow = 0;
    playerCol = 0;
    currentTurn = 1;

    /*looping through all possible board pieces and setting them to space
     * for now as well as initializing the last turn played for all pieces*/
    for(int row_ = 0 ; row_ < NROWS ; row_++){
        for(int col_ = 0 ; col_ < NCOLS ; col_++){
            pieces[row_][col_] = new Space();
            lastTurnPlayed[row_][col_] = 0;
        }
    }

    srand(time(nullptr));  //seeding the random integers

    /*creating board pieces: 1 Brick/1 Mine/1 Player/ 4 Robots*/
    for(int i=0;i<9;i++){

        /*getting a new random integer every loop*/
       int randRow = rand()%((NROWS-1)-0 + 1) + 0;
       int randCol = rand()%((NCOLS-1)-0 + 1) + 0;

       if(i==6) {
           pieces[randRow][randCol] = new Brick();
       }
       else if(i==7) {
           pieces[randRow][randCol] = new Mine();
       }
       else if(i==8) {
           pieces[randRow][randCol] = new Player();
           playerRow = randRow;
           playerCol = randCol;
       }
       else
           pieces[randRow][randCol] = new Robot();
    }
}

/*Checking if a board already exists; if not create a new one
 * else return the board that was already created*/
Board * Board::getBoard( ) {
    if(theBoard == NULL){
       theBoard = new Board() ;
    }
    return theBoard;
}

/* Outputting all the board pieces and spaces (printing board)*/
void Board::display( ) {

    for(int i = 0 ; i<nRows ; i++){
        for(int j = 0 ; j < nCols ; j++){
            pieces[i][j]->display();
        }
        cout<<"\n";
    }
}

/* while loop to control gameplay:
 * 1st: displaying the board
 * 2nd: allowing the player piece to make the first move
 * 3rd: looping through all the pieces in the board and asking them to move
 *      try is called to try the board pieces and calls upon move()
 * 4th: moveMeTo() determines if the move is valid or not and will throw exceptions at
 *      play(), who will catch the exceptions and take an action
 * 5th: incrementing currentTurn
 *
 * **For loop continues until either the player is killed by a robot or all robots die** */
void Board::play( ) {

    int numRobots = 4;

    while (true) {
            if(numRobots == 0){
                cout<<"     All robots are dead, Congratulations you won!";
                break;
            }

            cout<<"       There are "<<numRobots<< " Robots remaining, what is your move?\n"  ;
            display();
            row = playerRow;
            col = playerCol;

            lastTurnPlayed[playerRow][playerCol] +=1;

            pieces[playerRow][playerCol]->move(playerRow,playerCol); //calling player to make a move

            for (row = 0; row < nRows; row++) { //looping through all board pieces
                for (col = 0; col < nCols; col++) {

                    if (lastTurnPlayed[row][col] < currentTurn) {

                        lastTurnPlayed[row][col]+=1; // incrementing to show that piece has already played
                        try {
                            pieces[row][col]->move(row, col);
                        }
                        /*Catching exceptions thrown by moveMeTo()*/
                        catch (InvalidMove e ) {
                            cout<<"A piece has moved more than one space!";
                            continue;
                        }
                        catch( SpaceUnavailable g){
                            cout<<"You hit a barrier or attempted to go out of bounds, Please try again";
                            continue;
                        }
                        catch(Collision f){
                            int newRow = 0 ;
                            int newCol = 0 ;
                            f.getLocation(newRow,newCol);
                            if(!pieces[newRow][newCol]->isBarrier()){
                                pieces[row][col] = new Space();
                            }
                            else if(!pieces[newRow][newCol]->isMine() && !pieces[newRow][newCol]->isBarrier() &&
                                    (pieces[newRow][newCol] != pieces[playerRow][playerCol])){
                                pieces[row][col] = new Mine();
                                numRobots--;
                            }
                            else if((pieces[newRow][newCol] = pieces[playerRow][playerCol]) ){
                                cout<<"         The robot has killed the player piece\n"
                                <<"                         YOU LOST!";
                                break;
                            }
                            continue;
                        }
                    }
                }
            }
            currentTurn++;
        }
}//end play()


/* Responsible for switching board piece positions and throwing exceptions
 * Firstly must check if the move is valid
 * @InvalidMove is thrown when the piece moves more than one space
 * @SpaceUnavailable is thrown when robot or player runs into a barrier or out
 * of bounds
 * @Collision is thrown when 2 pieces collide with each other
 *
 * If move is valid then the two pieces switch positions*/
void Board::moveMeTo( int newRow, int newCol ) {

    if(newRow>row+1 || newCol > col+1){
        throw InvalidMove("Piece moved more than one space");

    }
    if(pieces[newRow][newCol]->isBarrier() || newRow <0 ||
    newRow ==NROWS || newCol < 0 || newCol == NCOLS ){
        throw SpaceUnavailable("a","Barrier Hit! Or attempted to move out of bounds!");
    }

    if(!(pieces[newRow][newCol]->isSpace())){
        throw Collision("Collision","2 pieces collided with eachother!",newRow,newCol);
    }

//    if(pieces[newRow][newCol])
    if(row == playerRow && col == playerCol){ //finding the player piece location
        playerRow =newRow;
        playerCol =newCol;
    }

    Piece * temp = pieces[newRow][newCol] ;     //new temp board piece to hold new position
    pieces[newRow][newCol] = pieces[row][col];  //setting new board piece to the old one
    pieces[row][col] = temp;            //setting old board piece to the new one
    temp = NULL;        //pointing temp back to NULL for safety
}

/*returns the current location of the player piece*/
void Board::getPlayerPosition( int & row, int & col ) {
    row = playerRow;
    col = playerCol;
}

