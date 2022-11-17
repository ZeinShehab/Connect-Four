#include "../include/bot.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"
#include "../include/console.h"

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
			y = col + row <= BOARD_WIDTH - 1 ? 0 : (col + row) - (BOARD_WIDTH - 1);
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

int nextEmptyRoww(int col, int *board) {
	int row = -1;
	for (int i = 0; i < 6; i++) {
		if (board[i * 7 + col] == 0) {
			row = i;
		}
	}
	return row;
}

// prioritize central columns first
int columnOrder[7] = {3, 2, 4, 1, 5, 0, 6};		// columnOrder[i] = WIDTH / 2 + (1 - 2 * (i % 2)) * (i + 1) / 2

int negamax(int* board, int depth, int alpha, int beta)
{
	int sum1 = 0;
	int sum2 = 0;
	for (int i = 0; i < 7 * 6; i++) {
		if (board[i] == 1) {
			sum1++;
		}
		else if (board[i] == 2) {
			sum2++;
		}
	}
	int toPlay = sum1 > sum2 ? 2 : 1;
	int nbMoves = sum1 + sum2;

	if (nbMoves == 7 * 6) {
		return 0;
	}

	if (depth == 0) {
		return (7 * 7 - nbMoves) / 2;
	}

	for (int i = 0; i < 7; i++) {									// if there is a winning move return
		if (isValidMovee(board, i)) {								// evaluation based on how many moves this win took
			int row = nextEmptyRoww(i, board);
			set(row, i, toPlay, board);
			nbMoves++;
			int* win = checkWinn(row, i, toPlay, board);
			if (win != NULL) {
				free(win);

				set(row, i, 0, board);
				return (7 * 7 - nbMoves) / 2;
			}
			set(row, i, 0, board);
			nbMoves--;
		}
	}

	int max = (7 * 5 - nbMoves)/2;									// upper bound for beta
	if (beta > max) {
		beta = max;
		if (alpha >= beta) {
			return beta;
		}
	}

	for (int i = 0; i < 7; i++) {
		if (isValidMovee(board, columnOrder[i])) {
			int row = nextEmptyRoww(columnOrder[i], board);

			set(row, columnOrder[i], toPlay, board);				// make move
			int score = -negamax(board, depth-1, -beta, -alpha);	// get score for move	
			set(row, columnOrder[i], 0, board);						// undo move

			if (score >= beta) {									
				return score;
			}
			if (score > alpha) {
				alpha = score;
			}
		}
	}
	return alpha;
}

int solve(int* board)
{
	int sum1 = 0;
	int sum2 = 0;
	for (int i = 0; i < 7 * 6; i++) {
		if (board[i] == 1) {
			sum1++;
		}
		else if (board[i] == 2) {
			sum2++;
		}
	}
	int toPlay = sum1 > sum2 ? 2 : 1;
	int nbMoves = sum1 + sum2;
	int min = -(7 * 6 - nbMoves) / 2;
	int max = (7 * 7 - nbMoves) / 2;

	while (min < max) {
		int med = min + (max - min) / 2;
		if (med <= 0 && min / 2 < med) {
			med = min / 2;
		}
		else if (med >= 0 && max / 2 > med) {
			med = max / 2;
		}
		int r = negamax(board, 10, med, med + 1);
		if (r <= med) {
			max = r;
		}
		else {
			min = r;
		}
	}
	return min;
}

int getComputerMove(int* board)
{
	int sum1 = 0;
	int sum2 = 0;
	for (int i = 0; i < 7 * 6; i++) {
		if (board[i] == 1) {
			sum1++;
		}
		else if (board[i] == 2) {
			sum2++;
		}
	}
	int toPlay = sum1 > sum2 ? 2 : 1;
	int opp = toPlay == 1 ? 2 : 1;

	int depth = 15;
	int bestMove = 3;
	int oldScore = NEG_INF;

	for (int i = 0; i < 7; i++) {
		int column = columnOrder[i];

		if (!isValidMovee(board, column)) {
			continue;
		}

		int row = nextEmptyRoww(column, board);									// make move
		set(row, column, toPlay, board);

		int* win = checkWinn(row, column, toPlay, board);						// if there is a winning move take it. no need to search
		if (win != NULL) {
			free(win);
			set(row, column, 0, board);
			return column;
		}

		//int newScore = -(negamax(board, depth, NEG_INF, POS_INF));			// score move using minimax
		int newScore = -solve(board);
		set(row, column, 0, board);												// undo move

		if (newScore > oldScore) {												// update best score and best move
			oldScore = newScore;
			bestMove = column;
		}
	}

	for (int i = 0; i < 7; i++) {
		if (!isValidMovee(board, i)) {
			continue;
		}

		int row = nextEmptyRoww(i, board);
		set(row, i, opp, board);

		int* win = checkWinn(row, i, opp, board);
		if (win != NULL) {
			free(win);
			set(row, i, 0, board);
			return i;
		}
		set(row, i, 0, board);
	}
	return bestMove;
}