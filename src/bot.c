#include "../include/bot.h"
#include <stdio.h>
#include <stdlib.h>

int score_map[BOARD_WIDTH * BOARD_HEIGHT] = { 3, 4, 5, 7, 5, 4, 3,
									 4, 6, 8, 10, 8, 6, 4,
									 5, 8, 11, 13, 11, 8, 5,
									 5, 8, 11, 13, 11, 8, 5,
									 4, 6, 8, 10, 8, 6, 4,
									 3, 4, 5, 7, 5, 4, 3 };

int evaluate(int* board) {
	int sum = 0;
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (board[i*BOARD_HEIGHT+j] == 1)
				sum += score_map[j + i * BOARD_WIDTH];
			if (board[i*BOARD_HEIGHT+j] == 2)
				sum -= score_map[j + i * BOARD_WIDTH];
		}
	}
	return sum;
}