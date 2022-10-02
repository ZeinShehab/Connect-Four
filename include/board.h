#pragma once

#define BOARD_HEIGHT 7     // One extra row to track number of pieces in each column
#define BOARD_WIDTH 7

int get(int i, int j, int* board);

void set(int i, int j, int value, int* board);

void reset(int* board);

void show(int* board);

int numPiecesInCol(int col, int* board);

int isFullColumn(int col, int* board);

int nextEmptyRow(int col, int* board);