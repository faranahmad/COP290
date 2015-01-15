#include <iostream>
#include <algorithm>
#include "BallTest.h"
#include "Test.h"
#include "Ball.h"

bool RunAllBallTests()
{
	BallInitialisationTests();
	SettingBallTests();
	UpdateBallTests();
}

bool BallInitialisationTests()
{
	Ball ball1=Ball(4.2,5.3);
	// cout <<ball1.GetBallInformation()<<endl;
	Test t("Testing the Initialisation of Ball");
	t.VerifyTrue(ball1.GetX()==4.2,"X should be 4.2");
	t.VerifyTrue(ball1.GetY()==5.3,"Y should be 5.3");
	t.VerifyTrue(ball1.GetVelocityX()==0.0,"Velocity X should be 0.0");
	t.VerifyTrue(ball1.GetVelocityY()==0.0,"Velocity Y should be 0.0");
	t.VerifyTrue(ball1.GetRadius()==1.0,"Radius should be 0.0");
	// t.VerifyTrue(ball1.GetColor()=="blue", "Color should be blue");
	return t.isPassed();
}

bool SettingBallTests()
{
	Ball ball1=Ball(4.2,5.3);
	ball1.SetRadius(3.76);
	ball1.SetPosition(5.21,-12.21);
	ball1.SetVelocity(-4.25,13.760);
	// ball1.SetColor("yellow");
	Test t("Testing the Setting Paramaters of Ball");
	t.VerifyTrue(ball1.GetX()==5.21,"X should be 5.21");
	t.VerifyTrue(ball1.GetY()==-12.21,"Y should be -12.21");
	t.VerifyTrue(ball1.GetVelocityX()==-4.25,"Velocity X should be -4.25");
	t.VerifyTrue(ball1.GetVelocityY()==13.760,"Velocity Y should be 13.760");
	t.VerifyTrue(ball1.GetRadius()==3.76,"Radius should be 3.76");
	// t.VerifyTrue(ball1.GetColor()=="yellow", "Color should be yellow");

	return t.isPassed();
}

bool UpdateBallTests()
{
	Ball ball1=Ball(9.7,4.3);
	ball1.SetVelocity(4.5,-6.7);
	ball1.SetPosition(-5.3,3.4);
	ball1.UpdateBall(1);
	Test t("Testing the update parameters of Ball");
	t.VerifyTrue(ball1.GetVelocityX()==4.5,"Vx should be 4.5");
	t.VerifyTrue(ball1.GetVelocityY()==-6.7,"Vy should be -6.7");
	t.VerifyTrue(abs(ball1.GetX()+0.8) < 0.01,"X should be -5.3 + 4.5");
	t.VerifyTrue(abs(ball1.GetY()+3.3) < 0.01,"Y should be 3.4 -6.7");
	// cout <<ball1.GetY()<<endl;
	// cout <<ball1.GetBallInformation()<<"\n";
	return t.isPassed();
}