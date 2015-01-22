#include "AllTests.h"
#include "BallTest.h"
#include "BoardTest.h"
#include "Test.h"
#include "Ball.h"
#include "Board.h"

bool RunAllTests()
{
	RunAllBallTests();
	RunAllBoardTests();
}

int main()
{
	RunAllTests();
	return 0;
}