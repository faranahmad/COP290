#include <iostream>
#include "BoardTest.h"
#include "Test.h"
#include "Board.h"

bool RunAllBoardTests()
{
	BoardInitialisationTests();
	SettingBoardTests();
}

bool BoardInitialisationTests()
{
	Board board1=Board(45.01,36.76);
	Test t("Testing the Initialisation of the board");
	t.VerifyTrue(board1.GetDimensionX()==45.01f,"X dimension should be 45.01");
	t.VerifyTrue(board1.GetDimensionY()==36.76f,"Y dimension should be 36.76");
	t.VerifyTrue(board1.GetNumberBalls()==0,"Number of balls should be 0");
	t.VerifyTrue(board1.GetVectorBalls().size()==0,"Size of vector should be 0");
	return t.isPassed();
}

bool SettingBoardTests()
{
	Test t("Testing the Setting functions of the board");
	
	Board board1=Board(45.01,36.76);
	board1.SetDimensionX(120.34);
	board1.SetDimensionY(489.45);

	Ball ball1=Ball(4.2,5.3);
	ball1.SetRadius(3.76f);
	ball1.SetPosition(5.21,-12.21);
	ball1.SetVelocity(-4.25,13.760);
	ball1.SetColor("yellow");


	Ball ball2=Ball(9.7,4.3);
	ball2.SetVelocity(4.5,-6.7);
	ball2.SetPosition(-5.3,3.4);

	vector<Ball> ballvector1;
	ballvector1.push_back(ball1);
	ballvector1.push_back(ball2);

	board1.SetVectorBalls(ballvector1);

	t.VerifyTrue(board1.GetDimensionX()==120.34f,"X dimension should be 120.34");
	t.VerifyTrue(board1.GetDimensionY()==489.45f,"Y dimension should be 489.45");
	t.VerifyTrue(board1.GetNumberBalls()==2,"Number of balls should be 2");
	t.VerifyTrue(board1.GetVectorBalls().size()==2,"Size of vector should be 2");

	Ball ball3= Ball(67.0,0.0);
	board1.SetBallFromId(0,ball3);

	Ball obtained=board1.GetBallFromId(0);

	t.VerifyTrue(obtained.GetX()==67.0f,"X should be 67.0");
	t.VerifyTrue(obtained.GetY()==0.0f,"Y should be 0.0");
	t.VerifyTrue(obtained.GetVelocityX()==0.0,"Velocity X should be 0.0");
	t.VerifyTrue(obtained.GetVelocityY()==0.0,"Velocity Y should be 0.0");
	t.VerifyTrue(obtained.GetRadius()==1.0,"Radius should be 0.0");
	t.VerifyTrue(obtained.GetColor()=="blue", "Color should be blue");

	return t.isPassed();	
}