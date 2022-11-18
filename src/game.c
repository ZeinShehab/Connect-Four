#include "../include/game.h"
#include "../include/board.h"
#include "../include/console.h"
#include "../include/bot.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char* names[3];
int pr = 1;

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
int getPlayerMove(int player, int* board, char* name)
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

		centerline(strlen("EEEEEE move: ") + 1);
		printf("%s's move (", name);
		if(pr== 1)
			printIntRed("%d", 1);
		else
			printIntYellow("%d", 2);
		printf("): ");
		move = getdigit();
		hidecursor();

		invalidCounter++;
	}
	pr = pr == 1 ? 0 : 1;
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
void winIfWinner(int *winning_line, int tie, int *board,char* name)
{
	if (winning_line != NULL ) {
		int player = *winning_line;

		// No line to highlight if the win was through a tie
		if (!tie) {
			clrscr();
			showWinningLine(winning_line[1], winning_line[2], winning_line[3], winning_line[4], board);
			free(winning_line);
		}
		centerline(strlen("EEEEEEEE wins"));
		printf("%s wins\n\n", name);
		exit(0);
	}
}

/*
* If player is 0 no winner is declared otherwise the player times along with the winner will be displayed.
*/
void winIfTie(int player, int playerOneTime, int playerTwoTime,char* name)
{
	if (player > 0 && player <= 2) {
		centerline(strlen("EEEEEEEE took: xxx seconds"));
		printf("%s took: %d seconds\n",names[1], playerOneTime / 1000);
		centerline(strlen("EEEEEEEE took: xxx seconds"));
		printf("%s took: %d seconds\n", names[2], playerTwoTime / 1000);
		winIfWinner(&player, 1, NULL, name);										// The only part we need from the winning line is the player number 
	}																		// since there is no winning line. So we also dont need a board.
}

/*
* Plays out a single game cycle for given player
*/
void playerTurn(int player, int* board, int *playerTime, char* name)
{
	clock_t start = clock(), diff;
	int col = getPlayerMove(player, board,name);									// time this to know how much time player took to make a move.
	diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	*playerTime += msec;

	int row = nextEmptyRow(col, board);
	makeMove(row, col, player, board);

	clrscr();
	show(board);
	
	int *winning_line = checkWin(row, col, player, board);
	winIfWinner(winning_line, 0, board,name);
	
}

void init(int* board)
{
	reset(board);
	clrscr();
	show(board);
}

void multiPlayer()
{
	int board[BOARD_HEIGHT * BOARD_WIDTH];
	int totalPieces = 0;
	int playerOneTime = 0;
	int playerTwoTime = 0;

	init(board);
	srand(time(NULL));
	int num = (rand() % 2) + 1;
	int start = num;
	int sec_start = abs(3 - num);
	int quit = 0;
	char p1[6];
	char p2[6];

	if (CENTER_HOZ) {
		centerline(strlen("Enter your name: EEEEEE"));
	}
	printf("Enter your name: ");
	gets(p1);
	if (CENTER_HOZ) {
		centerline(strlen("Enter your name: EEEEEE"));
	}
	printf("Enter your name: ");
	gets(p2);
	char* first = (num == 1) ? p1 : p2;
	char* second = (num == 1) ? p2 : p1;
	names[start] = first;
	names[sec_start] = second;



	while (!quit) {
		playerTurn(1, board, &playerOneTime, names[start]);
		totalPieces++;

		int tieWinner = checkTie(totalPieces, playerOneTime, playerTwoTime);
		winIfTie(tieWinner, playerOneTime, playerTwoTime,names[start]);

		playerTurn(2, board, &playerTwoTime,names[sec_start]);
		totalPieces++;

		tieWinner = checkTie(totalPieces, playerOneTime, playerTwoTime);
		winIfTie(tieWinner, playerOneTime, playerTwoTime,names[sec_start]);
	}
}

void singlePlayer() 
{
	centerline(strlen("Choose difficulty | Easy(1) | Medium(2) | Hard(3) |: 1"));
	printf("Choose difficulty | Easy(1) | Medium(2) | Hard(3) |: ");
	int difficulty = getdigit();
	int depth = 0;

	if (difficulty == 1) {
		depth = 2;							// very easy
	}
	else if (difficulty == 2) {
		depth = 6;							// medium
	}
	else if (difficulty == 3) {
		depth = 10;							// unwinnable
	}
	else depth = 6;



	int board[BOARD_HEIGHT * BOARD_WIDTH];
	int totalPieces = 0;
	int playerOneTime = 0;
	int computerTime = 0;

	init(board);
	srand(time(NULL));
	int num = (rand() % 2) + 1;
	int start = num;
	int sec_start = abs(3 - num);
	char name[10];
	if (CENTER_HOZ) {
		centerline(strlen("Enter your name: EEEEEE"));
	}
	printf("Enter your name: ");
	gets(name);
	int quit = 0;

	while (!quit) {
		
		if(num==1){
			playerTurn(1, board, &playerOneTime,name);
			totalPieces++;
			int tieWinner = checkTie(totalPieces, playerOneTime, computerTime);
			winIfTie(tieWinner, playerOneTime, computerTime,name);

			int computerMove = getComputerMove(board, depth);  // minimax();											// time this to get computer time
			int row = nextEmptyRow(computerMove, board);
			makeMove(row, computerMove, 2, board);
			clrscr();
			show(board);
			int* winning_line = checkWin(row, computerMove, 2, board);
			winIfWinner(winning_line, 0, board,"Computer");
			totalPieces++;
			pr = pr == 1 ? 0 : 1;

			tieWinner = checkTie(totalPieces, playerOneTime, computerTime);
			winIfTie(tieWinner, playerOneTime, computerTime,"Computer");
		}
		else {
			int computerMove = getComputerMove(board, depth);  // minimax();											// time this to get computer time
			int row = nextEmptyRow(computerMove, board);
			makeMove(row, computerMove, 1, board);
			clrscr();
			show(board);
			int* winning_line = checkWin(row, computerMove, 1, board);
			winIfWinner(winning_line, 0, board,"Computer");
			totalPieces++;
			pr = pr == 1 ? 0 : 1;

			int tieWinner = checkTie(totalPieces, playerOneTime, computerTime);
			winIfTie(tieWinner, playerOneTime, computerTime,"Computer");

			playerTurn(2, board, &playerOneTime,name);
			totalPieces++;
			tieWinner = checkTie(totalPieces, playerOneTime, computerTime);
			winIfTie(tieWinner, playerOneTime, computerTime,name);
		}

	}
}

/*
* Initializes the game variables and starts the game loop.
*/
void runGame()
{
	centerline(strlen("Multiplayer(1) or Computer(2): 1"));
	printf("Multiplayer(1) or Computer(2): ");
	int multiplayer = getdigit();

	if (multiplayer == 1) {
		multiPlayer();
	}
	if (multiplayer == 2) {
		singlePlayer();
	}
}