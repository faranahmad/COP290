#include "AllTests.h"
#include "BallTest.h"
#include "Test.h"
#include "Ball.h"
#include "Board.h"

bool RunAllTests()
{
	RunAllBallTests();
}

int main()
{
	RunAllTests();
	return 0;
}