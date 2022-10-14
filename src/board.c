#include <stdio.h>
#include "../include/board.h"
#include "../include/console.h"

/*
* **Requires**: i and j to be positive indices within bounds
* **Effects**: Returns value at [i][j]
*/
int get(int i, int j, int* board)
{
	return board[i * BOARD_WIDTH + j];
}

/*
* **Requires**: i and j to be positive indices within bounds
* **Effects**: Set element at [i][j] to given value
*/
void set(int i, int j, int value, int* board)
{
	board[i * BOARD_WIDTH + j] = value;
}

void reset(int* board)
{
	for (int i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
		board[i] = 0;
	}
}

/*
* Helper method for local use. Draws a horizontal line on the screen.
*/
void hozLine()
{
	if (CENTER_HOZ) {
		centerline(BOARD_WIDTH * 3);
	}
	for (int i = 0; i < BOARD_WIDTH * 3; i++) {
		printBlue("-");
	}
	printf("\n");
}

/*
* Prints out the game board to the screen.
*/
void show(int* board)
{
	if (CENTER_VER) {
		centerTextVer(14);
	}

	hozLine();
	for (int i = 0; i < BOARD_HEIGHT-1; i++) {
		if (CENTER_HOZ) {
			centerline(BOARD_WIDTH * 3);
		}

		for (int j = 0; j < BOARD_WIDTH; j++) {
			int value = get(i, j, board);

			if (value == 0) {
				printBlue("|");
				printf("%d", value);
				printBlue("|");
			}
			else if (value == 1) {
				printBlue("|");
				printIntRed("%d", value);
				printBlue("|");
			}
			else {
				printBlue("|");
				printIntYellow("%d", value);
				printBlue("|");
			}
		}
		printf("\n");
	}
	hozLine();
}

/*
* Prints out the game board to the screen but also highlights the winning line in green.
*/
void showWinningLine(int row, int col, int dir_x, int dir_y, int* board)
{
	if (CENTER_VER) {
		centerTextVer(14);
	}

	hozLine();
	int green = 0;
	for (int i = 0; i < BOARD_HEIGHT - 1; i++) {
		if (CENTER_HOZ) {
			centerline(BOARD_WIDTH * 3);
		}

		for (int j = 0; j < BOARD_WIDTH; j++) {
			int value = get(i, j, board);
			if (i == row && col == j && green < 4) {
				printBlue("|");
				printIntGreen("%d", value);
				printBlue("|");
				row += dir_y;
				col += dir_x;
				green++;
			}
			else if (value == 0) {
				printBlue("|");
				printf("%d", value);
				printBlue("|");
			}
			else if (value == 1) {
				printBlue("|");
				printIntRed("%d", value);
				printBlue("|");
			}
			else {
				printBlue("|");
				printIntYellow("%d", value);
				printBlue("|");
			}
		}
		printf("\n");
	}
	hozLine();
}

/*
* **Requires**: The given column to be a postive index within bounds of the board
*/
int numPiecesInCol(int col, int* board)
{
	return get(BOARD_HEIGHT - 1, col, board);
}

/*
* **Requires**: The given column to be a postive index within bounds of the board
*/
int isFullColumn(int col, int* board)
{
	if (numPiecesInCol(col, board) == BOARD_HEIGHT - 1) {
		return 1;
	}
	return 0;
}

/*
* **Requires**: The given column to be a postive index within bounds of the board
* **Effects**: The next empty slot in given column
*/
int nextEmptyRow(int col, int* board)
{
	return BOARD_HEIGHT - 2 - numPiecesInCol(col, board);
}