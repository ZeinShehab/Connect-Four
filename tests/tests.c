#include "tests.h"
#include "gameTests.h"
#include "boardTests.h"
#include "../include/console.h"

void runTests()
{
	//runBoardTests();
	runGameTests();
}

void printTestResult(char* testName, int testResult)
{
	if (testResult != 0) {
		printRed("[-] ");
		printRed(testName);
		printIntRed(" failed at test case: %d\n", testResult);
	}
	else {
		printGreen("[+] ");
		printGreen(testName);
		printGreen(" passed!\n");
	}
}