#ifndef BOARD_H
#define BOARD_H

#include "Ball.h"
#include <vector>

class Board
{
	public:
		Board();
		Board(double,double,int);

		double GetDimensionX();
		double GetDimensionY();
		int GetNumberBalls ();
		vector<Ball> GetVectorBalls();
		Ball GetBallFromId (int);

		string GetBoardInformation();

		void SetDimensionX(double);
		void SetDimensionY(double);
		void SetNumberOfBalls(int);
		void SetVectorBalls(vector<Ball>);
		void SetBallFromId(int,Ball);

		void AddBallToBoard(Ball);
		void RemoveBallFromBoard();
		
		void UpdateBoard(double);

	private:
		double dimension_x;
		double dimension_y;
		int number_balls;
		vector<Ball> vector_of_balls;
};

#endif