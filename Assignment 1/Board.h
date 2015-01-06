#ifndef BOARD_H
#define BOARD_H

#include "Ball.h"
#include <vector>

class Board
{
	public:
		Board(float,float);

		float GetDimensionX();
		float GetDimensionY();
		int GetNumberBalls ();
		vector<Ball> GetVectorBalls();
		Ball GetBallFromId (int);

		void SetDimensionX(float);
		void SetDimensionY(float);
		void SetNumberOfBalls(int);
		void SetVectorBalls(vector<Ball>);
		void SetBallFromId(int,Ball);

		void AddBallToBoard(Ball);
		
		void UpdateBoard(float);

	private:
		float dimension_x;
		float dimension_y;
		int number_balls;
		vector<Ball> vector_of_balls;
};

#endif