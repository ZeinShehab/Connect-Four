#include "../include/bot.h"
#include <stdio.h>
#include <stdlib.h>

int score_map[BOARD_WIDTH * BOARD_HEIGHT] = 
{
									 3, 4, 5, 7, 5, 4, 3,
									 4, 6, 8, 10, 8, 6, 4,
									 5, 8, 11, 13, 11, 8, 5,
									 5, 8, 11, 13, 11, 8, 5,
									 4, 6, 8, 10, 8, 6, 4,
									 3, 4, 5, 7, 5, 4, 3 
};
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
int num_occurance(int* board,int player) {
	int occurance[5] = { 0,0,0,0,0 };
	int occ = 0;
	//score horizantally 
	for (int i = 0; i < BOARD_HEIGHT-1; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (board[i * BOARD_WIDTH + j] == player)
				occ += 1;
			else {
				occurance[occ] += 1;
				occ = 0;
			}	
		}
		occurance[occ] += 1;occ = 0;
	}
	//score vertically
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT-1; j++) {
			if (board[j * BOARD_WIDTH + i] == player)
				occ += 1;
			else {
				occurance[occ] += 1;
				occ = 0;
			}
		}
		occurance[occ] += 1;occ = 0;
	}
	//score diagonally from the bottom half \/
	for (int j = 0; j < BOARD_HEIGHT - 1; j++) {
		for (int i = j; i < BOARD_HEIGHT - 1; i++) {
			if (board[i * BOARD_WIDTH + i - j] == player) {
				occ += 1;
			}
			else {
				occurance[occ] += 1;
				occ = 0;
			}
		}
		occurance[occ] += 1;occ = 0;
		for (int k = 0; k <BOARD_HEIGHT-1-j; k++) {
			if (board[BOARD_WIDTH-1+BOARD_WIDTH*k-k+BOARD_WIDTH*j] == player) {
				occ += 1;
			}
			else {
				occurance[occ] += 1;
				occ = 0;
			}
		}
		occurance[occ] += 1;occ = 0;
	}
	//score diagonally from the top half 
	for (int j = 1; j < BOARD_WIDTH ; j++) {
		for (int i = j; i <BOARD_HEIGHT; i++) {
			if (board[(i - j) * BOARD_WIDTH + i]==player) {
				occ += 1;
			}
			else {
				occurance[occ] += 1;
				occ = 0;
			}
		}
		occurance[occ] += 1;occ = 0;
		for (int k = j; k < BOARD_WIDTH; k++) {
			if (board[k * BOARD_WIDTH - k - j] == player) {
				occ += 1;
			}
			else {
				occurance[occ] += 1;
				occ = 0;
			}
		}
		occurance[occ] += 1;occ = 0;
	}
	return 1000*occurance[4]+100*occurance[3]+10*occurance[2];
}