#include "connect4_house.h"
#include "stdlib.h"

// prioritize central columns first
int columnOrder_house[7] = { 3, 2, 4, 1, 5, 0, 6 };						// columnOrder[i] = WIDTH / 2 + (1 - 2 * (i % 2)) * (i + 1) / 2

void set_house(int row, int column, int value, int** board) {
	board[row][column] = value;
}

int* checkWin_house(int row, int col, int player, int** board)
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
			x = col + row <= BOARD_WIDTH_HOUSE - 1 ? col + row : BOARD_WIDTH_HOUSE - 1;
			y = col + row <= BOARD_WIDTH_HOUSE - 1 ? 0 : (col + row) - (BOARD_WIDTH_HOUSE - 1);
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
		while (x < BOARD_WIDTH_HOUSE && x >= 0 && y < BOARD_HEIGHT_HOUSE && y >= 0) {
			n_pieces = board[y][x] == player ? n_pieces + 1 : 0;		// If different piece is found reset counter else increment by 1

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

int isValidMove_house(int** board, int move)
{
	return board[0][move] == 0;
}

int nextEmptyRow_house(int col, int** board) {
	int row = -1;
	for (int i = 0; i < BOARD_HEIGHT_HOUSE; i++) {
		if (board[i][col] == 0) {
			row = i;
		}
	}
	return row;
}



int negamax_house(int** board, int depth, int alpha, int beta, int nbMoves, int toPlay)
{
	if (nbMoves == BOARD_HEIGHT_HOUSE * BOARD_WIDTH_HOUSE) {
		return 0;
	}

	if (depth == 0) {
		return (BOARD_WIDTH_HOUSE * BOARD_HEIGHT_HOUSE + 1 - nbMoves) / 2;
	}

	for (int i = 0; i < BOARD_WIDTH_HOUSE; i++) {									// if there is a winning move return
		if (isValidMove_house(board, i)) {								// evaluation based on how many moves this win took
			int row = nextEmptyRow_house(i, board);
			set_house(row, i, toPlay, board);
			nbMoves++;
			int* win = checkWin_house(row, i, toPlay, board);
			if (win != NULL) {
				free(win);

				set_house(row, i, 0, board);
				return (BOARD_WIDTH_HOUSE * BOARD_HEIGHT_HOUSE + 1 - nbMoves) / 2;
			}
			set_house(row, i, 0, board);
			nbMoves--;
		}
	}

	int max = (BOARD_WIDTH_HOUSE * BOARD_HEIGHT_HOUSE - 1 - nbMoves) / 2;									// upper bound for beta
	if (beta > max) {
		beta = max;
		if (alpha >= beta) {
			return beta;
		}
	}

	for (int i = 0; i < BOARD_WIDTH_HOUSE; i++) {
		if (isValidMove_house(board, columnOrder_house[i])) {
			int row = nextEmptyRow_house(columnOrder_house[i], board);

			set_house(row, columnOrder_house[i], toPlay, board);				// make move
			int score = -negamax_house(board, depth - 1, -beta, -alpha, nbMoves + 1, toPlay == 1 ? 2 : 1);	// get score for move	
			set_house(row, columnOrder_house[i], 0, board);						// undo move

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

int solve_house(int** board, int depth)
{
	int sum1 = 0;
	int sum2 = 0;
	for (int i = 0; i < BOARD_HEIGHT_HOUSE; i++) {
		for (int j = 0; j < BOARD_WIDTH_HOUSE; j++) {
			if (board[i][j] == 1) {
				sum1++;
			}
			else if (board[i][j] == 2) {
				sum2++;
			}
		}
	}
	int toPlay = sum1 > sum2 ? 2 : 1;
	int nbMoves = sum1 + sum2;
	int min = -(BOARD_WIDTH_HOUSE * BOARD_HEIGHT_HOUSE - nbMoves) / 2;
	int max = (BOARD_WIDTH_HOUSE * BOARD_HEIGHT_HOUSE + 1 - nbMoves) / 2;

	while (min < max) {
		int med = min + (max - min) / 2;
		if (med <= 0 && min / 2 < med) {
			med = min / 2;
		}
		else if (med >= 0 && max / 2 > med) {
			med = max / 2;
		}
		int r = negamax_house(board, depth, med, med + 1, nbMoves, toPlay);
		if (r <= med) {
			max = r;
		}
		else {
			min = r;
		}
	}
	return min;
}

int make_move_house(int** board)
{
	int depth = 8;
	int sum1 = 0;
	int sum2 = 0;
	for (int i = 0; i < BOARD_HEIGHT_HOUSE; i++) {
		for (int j = 0; j < BOARD_WIDTH_HOUSE; j++) {
			if (board[i][j] == 1) {
				sum1++;
			}
			else if (board[i][j] == 2) {
				sum2++;
			}
		}
	}
	int toPlay = sum1 > sum2 ? 2 : 1;
	int opp = toPlay == 1 ? 2 : 1;

	int bestMove = 3;
	int oldScore = NEG_INF_HOUSE;

	for (int i = 0; i < BOARD_WIDTH_HOUSE; i++) {
		int column = columnOrder_house[i];

		if (!isValidMove_house(board, column)) {
			continue;
		}

		int row = nextEmptyRow_house(column, board);									// make move
		set_house(row, column, toPlay, board);

		int* win = checkWin_house(row, column, toPlay, board);						// if there is a winning move take it. no need to search
		if (win != NULL) {
			free(win);
			set_house(row, column, 0, board);

			return column;
		}

		//int newScore = -(negamax(board, depth, NEG_INF, POS_INF));			// score move using minimax
		int newScore = -solve_house(board, depth);
		set_house(row, column, 0, board);												// undo move

		if (newScore > oldScore) {												// update best score and best move
			oldScore = newScore;
			bestMove = column;
		}
	}
	return bestMove;
}
