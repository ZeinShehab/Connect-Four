#include <stdio.h>
#include "boardTests.h"
#include "../include/board.h"
#include "tests.h";

int testGetSet()
{
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	reset(board);

	// testing at the top left of the board
	set(0, 0, 9, board);
	int tc1 = get(0, 0, board);

	if (tc1 != 9) {
		return 1;
	}

	// testing at the middle of the board
	set(4, 4, 9, board);
	int tc2 = get(4, 4, board);

	if (tc2 != 9) {
		return 2;
	}

	// testing at the bottom right of the board
	set(BOARD_WIDTH - 1, BOARD_HEIGHT - 1, 20, board);
	int tc3 = get(BOARD_WIDTH - 1, BOARD_HEIGHT - 1, board);

	if (tc3 != 20) {
		return 3;
	}

	return 0;
}

int testIsFullColumn() 
{
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	reset(board);

	//testing in case given an input out of bound
	int tc1 = isFullColumn(8, board);
	if (tc1 != 0) {
		return 1;
	}

	// filling out the top left, middle and the bottom right of the board 
	for (int i = 0; i < BOARD_HEIGHT - 1; i++) {
		set(i, 0, 1, board);
		set(i, 3, 1, board);
		set(i, 6, 1, board);
	}

	// testing top left
	int tc2 = isFullColumn(0, board);
	if (tc2 != 0) {
		return 2;
	}

	// testing middle
	int tc3 = isFullColumn(3, board);
	if (tc3 != 0) {
		return 3;
	}

	//testing bottom right
	int tc4 = isFullColumn(6, board);
	if (tc4 != 0) {
		return 4;
	}
	return 0;
}

int testReset() 
{
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	reset(board);

	// filling the diagonal line in the board with random variables
	for (int i = 0; i < BOARD_HEIGHT - 1; i++) {
		set(i, i, i, board);
	}
	reset(board);

	// testing top left 
	int tc1 = get(0, 0, board);
	if (tc1 != 0) {
		return 1;
	}

	// testing middle 
	int tc2 = get(3, 3, board);
	if (tc2 != 0) {
		return 2;
	}

	// testing bottom right
	int tc3 = get(BOARD_WIDTH-1, BOARD_HEIGHT-1, board);
	if (tc3 != 0) {
		return 3;
	}
	return 0;
}
int testnumPiecesInCol() {
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	reset(board);

	// filling out the last row in the board with random value in different columns
	set(6, 0, 2, board);
	set(6, 2, 3, board);
	set(6, 5, 4, board);



	// testing first column
	int tc1 = numPiecesInCol(0, board);

	if (tc1 != 2) {
		return 1;
	}
	
	//testing middle column
	int tc2 = numPiecesInCol(2, board);

	if (tc2 != 3) {
		return 2;
	}

	//testing column 5(one before last)
	int tc3 = numPiecesInCol(5, board);
	
	if (tc3 != 4) {
		return 3;
	}

	return 0;
}
int testnextEmptyRow() 
{
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	reset(board);

	// filling the board with random variable at different columns
	set(6, 0, 1, board);
	set(6, 2, 3, board);
	set(6, 4, 4, board);
	set(6, 6, 5, board);

	// testing the first column
	int tc1 = nextEmptyRow(0, board);
	if (tc1 != 4) {
		return 1;
	}

	// testing the 3rd column
	int tc2 = nextEmptyRow(2, board);
	if (tc2 != 2) {
		return 2;
	}

	// testing the 5th column
	int tc3 = nextEmptyRow(4, board);
	if (tc3 != 1) {
		return 3;
	}

	//testing the last column
	int tc4 = nextEmptyRow(6, board);
	if (tc4 != 0) {
		return 4;
	}

	return 0;

}

/*
* Runs all board tests and reports their results.
*/
void runBoardTests()
{
	printTestResult("NextEmptyRow test", testnextEmptyRow());
	printTestResult("GetSet test", testGetSet());
	printTestResult("IsFullColumn test", testIsFullColumn());
	printTestResult("Reset test", testReset());
	printTestResult("NumPiecesInCol test", testnumPiecesInCol());
}