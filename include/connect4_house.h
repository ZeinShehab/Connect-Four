#pragma once

#include "limits.h"

#define BOARD_HEIGHT_HOUSE 6
#define BOARD_WIDTH_HOUSE 7
#define NEG_INF_HOUSE INT_MIN + 1 
#define POS_INF_HOUSE INT_MAX - 1 

int make_move_house(int** board);