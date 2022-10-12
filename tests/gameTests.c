#include <stdio.h>
#include "../include/game.h"
#include "tests.h"
#include "gameTests.h"
#include "../include/board.h"

int testisValidMove()
{
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	reset(board);

	// testing an input outside the bounds
	int tc1 = isValidMove(-1, board);
	if (tc1 != 0) {
		return 1;
	}

	int tc2 = isValidMove(10, board);
	if (tc2 != 0) {
		return 2;
	}

	// filling out the first column
	set(6, 0, 6, board);

	int tc3 = isValidMove(0, board);
	if (tc3 != 0) {
		return 3;
	}

	// filling out column 3
	set(6, 3, 6, board);
	
	int tc4 = isValidMove(3, board);
	if (tc4 != 0) {
		return 4;
	}

	// filling the last column
	set(6, 6, 6, board);
	
	int tc5 = isValidMove(6, board);
	if (tc5 != 0) {
		return 5;
	}
}

int testmakeMove()
{
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	reset(board);

	// testing first column
	makeMove(5, 0, 2, board);
	int tc1 = get(5, 0, board);
	if (tc1 != 2) {
		return 1;
	}
	
	// testing 5th column
	makeMove(1, 5, 1, board);
	int tc2 = get(1, 5, board);
	if (tc2 != 1) {
		return 2;
	}
	
	// testing at 3rd riow and 4th column
	makeMove(2, 3, 2, board);
	int tc3 = get(2, 3, board);
	if (tc3 != 2) {
		return 3;
	}

	return 0;
}

void runGameTests()
{
	printTestResult("isValidMove test", testisValidMove());
	printTestResult("makeMove test", testmakeMove());
}
