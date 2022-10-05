#include "../include/game.h"
#include "../include/board.h"
#include <stdio.h>

/*
* A valid move is a move that is within bounds of the board 
* and is not in a full column.
* 
* **Effects**: return 1 if the move is valid and 0 otherwise
*/
int isValidMove(int col, int* board)
{
	if (col < 0 || col >= BOARD_WIDTH) {
		return 0;
	}
	else if (isFullColumn(col, board)) {
		return 0;
	}
	return 1;
}

/*
* **Requires**: The column specified to be a valid move.
* **Effects**: Performs the move on the given board if it is valid and nothing otherwise.
*			   This modifies the values of given board.
*/
void makeMove(int col, int player, int* board)
{
	// col - 1 to change from 1 indexed to zero indexed. user will give 1 indexed input
	if (isValidMove(col-1, board)) {
		int row = nextEmptyRow(col-1, board);
		set(row, col-1, player, board);

		set(BOARD_HEIGHT - 1, col-1, numPiecesInCol(col-1, board) + 1, board);
	}
}

/*
* If player is 0 no winner is declared otherwise the player number given is declared as winner and the game quits.
*/
void winIfWinner(int player)
{
	if (player != 0) {
		printf("Player %d wins", player);
		exit(0);
	}
}

/*
* Checks the given board for any 4 consecutive pieces in any direction.
* Will return 0 if there is no winner otherwise it returns the number of the player who won.
*/
int checkWin(int* board)
{
	//search for four consecutive numbers in the 2-d array.
	//we will check horizentally, vertically, and diagonally.
	for (int i = 0; i < 6*7; i += 7) {
		int count = 0;
		for (int j = 0; j < 7-1; j++) {

			if ((board[i + j] == 1 && board[i + j + 1] == 1) || (board[i + j] == 2 && board[i + j + 1] == 2)) {
				count += 1;
			}
			else
				count = 0;
			if (count == 3 && (board[i + j] == 1 && board[i + j + 1] == 1))
				return 1;
			else if (count == 3 && (board[i + j] == 2 && board[i + j + 1] == 2))
				return 2;
		}
	}
	for (int i = 0; i < 7 ; i ++) {
		int count = 0;
		for (int j = 0; j < 6 * 7-7; j+=7) {
			if ((board[i + j] == 1 && board[i + j + 7] == 1) || (board[i + j] == 2 && board[i + j + 7] == 2)) {
				count += 1;
			}
			else
				count = 0;
			if (count == 3 && (board[i + j] == 2 && board[i + j + 7] == 2))
				return 2;
			else if (count == 3 && (board[i + j] == 1 && board[i + j + 7] == 1))
				return 1;
		}
	}


	return 0;
}

/*
* Initializes the game variables and starts the game loop.
*/
void run()
{
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	reset(board);
	show(board);

	int quit = 0;
	int player = 1;

	while (!quit) {
		int firstMove;
		int secondMove;

		printf("Player one move: ");
		scanf_s("%d", &firstMove);

		makeMove(firstMove, player, board);

		show(board);

		int winner = checkWin(board);
		winIfWinner(winner);
			
		player = 2;

		printf("Player two move: ");
		scanf_s("%d", &secondMove);

		makeMove(secondMove, player, board);

		show(board);

		winner = checkWin(board);
		winIfWinner(winner);

		player = 1;
	}
}