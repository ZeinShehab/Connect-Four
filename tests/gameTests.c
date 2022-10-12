#include <stdio.h>
#include "../include/game.h"
#include "gameTests.h"
#include "tests.h";
#include "../include/board.h"

/**
	Test Cases for the functions in Game.c file.
*/


/*
* testGetPlayerMove function systematically tests the functionality of "getPlayerMove" function. 
* BOUNDRY CASSES: 
* Value:						-1			0			8			100			-2			 5
* Expected Varified Restult: try again		try again	try again	try again	try again	Update Table
*/
int testGetPlayerMove() {
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	reset(board);
	/*
	* Manually Entering the Values of BOUNDRY CASES. 
	* The Expected Behavior: the function should keep asking untill we make a valid move.
	*/
	return 0; 
}
/*
* Checks the given board for any 4 consecutive pieces in any direction.
* Will return 0 if there is no winner otherwise it returns the number of the player who won.
* int checkWin(int row, int col, int player, int* board)
*/

/*
*Test Function for checkWin function. 
* 
*/

int testCheckWin() {
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	reset(board);
	
	//Horizontal Test
	set(1, 1, 1, board);
	set(1, 2, 1, board);
	set(1, 3, 1, board);
	set(1, 4, 1, board);
	
	show(board);
	printf("The Wincheck returns: %d", checkWin(1, 3, 1, board));

	/*
	*Diagonal Test: 
	* 3 CASES: 
	* 1. the winning Move (W = 1) is on the upper edge of the diagonal line. (passed)
			|0||0||0||0||0||0||0|
            |0||0||0||0||0||0||0|
            |0||0||0||w||0||0||0|
            |0||0||1||2||0||0||0|
            |0||1||2||1||0||0||0|
            |1||2||1||2||0||0||0|
	* 2. The winning Move is on the Lower edge of the diagonal line. (Passed)
			|0||0||0||0||0||0||0|
            |0||0||0||0||0||0||0|
            |0||0||0||1||0||0||0|
            |0||0||1||2||0||0||0|
            |0||1||2||1||0||0||0|
            |w||2||1||2||0||0||0|
	* 3. The winning Move is in the middle of the diagonal line. (Failed)
			|0||0||0||0||0||0||0|
            |0||0||0||0||0||0||0|
            |0||0||0||1||0||0||0|
            |0||0||w||2||0||0||0|
            |0||1||2||1||0||0||0|
            |1||2||1||2||0||0||0|
			OR
			|0||0||0||0||0||0||0|
			|0||0||0||0||0||0||0|
			|0||0||0||1||0||0||0|
			|0||0||1||2||0||0||0|
			|0||w||2||1||0||0||0|
			|1||2||1||2||0||0||0|
	*/
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
	set(2, 3, 1, board);

	show(board);
	printf("The Wincheck returns: %d", checkWin(3, 2, 1, board));
	reset(board); 

	/*
	*Vertical Line Test:
	* 3 CASES:
	* 1. the winning Move (W = 1) is on the upper edge of the vertical line. (failed)
			|0||0||0||0||0||0||0|
            |0||0||0||0||0||0||0|
            |0||w||0||0||0||0||0|
            |0||1||0||0||0||0||0|
            |0||1||0||0||0||0||0|
            |0||1||0||0||0||0||0|
            ---------------------
            |0||4||0||0||0||0||0|
            ---------------------
	* 2. The winning Move is on the Lower edge of the vertical line. (failed)
			|0||0||0||0||0||0||0|
            |0||0||0||0||0||0||0|
            |0||1||0||0||0||0||0|
            |0||1||0||0||0||0||0|
            |0||1||0||0||0||0||0|
            |0||w||0||0||0||0||0|
            ---------------------
            |0||4||0||0||0||0||0|
            ---------------------
	* 3. The winning Move is in the middle of the vertical line. (Failed)
			|0||0||0||0||0||0||0|
            |0||0||0||0||0||0||0|
            |0||1||0||0||0||0||0|
            |0||1||0||0||0||0||0|
            |0||w||0||0||0||0||0|
            |0||1||0||0||0||0||0|
            ---------------------
            |0||4||0||0||0||0||0|
            ---------------------
			OR
			|0||0||0||0||0||0||0|
			|0||0||0||0||0||0||0|
			|0||1||0||0||0||0||0|
			|0||w||0||0||0||0||0|
			|0||1||0||0||0||0||0|
			|0||1||0||0||0||0||0|
			---------------------
			|0||4||0||0||0||0||0|
			---------------------
	*/
	set(5, 1, 1, board);
	set(4, 1, 1, board);
	set(3, 1, 1, board);
	set(2, 1, 1, board);
	set(6, 1, 4, board);
	show(board);
	printf("The Wincheck returns: %d", checkWin(3, 1, 1, board));

}

void runGameTests()
{
	testGetPlayerMove(); 
	testCheckWin();
	
}