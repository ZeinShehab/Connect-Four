#pragma once

#define BOARD_HEIGHT 7			// One extra row to track number of pieces in each column.
#define BOARD_WIDTH 7
#define CENTER_HOZ 1			// Center board horizontally
#define CENTER_VER 0			// Center board vertically

/* 
Return element at row i and column j.
*/
int get(int i, int j, int* board);

/* 
Set element at row i and column j to given value.
*/
void set(int i, int j, int value, int* board);

/* 
Fill board with zeros
*/
void reset(int* board);

/*
Print out the game board to the screen.
*/
void show(int* board);

/*
Returns the number of pieces already placed in given column.
*/
int numPiecesInCol(int col, int* board);

/*
Checks whether the given column contains the maximum number of pieces it fits or not.
*/
int isFullColumn(int col, int* board);

/*
Returns the next empty row in given column where a piece can be placed.
*/
int nextEmptyRow(int col, int* board);