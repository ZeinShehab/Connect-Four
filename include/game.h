#pragma once

/*
* Checks if the specified column is a valid move choice in the given board.
*/
int isValidMove(int col, int* board);

/*
* Plays out the given move on the board.
*/
void makeMove(int row, int col, int player, int* board);

/*
* Returns a column to make user move in
*/
int getPlayerMove(int player, int* board);

/*
* Checks if any player has won in the current state of the board.
*/
int checkWin(int* board);

/*
* Ends the game and declares a winner if given player is a winner.
*/
void winIfWinner(int player);

/*
* Runs the main game loop.
*/
void run();