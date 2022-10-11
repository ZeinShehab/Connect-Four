#include "../include/game.h"
#include "../include/board.h"
#include "../include/console.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
void makeMove(int row, int col, int player, int* board)
{
	set(row, col, player, board);
	set(BOARD_HEIGHT - 1, col, numPiecesInCol(col, board) + 1, board);
}

/*
* Return column to make move in from user input.
* Will retry until user gives valid move.
*/
int getPlayerMove(int player, int* board)
{
	int move = -1;
	int invalidCounter = 0;
	while (!isValidMove(move - 1, board)) {
		if (invalidCounter >= 1) {
			printf("Invalid move. Try again. ");
		}
		printf("Player %d move: ", player);
		scanf_s("%d", &move);
		invalidCounter++;
	}
	// user input is 1 indexed so it returns 0 indexed column
	return move - 1;
}

/*
* Checks the given board for any 4 consecutive pieces in any direction.
* Will return 0 if there is no winner otherwise it returns the number of the player who won.
*/
int checkWin(int row, int col, int player, int* board)
{
	// check how we will search
	// left or right
	// diagonal left up or down
	// diagonal right up or down
	// down
	//search rightt
	int count = 0;
	if (col <= BOARD_WIDTH - 4) {
		for (int i = col; i < BOARD_WIDTH; i++) { // search right
			if (board[7 * row + i] == player)
				count += 1;
			else
				count = 0;
			if (count == 4)
				return player;
		}
		count = 0;
	}
	if (row <= BOARD_HEIGHT - 1 - 4) {
		for (int i = row + 1; i < BOARD_HEIGHT - 1; i++) {// search down 
			if (board[7 * i + col] == player)
				count += 1;
			else
				count = 0;
			if (count == 3)
				return player;
		}

	}

	if (col >= BOARD_WIDTH - 4) {
		for (int i = col; i >= 0; i--) { // search left
			if (board[7 * row + i] == player)
				count += 1;
			else
				count = 0;
			if (count == 4)
				return player;
		}
	}
	if (row >= BOARD_HEIGHT - 1 - 4 && col < BOARD_WIDTH - 4) {
		int level = 1;
		count = 0;
		for (int i = row - 1; i >= 0; i--) { // search diagonally up and to the right
			if (player == board[7 * i + col + level])
				count += 1;
			else
				count = 0;
			if (count == 3)
				return player;
			level += 1;
		}

	}
	if (row >= BOARD_HEIGHT - 1 - 4 && col >= BOARD_WIDTH - 4) {
		int level = 1;
		count = 0;
		for (int i = row - 1; i >= 0; i--) { // search diagonally up and to the left
			if (player == board[7 * i + col - level])
				count += 1;
			else
				count = 0;
			if (count == 3)
				return player;
			level += 1;
		}

	}
	if (row <= BOARD_HEIGHT - 1 - 4 && col >= BOARD_WIDTH - 4) {

		int level = 1;
		count = 0;
		for (int i = row + 1; i < BOARD_HEIGHT - 1; i++) { // search diagonally DOWN and to the left
			if (player == board[7 * i + col - level])
				count += 1;
			else
				count = 0;
			if (count == 3)
				return player;
			level += 1;
		}

	}
	if (row <= BOARD_HEIGHT - 1 - 4 && col <= BOARD_WIDTH - 4) {

		int level = 1;
		count = 0;
		for (int i = row + 1; i < BOARD_HEIGHT - 1; i++) { // search diagonally DOWN and to the right
			if (player == board[7 * i + col + level])
				count += 1;
			else
				count = 0;
			if (count == 3)
				return player;
			level += 1;
		}
	}
	return 0;
}

/*
* Checks if the board is full. A tie is declared if the board is full and no player has won.
* Returns 0 if there is no tie otherwise the number of player who wins by time.
*/
int checkTie(int totalPieces, int playerOneTime, int playerTwoTime)
{
	int tie = (totalPieces == BOARD_WIDTH * (BOARD_HEIGHT - 1));			// if board is full then we have a tie
	return tie * (playerOneTime < playerTwoTime ? 1 : 2);					// if there is no tie the tieWinner will be 0 and there will be no winner otherwise the winner is selected
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
* Plays out a single game cycle for given player
*/
void playerTurn(int player, int* board, int *playerTime)
{
	clock_t start = clock(), diff;
	int col = getPlayerMove(player, board);									// time this to know how much time player took to make a move.
	diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	*playerTime += msec;

	int row = nextEmptyRow(col, board);
	makeMove(row, col, player, board);

	clrscr();
	show(board);

	int winner = checkWin(row, col, player, board);
	winIfWinner(winner);
}

/*
* Initializes the game variables and starts the game loop.
*/
void run()
{
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	reset(board);

	clrscr();
	show(board);

	int totalPieces = 0;

	int playerOneTime = 0;
	int playerTwoTime = 0;

	int quit = 0;
	while (!quit) {
		playerTurn(1, board, &playerOneTime);
		totalPieces++;

		int tieWinner = checkTie(totalPieces, playerOneTime, playerTwoTime);
		winIfWinner(tieWinner);

		playerTurn(2, board, &playerTwoTime);
		totalPieces++;

		tieWinner = checkTie(totalPieces, playerOneTime, playerTwoTime);
		winIfWinner(tieWinner);
	}
}