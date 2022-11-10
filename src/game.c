#include "../include/game.h"
#include "../include/board.h"
#include "../include/console.h"
#include "../include/bot.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


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
			clrscr();
			show(board);

			if (CENTER_HOZ) {
				centerline(strlen("Invalid move. Try again."));
			}
			printf("Invalid move. Try again.\n");
		}

		// the cursor only needs to be visible on the screen when taking user input
		showcursor();
		centerline(strlen("Please choose a column between 1 and 7"));
		printf("Please choose a column between 1 and 7\n");

		centerline(strlen("Player 1 move: ") + 1);
		printf("Player %d move: ", player);
		move = getdigit();
		hidecursor();

		invalidCounter++;
	}
	// user input is 1 indexed so it returns 0 indexed column
	return move - 1;
}

/*
* Checks if the last move `player` made is a winning move or not.
* Will return NULL if there is no winner otherwise it will return an array containing the winning player 
* along with information about the winning line so we can highlight it in green.
*/
int* checkWin(int row, int col, int player, int* board)
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
				int* winning_line = (int*) malloc(sizeof(int) * 5);
				
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
* If winning_line is NULL no winner is declared otherwise the player number given is declared as winner
* and the winning line is highlighted in green then the game quits.
*/
void winIfWinner(int *winning_line, int tie, int *board)
{
	if (winning_line != NULL ) {
		int player = *winning_line;

		// No line to highlight if the win was through a tie
		if (!tie) {
			clrscr();
			showWinningLine(winning_line[1], winning_line[2], winning_line[3], winning_line[4], board);
			free(winning_line);
		}
		centerline(strlen("Player 1 wins"));
		printf("Player %d wins\n\n", player);
		exit(0);
	}
}

/*
* If player is 0 no winner is declared otherwise the player times along with the winner will be displayed.
*/
void winIfTie(int player, int playerOneTime, int playerTwoTime)
{
	if (player > 0 && player <= 2) {
		centerline(strlen("Player 1 took: xxx seconds"));
		printf("Player 1 took: %d seconds\n", playerOneTime / 1000);
		centerline(strlen("Player 2 took: xxx seconds"));
		printf("Player 2 took: %d seconds\n", playerTwoTime / 1000);
		winIfWinner(&player, 1, NULL);										// The only part we need from the winning line is the player number 
	}																		// since there is no winning line. So we also dont need a board.
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
	printf("%d", evaluate(board));

	int *winning_line = checkWin(row, col, player, board);
	winIfWinner(winning_line, 0, board);
	
}

/*
* Initializes the game variables and starts the game loop.
*/
void runGame()
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
		winIfTie(tieWinner, playerOneTime, playerTwoTime);

		playerTurn(2, board, &playerTwoTime);
		totalPieces++;

		tieWinner = checkTie(totalPieces, playerOneTime, playerTwoTime);
		winIfTie(tieWinner, playerOneTime, playerTwoTime);
	}
}