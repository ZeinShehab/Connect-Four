#include "tests.h"
#include "gameTests.h"
#include "boardTests.h"
#include "botTests.h"
#include "../include/console.h"

/*
* Entry point for running tests.
* Runs all tests and reports the results.
*/
void runTests()
{
	runBoardTests();
	runGameTests();
	runBotTests();
}

/*
* Helper function for reporting test results.
*/
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