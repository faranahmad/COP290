#include "Board.h"

Board::Board(float x,float y)
{
	// Constructs a new Board
	// Default number of balls is 0
	// Default vector of balls is empty
	dimension_x=x;
	dimension_y=y;
	number_balls=0;
}

float Board::GetDimensionX()
{
	// Returns the x dimension of the board
	return dimension_x;
}

float Board::GetDimensionY()
{
	// Returns the y dimension of the board
	return dimension_y;
}

int Board::GetNumberBalls()
{
	// Returns the number of balls on the board
	return number_balls;
}

vector<Ball> Board::GetVectorBalls()
{
	// Returns the vector of all the balls on the board
	return vector_of_balls;
}

Ball Board::GetBallFromId(int position)
{
	// Returns the position id ball from the vector of balls if the position id is less than the number of balls on the board
	// TODO: Add Exception
	if (position < number_balls)
		return vector_of_balls[position];
	else
		return Ball(1.0,1.0);
}

void Board::SetDimensionX(float x)
{
	// Updates the x dimension of the board
	dimension_x=x;
}

void Board::SetDimensionY(float y)
{
	// Updates teh y dimension of the board
	dimension_y=y;
}

void Board::SetNumberOfBalls(int number)
{
	// Updates the number of balls on the board
	// CAUTION: This might violate that length of vector == number_balls
	number_balls=number;
}

void Board::SetVectorBalls(vector<Ball> newvector)
{
	// Updates the vector of balls to the new vector and changes the number of balls variable as well
	number_balls=newvector.size();
	vector_of_balls=newvector;
}

void Board::SetBallFromId(int id, Ball newBall)
{
	// Updates the ball at position id if id < number of balls with the new ball
	// TODO: Add exception
	if (id<number_balls)
	{
		vector_of_balls[id]=newBall;
	}
}

void Board::AddBallToBoard(Ball newBall)
{
	// Adds a new ball to the board and increments the nunmber of balls counter
	number_balls += 1;
	vector_of_balls.push_back(newBall);
}

void Board::UpdateBoard(float time_elapsed)
{
	// Updates the situation of the board after a time time_elapsed has passed using the updae ball function
	for (int i=0; i<number_balls; i++)
	{
		vector_of_balls[i].UpdateBall(time_elapsed);
	}
}