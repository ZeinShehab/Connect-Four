#include <stdio.h>
#include "../include/board.h"


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
	for (int i = 0; i < BOARD_WIDTH * 3; i++) {
		printf("-");
	}
	printf("\n");
}

void show(int* board)
{
	hozLine();
	for (int i = 0; i < BOARD_HEIGHT-1; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			printf("|%d|", get(i, j, board));
		}
		printf("\n");
	}
	hozLine();

	// -- FOR DEBUGGING REMOVE LATER -- //
	for (int i = 0; i < BOARD_WIDTH; i++) {
		printf("|%d|", get(BOARD_HEIGHT - 1, i, board));
	}
	printf("\n");
	hozLine();
	// -- FOR DEBUGGING REMOVE LATER -- //
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