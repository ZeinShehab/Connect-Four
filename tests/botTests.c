#include "botTests.h"
#include "tests.h"
#include "../include/bot.h"

#include "../include/board.h"



/*
* **Requires**: nothing
* **Effects**: Returns the number of the test case in case it fails or returns 0 otherwise. 
*/

int Test_getComputerMove() {

	// This function includes 5 automatic test cases each systematically choosen from specific domains. 
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	int ExpectedResult = 3; 

	// Test Case1 : blocking move test on all difficulty levels. 
	reset(board);
	set(5, 0, 1, board);
	set(5, 1, 2, board);
	set(4, 1, 1, board);
	set(5, 2, 1, board);
	set(4, 2, 2, board);
	set(3, 2, 1, board);
	set(5, 3, 2, board);
	set(4, 3, 1, board);
	set(3, 3, 2, board);
	int tc1[3];
	int depths[3] = { 2,6,10 };
	for (int i = 0; i < 3; i++) {
		tc1[i] = getComputerMove(board, depths[i]);
	} 
	
	for (int i = 0; i < 3; i++) {
		if (tc1[i] != ExpectedResult) {
			return 1;
		}	
	}

	//Test Case2: Winning Move Test for all difficulty levels.
	reset(board);
	set(5, 0, 1, board);
	set(5, 1, 2, board);
	set(4, 1, 1, board);
	set(5, 2, 1, board);
	set(4, 2, 2, board);
	set(3, 2, 1, board);
	set(5, 3, 2, board);
	set(4, 3, 1, board);
	set(5, 0, 1, board);
	set(4, 0, 1, board);
	set(4, 1, 1, board);
	set(5, 5, 2, board);
	set(5, 4, 2, board);

	int tc2[3];
	for (int i = 0; i < 3; i++) {
		tc2[i] = getComputerMove(board, depths[i]);
	}
	ExpectedResult = 6; 
	for (int i = 0; i < 3; i++) {

		if (tc2[i] != ExpectedResult) {
			return 2;
		}
	}

	//Test Case 3: palying from right perspective test (the bot knows whos turn it is and plays accordingly) for all difficulty levels. 
	reset(board);
	set(5, 0, 1, board);
	set(4, 0, 1, board);
	set(3, 0, 1, board);
	set(5, 6, 2, board);
	set(4, 6, 2, board);
	set(3, 6, 2, board);


	int tc3[3];
	for (int i = 0; i < 3; i++) {
		tc3[i] = getComputerMove(board, depths[i]);
	}
	ExpectedResult = 0;
	for (int i = 0; i < 3; i++) {
		if (tc3[i] != ExpectedResult) {
			return 3;
		}
	}

	//Test Case 4: Logical Move Test for all difficulty levels when there is no wining or blocking move (Easy Move). 
	reset(board);
	set(5, 3, 1, board);
	set(4, 3, 2, board);
	int tc4[3];
	for (int i = 0; i < 3; i++) {
		tc4[i] = getComputerMove(board, depths[i]);
	}
	ExpectedResult = 3;
	for (int i = 0; i < 3; i++) {
		if (tc4[i] != ExpectedResult) {
			return 4;
		}
	}

	//Test Case 5: Logical Move Test for all difficulty levels when there is no wining or blocking move (Hard Move).
	reset(board);
	set(5, 3, 1, board);
	set(4, 3, 2, board);
	set(5, 4, 1, board);
	int tc5[3];
	for (int i = 0; i < 3; i++) {
		tc5[i] = getComputerMove(board, depths[i]);
	}

	//The easy level is expected to be dumb and give the player a chance to win otherwise the testCase 5 fails. 
	ExpectedResult = 2;
	if (tc5[0] == 2)
		return 5;

	//The medium and hard levels are expected to think ahead and block the opportunity to win. 
	for (int i = 1; i < 3; i++) {
		if (tc5[i] != ExpectedResult) {
			return 5;
		}
	}

	return 0; 
}

/*
* **Requires**: nothing
* **Effects**: runs the board test and prints if it passed of failed. 
*/
void runBotTests()
{
	printTestResult("getComputerMove test", Test_getComputerMove());
}