#include "tests.h"
#include "gameTests.h"
#include "boardTests.h"


void runTests()
{
	runBoardTests();
	runGameTests();
}

void printTestResult(char* testName, int testResult)
{
	if (testResult != 0) {
		printf("%s failed at test case: %d\n", testName, testResult);
	}
	else {
		printf("%s passed!\n", testName);
	}
}