#pragma once
#include <limits.h>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 7

#define POS_INF (INT_MAX - 1)
#define NEG_INF (INT_MIN + 1)

int getComputerMove(int* board);