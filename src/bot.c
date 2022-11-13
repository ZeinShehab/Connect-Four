#include "../include/bot.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"

int score_map[BOARD_WIDTH * (BOARD_HEIGHT - 1)] =
{
									 3, 4, 5, 7, 5, 4, 3,
									 4, 6, 8, 10, 8, 6, 4,
									 5, 8, 11, 13, 11, 8, 5,
									 5, 8, 11, 13, 11, 8, 5,
									 4, 6, 8, 10, 8, 6, 4,
									 3, 4, 5, 7, 5, 4, 3 
};
int evaluate(int* board, int player) {
	int sum1 = 0;
	int sum2 = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			if (board[i*7+j] == 1)
				sum1 += score_map[j + i * 7];
			if (board[i*7+j] == 2)
				sum2 += score_map[j + i * 7];
		}
	}
	return (sum1 - sum2) * player == 1 ? 1: -1;
}

int num_occurance(int* board, int player) {
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

int* checkWinn(int row, int col, int player, int* board)
{
	// 4 directions. Horizontal, Vertical, Left diagonal and right diagonal respectively.
	int directions[4][2] = { {0, 1}, {1, 0}, {1, 1}, {1, -1} };

	for (int dir = 0; dir < 4; dir++) {
		int* direction = directions[dir];
		int x = 0;
		int y = 0;

		// Left most position on the left diagonal that the piece falls on
		if (dir == 2) {
			x = col >= row ? col - row : 0;
			y = row >= col ? row - col : 0;
		}
		// Right most position on the right diagonal that the piece falls on
		else if (dir == 3) {
			x = col + row <= BOARD_WIDTH - 1 ? col + row : BOARD_WIDTH - 1;
			y = col + row <= BOARD_WIDTH - 1 ? 0 : col + row - BOARD_WIDTH - 1;
		}
		// Left most position on the horizontal or topmost position on the vertical. Depending on the direction.
		// If we are iterating over the horizontal then the x would be 0 and y would be the row of the last move.
		else {
			x = col * direction[0];
			y = row * direction[1];
		}

		// Iterate through the whole line in current direction and look for 4 consecutive pieces. 
		// Maximum length of a line is 7 so we are at most iterating over 3 extra pieces only.
		int n_pieces = 0;
		while (x < BOARD_WIDTH && x >= 0 && y < BOARD_HEIGHT - 1 && y >= 0) {
			n_pieces = get(y, x, board) == player ? n_pieces + 1 : 0;		// If different piece is found reset counter else increment by 1

			y += direction[0];												// Move x and y in the current direction
			x += direction[1];

			if (n_pieces >= 4) {											// If we have counted four pieces so far we have a winner
				int start_x = x - 4 * direction[1];							// We return information about the winning line such as pos and direction to highlight it in green
				int start_y = y - 4 * direction[0];
				int* winning_line = (int*)malloc(sizeof(int) * 5);

				winning_line[0] = player;
				winning_line[1] = start_y;
				winning_line[2] = start_x;
				winning_line[3] = direction[1];
				winning_line[4] = direction[0];

				return winning_line;
			}
		}
	}
	return NULL;
}

int isValidMovee(int* board, int move)
{
	return board[move] == 0;
}

int isTerminal(int* board)
{
	for (int i = 0; i < 7; i++) {
		if (isValidMovee(board, i)) {
			return 0;
		}
	}
	return 1;
}

int minimax(int* board, int depth, int maximizingPlayer)
{
	if (depth == 0) {
		return evaluate(board, 2);
	}

	if(isTerminal(board)) {
		return 0;
	}

	if (maximizingPlayer) {
		int bestEvaluation = NEG_INF;
		int evaluation = 0;

		for (int i = 0; i < 7; i++) {
			if (!isValidMovee(board, i)) {
				continue;
			}

			int row = nextEmptyRow(i, board);
			set(row, i, 2, board);					// make move

			int* win = checkWinn(row, i, 2, board);
			if (win != NULL) {
				free(win);
				set(row, i, 0, board);
				return POS_INF;
			}

			evaluation = minimax(board, depth - 1, 0);
			set(row, i, 0, board);					// undo move

			if (evaluation > bestEvaluation) {
				bestEvaluation = evaluation;
			}
		}
		return bestEvaluation;
	}

	else {
		int bestEvaluation = POS_INF;
		int evaluation = 0;

		for (int i = 0; i < 7; i++) {
			if (!isValidMovee(board, i)) {
				continue;
			}

			int row = nextEmptyRow(i, board);
			set(row, i, 1, board);

			int* win = checkWinn(row, i, 1, board);
			if (win != NULL) {
				free(win);
				set(row, i, 0, board);
				return NEG_INF;
			}

			evaluation = minimax(board, depth - 1, 1);
			set(row, i, 0, board);

			if (evaluation < bestEvaluation) {
				bestEvaluation = evaluation;
			}
		}
		return bestEvaluation;
	}
}

int getComputerMove(int* board)
{
	int depth = 3;
	int bestMove = 3;
	int oldScore = 0;

	for (int i = 0; i < 7; i++) {

		if (!isValidMovee(board, i)) {
			continue;
		}

		int row = nextEmptyRow(i, board);
		set(row, i, 2, board);

		int* win = checkWinn(row, i, 2, board);
		if (win != NULL) {
			free(win);
			set(row, i, 0, board);
			return i;
		}

		int newScore = -minimax(board, depth, 0);
		set(row, i, 0, board);

		if (newScore > oldScore) {
			oldScore = newScore;
			bestMove = i;
		}
	}

	for (int i = 0; i < 7; i++) {
		if (!isValidMovee(board, i)) {
			continue;
		}

		int row = nextEmptyRow(i, board);
		set(row, i, 1, board);

		int* win = checkWinn(row, i, 1, board);
		if (win != NULL) {
			free(win);
			set(row, i, 0, board);
			return i;
		}
		set(row, i, 0, board);
	}
	return bestMove;
}