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
* CASE 5: when the user Enters -1.(Expected: try again) (passed).
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


//Auxiliry test Function.
int testCheckWin() {
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	reset(board);
	
	//Horizontal Test
	set(1, 1, 1, board);
	set(1, 2, 1, board);
	set(1, 3, 1, board);
	set(1, 4, 1, board);

	for (int i = 1; i < 5; i++) {

		if ((checkWin(i, 1, 1, board) != 1)) {
			return 1;
		}
	}
	

	//show(board);

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

	for (int i = 2, j = 3; i < 6 && j >= 0; i++, j--) {
		if (checkWin(i, j, 1, board) != 1) {
			return 2;
		}
	}

	//show(board);
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
	for (int i = 2; i < 6; i++) {
		
		if ((checkWin(i, 1, 1, board) != 1)) {
			return 3; 
		}
	}

}


/*
* AUTOMATICALLY TESTED! 
*TEST function for checkwin():
* TEST CASES:
* CASE 1: Checks all four nodes of Horizonal line individually. (*---)(-*--)(--*-)(---*)
* CASE 2: checks all four nodes of diagonal line individually.
* CASE 3: checks all four nodes of vertical line individually. 
*
*/
void TestCheckWin() {
	int result = testCheckWin();
	if (result == 1) {
		printf("Horizontal Line test Failed. \n");
	}else if (result == 2) {
		printf("Diagonal Line test Failed. \n");
	}
	else if (result == 3) {
		printf("Vertical Line test failed. \n");
	}
	else {
		printf("CheckWin Tests passed. \n");
	}
}






//Auxiliry function
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
* AUTOMATICALLY TESTED!
*Test Function for CheckTie():
* TEST CASES:
* CASE 1: when the board is full and playerOneTime is less than PlayerTwoTime. (Expected: 1) (passed)
* CASE 2: Whenthe board is full and playerOneTime is greater than PlayerTwoTime. (Expected: 2) (passed)
* CASE 3: When the board is not full. (Expected 0) (passed)
*/

void TestCheckTie() {
	int result = testCheckTie();
	if (result == 1) {
		printf("TestCheckTie Case 1 Failed. \n");
	}
	else if (result == 2) {
		printf("TestCheckTie Case 2 Failed. \n");
	}
	else if (result == 3) {
		printf("TestCheckTie Case 3 failed. \n");
	}
	else {
		printf("TestCheckTie Tests passed. \n");
	}
}


/*
* MANUALLY TESTED!
* TEST function for winIFWinner(int player): 
* CASE 1: When the value is 1. (Expected: 1 wins) (passed)
* CASE 2: when the value is 2. (Expected: 2 wins) (passed)
* CASE 3: when the value is 0. (Expected: No Action) (Passed)
* CASE 4: when the value is 3  (Expected: No Action) (Passed)
*/
 //int testWinIfWinner() {
	 /*
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
	//testGetPlayerMove(); MANUALLY TESTED
	TestCheckWin();
	TestCheckTie();
	//testWinIfWinner(); MANUALLY TESTED
	//testRun();	MANUALLY TESTED
	


}
