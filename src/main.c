#include <stdio.h>
#include "../include/board.h"

int main() {
	int board[BOARD_HEIGHT * BOARD_WIDTH];

	reset(board);
	show(board);

   return 0;
}