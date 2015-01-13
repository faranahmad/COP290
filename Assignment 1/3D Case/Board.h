#ifndef BOARD_H
#define BOARD_H

#include "Ball.h"
#include <vector>

bool CheckCorrect(std::vector<Ball>,Ball);

class Board
{
	public:
		Board();
		Board(double,double,int);

		double GetDimensionX();
		double GetDimensionY();
		double GetDimensionZ();
		int GetNumberBalls ();
		vector<Ball> GetVectorBalls();
		Ball GetBallFromId (int);

		string GetBoardInformation();

		void SetDimensionX(double);
		void SetDimensionY(double);
		void SetDimensionZ(double);
		void SetNumberOfBalls(int);
		void SetVectorBalls(vector<Ball>);
		void SetBallFromId(int,Ball);

		void AddBallToBoard(Ball);
		void RemoveBallFromBoard();
		
		void UpdateBoard(double);

	private:
		double dimension_x;
		double dimension_y;
		double dimension_z;
		int number_balls;
		vector<Ball> vector_of_balls;
};

#endif