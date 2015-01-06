#include <iostream>
#include "BallTest.h"
#include "Test.h"
#include "Ball.h"
#include "Board.h"

bool RunAllBallTests()
{
	InitialisationTests();
	SettingBallTests();
	UpdateBallTests();
}

bool InitialisationTests()
{
	Ball ball1=Ball(4.2,5.3);
	Test t("Testing the Initialisation of Ball");
	t.VerifyTrue(ball1.GetX()==4.2f,"X should be 4.2");
	t.VerifyTrue(ball1.GetY()==5.3f,"Y should be 5.3");
	t.VerifyTrue(ball1.GetVelocityX()==0.0,"Velocity X should be 0.0");
	t.VerifyTrue(ball1.GetVelocityY()==0.0,"Velocity Y should be 0.0");
	t.VerifyTrue(ball1.GetRadius()==1.0,"Radius should be 0.0");
	t.VerifyTrue(ball1.GetColor()=="blue", "Color should be blue");
	return t.isPassed();
}

bool SettingBallTests()
{
	Ball ball1=Ball(4.2,5.3);
	ball1.SetRadius(3.76f);
	ball1.SetPosition(5.21,-12.21);
	ball1.SetVelocity(-4.25,13.760);
	ball1.SetColor("yellow");
	Test t("Testing the Setting Paramaters of Ball");
	t.VerifyTrue(ball1.GetX()==5.21f,"X should be 5.21");
	t.VerifyTrue(ball1.GetY()==-12.21f,"Y should be -12.21");
	t.VerifyTrue(ball1.GetVelocityX()==-4.25f,"Velocity X should be -4.25");
	t.VerifyTrue(ball1.GetVelocityY()==13.760f,"Velocity Y should be 13.760");
	t.VerifyTrue(ball1.GetRadius()==3.76f,"Radius should be 3.76");
	t.VerifyTrue(ball1.GetColor()=="yellow", "Color should be yellow");
	return t.isPassed();
}

bool UpdateBallTests()
{
	Ball ball1=Ball(9.7,4.3);
	ball1.SetVelocity(4.5,-6.7);
	ball1.SetPosition(-5.3,3.4);
	ball1.UpdateBall(0.5);
	Test t("Testing the update parameters of Ball");
	t.VerifyTrue(ball1.GetVelocityX()==4.5f,"Vx should be 4.5");
	t.VerifyTrue(ball1.GetVelocityY()==-6.7f,"Vy should be -6.7");
	t.VerifyTrue(ball1.GetX()==-3.05,"X should be -5.3+2.25");
	cout <<ball1.GetX()<<"\n";
	cout <<ball1.GetY()<<"\n";
	t.VerifyTrue(ball1.GetY()==0.05,"Y should be 3.4-3.35");
	return t.isPassed();
}