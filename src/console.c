#include <stdio.h>
#include <windows.h>
#include "../include/console.h"

void resetColor()
{
	printf("\033[0m");
}

void printRed(char* string)
{
	printf("\033[0;31m");
	printf(string);
	resetColor();
}

void printIntRed(char* string, int value)
{
	printf("\033[0;31m");
	printf(string, value);
	resetColor();
}

void printGreen(char* string)
{
	printf("\033[0;32m");
	printf(string);
	resetColor();
}

void printIntGreen(char* string, int value)
{
	printf("\033[0;32m");
	printf(string, value);
	resetColor();
}

void printYellow(char* string)
{
	printf("\033[0;33m");
	printf(string);
	resetColor();
}

void printIntYellow(char* string, int value)
{
	printf("\033[0;33m");
	printf(string, value);
	resetColor();
}

void printBlue(char* string)
{
	printf("\033[0;34m");
	printf(string);
	resetColor();
}

int consoleWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	return columns;
}

int consoleHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return rows;
}

void centerline(int lineLength)
{
	int spaces = (consoleWidth() / 2) - (lineLength / 2);
	for (int k = 0; k < spaces; k++) {
		printf(" ");
	}
}

void centerTextVer(int textLength)
{
	int newlines = (consoleHeight() / 2) - (textLength / 2);
	for (int k = 0; k < newlines; k++) {
		printf("\n");
	}
}

/*
* Clears the console and resets the cursor to (0,0)
*/
void clrscr()
{
	system("@cls||clear");
}