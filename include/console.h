#pragma once

#define BUFFER_SIZE 15								// large enough buffer to prevent input from one player going to another player

void resetColor();

void printRed(char *string);

void printIntRed(char *string, int value);

void printGreen(char *string);

void printIntGreen(char *string, int value);

void printYellow(char* string);

void printIntYellow(char* string, int value);

void printBlue(char* string);

int consoleWidth();

int consoleHeight();

void centerline(int lineLength);

void centerTextVer(int textLength);

void clrscr();

int getdigit();