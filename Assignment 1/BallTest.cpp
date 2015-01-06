// #include <iostream>
#include "BallTest.h"
#include "Test.h"
#include "Ball.h"
#include "Board.h"

bool RunAllBallTests()
{
	// GetValueTests();
	InitialisationTests();
	// UpdateBallTests();
}

bool InitialisationTests()
{
	Ball ball1=Ball(4.2,5.3);
	Test t("Testing the Initialisation of Ball");
	t.VerifyTrue(ball1.GetX()==4.2f,"X should be 4.2");
	t.VerifyTrue(ball1.GetY()==5.3f,"Y should be 5.3");
	t.VerifyTrue(ball1.GetVelocityX()==0.0,"Velocity X should be 0.0");
	t.VerifyTrue(ball1.GetVelocityY()==0.0,"Velocity Y should be 0.0");
	t.VerifyTrue(ball1.GetRadius()==1.0,"Velocity Y should be 0.0");
	t.VerifyTrue(ball1.GetColor()=="blue", "Color should be blue");
	
	return t.isPassed();
}
