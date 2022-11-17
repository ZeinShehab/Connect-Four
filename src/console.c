#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../include/console.h"

/*
* Resets the text color to the default console color.
*/
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

void printIntPink(char* string,int value) {
	printf("\033[0;35m");
	printf(string, value);
	resetColor();
}

/*
* Retuns the width of the current console window. Works for resizable windows.
*/
int consoleWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	return columns;
}

/*
* Retuns the height of the current console window. Works for resizable windows.
*/
int consoleHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return rows;
}

/* Centers a line of text in the middle of the screen horizontally.
* Spaces are added for padding based on the length of the line to be centered.
*/
void centerline(int lineLength)
{
	int spaces = (consoleWidth() / 2) - (lineLength / 2);
	for (int k = 0; k < spaces; k++) {
		printf(" ");
	}
}

/*
* Centers text in the middle of the screen vertically.
* Newlines are added for padding based on the height of the text to be centered.
*/
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

/*
* Reads an entire line of input. 
* If given input is not a digit -1 is returned to indicate an invalid move otherwise we return the digit.
*/
int getdigit()
{
	char buffer[BUFFER_SIZE];
	fgets(buffer, BUFFER_SIZE, stdin);

	// We expect a single digit so any input longer than that is invalid
	int len = 0;
	while (buffer[len] != '\n') {
		len++;
		if (len != 1) {
			return -1;
		}
	}
	return isdigit(buffer[0]) ? atoi(buffer) : -1;
}

/*
* Hides the cursor on the console.
*/
void hidecursor()
{
	printf("\33[?25l");
}

/*
* Shows the cursor on the console.
*/
void showcursor()
{
	printf("\33[?25h");
}