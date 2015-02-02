#include "AllTests.h"

bool RunAllTests()
{
	RunAllUserTests();
	RunAllUserBaseTests();
}

int main()
{
	RunAllTests();
	return 0;
}