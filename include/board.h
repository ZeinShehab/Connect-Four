#pragma once

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7

int get(int i, int j, int* board);

void set(int i, int j, int value, int* board);

void reset(int* board);

void show(int* board);
