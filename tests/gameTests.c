#include <stdio.h>
#include "../include/game.h"
#include "gameTests.h"
#include "tests.h";
#include "../include/board.h"

/**
	Test Cases for the functions in Game.c file.
*/


/*
* MANUALLY TESTED!
* testGetPlayerMove function systematically tests the functionality of "getPlayerMove" function. 
* TEST CASSES: 
* INPUT DOMAIN (+Z)
* CASE 1: when the user Enters 0. (Expected: try again) (passed)
* CASE 2: when the user Enters 8. (Expected: try again) (passed)
* CASE 3: when the user Enters 7. (Expected: update board) (passed)
* CASE 4: when the user Enters 1. (Expected: update board) (passed)
* CASE 5: when the user Enters -1.(Expected: try again) (passed).  						-1			0			8			100			-2			 5
* Expected Varified Restult: try again		try again	try again	try again	try again	Update Table
*/
int testGetPlayerMove() {
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	reset(board);
	getPlayerMove(1, board);
	/*
	* MANUALLY TESTED.
	* CASE 1:.
	* CASE 2:
	* CASE 3:
	* CASE 4:
	* CASE 5:
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



/*
*Test Function for CheckTie(): 
* TEST CASES: 
* CASE 1: when the board is full and playerOneTime is less than PlayerTwoTime. (Expected: 1) (passed)
* CASE 2: Whenthe board is full and playerOneTime is greater than PlayerTwoTime. (Expected: 2) (passed)
* CASE 3: When the board is not full. (Expected 0) (passed)
*/
int testCheckTie() {
	//CASE 1: 
	if ((checkTie(7 * 6, 2, 4)) != 1) {
		return 1;
	}

	//CASE 2:
	if ((checkTie(7 * 6, 2, 1)) != 2) {
		return 2; 
	}


	//CASE 3:
	if ((checkTie(7 * 5, 2, 1)) != 0) {
		return 3;
	}
	
	return 0; 
}


/*
* MANUALLY TESTED!
* TEST function for winIFWinner(int player): 
* CASE 1: When the value is 1. (Expected: 1 wins) (passed)
* CASE 2: when the value is 2. (Expected: 2 wins) (passed)
* CASE 3: when the value is 0. (Expected: No Action) (Passed)
* CASE 4: when the value is 3  (Expected: No Action) (Passed)
*/
/*
int testWinIfWinner() {
	
	//CASE 1:
	winIfWinner(1);
	//CASE 2:
	winIfWinner(2);
	//CASE 3:
	winIfWinner(0);
	//CASE 4:
	winIfWinner(3);
	return 0;
	
}
*/


/*
* MANUALLY TESTED!
* TEST function for run().
* CASE 1: Assuming the other tests are done. This function should start the game loop. (passed) 
* CASE 2: Assuming the other tests are done. This function should stop when board is full and announce winner. (passed). 
*/
void testRun() {
	//CASE 1:
	run();
	//CASE 2:
	run();
}

void runGameTests()
{
	//testGetPlayerMove(); 
	//testCheckWin();
	//printf("returned: %d", testCheckTie());
	//testWinIfWinner();
	/*
	int t = 2;
	printf("you took %d units of time. ", 2);
	playerTurn(1, 2, &t);
	printf("you took %d units of time. ", 2);
	*/


}
