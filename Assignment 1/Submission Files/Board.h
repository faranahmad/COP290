#ifndef BOARD_H
#define BOARD_H

#include "Ball.h"
#include <vector>
#include <algorithm>

bool CheckCorrect(std::vector<Ball>,Ball);

class Board
{
	public:
		Board();
		Board(double,double,double,int);

		double GetDimensionX();
		double GetDimensionY();
		double GetDimensionPosY();
		double GetDimensionNegY();
		int GetNumberBalls();
		vector<Ball> GetVectorBalls();
		Ball GetBallFromId (int);

		string GetBoardInformation();

		void SetDimensionX(double);
		void SetDimensionY(double);
		void SetDimensionPosY(double);
		void SetDimensionNegY(double);
		void SetNumberOfBalls(int);
		void SetVectorBalls(vector<Ball>);
		void SetBallFromId(int,Ball);

		void AddBallToBoard(Ball);
		void RemoveBallFromBoard();
		
		void UpdateBoard(double);

	private:
		double dimension_x;
		double dimension_y;
		double dimension_pos_y;
		double dimension_neg_y;
		int number_balls;
		vector<Ball> vector_of_balls;
};

#endif