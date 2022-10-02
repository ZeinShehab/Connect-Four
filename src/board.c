#include <stdio.h>
#include "../include/board.h"

int get(int i, int j, int* board)
{
	return board[i * BOARD_WIDTH + j];
}

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

int numPiecesInCol(int col, int* board)
{
	return get(BOARD_HEIGHT - 1, col, board);
}

int isFullColumn(int col, int* board)
{
	if (numPiecesInCol(col, board) == BOARD_HEIGHT - 1) {
		return 1;
	}
	return 0;
}

int nextEmptyRow(int col, int* board)
{
	return BOARD_HEIGHT - 2 - numPiecesInCol(col, board);
}