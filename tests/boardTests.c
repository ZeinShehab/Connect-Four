#include <stdio.h>
#include "boardTests.h"
#include "../include/board.h"

int testGetSet()
{
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	reset(board);

	set(0, 0, 9, board);
	int x = get(0, 0, board);

	if (x != 9) {
		printf("testGetSet failed at test case 1:\n Returned Output: 7, Expected Output: 9");
		return 1;
	}
	return 0;
}

void runBoardTests()
{
	int testResult = testGetSet();
	if (testResult != 0) {
		printf("TestGetSet failed at test case: %d\n", testResult);
	}
	else {
		printf("TestGetSet passed!\n");
	}
}