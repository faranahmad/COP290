#ifndef BOARD_H
#define BOARD_H

#include "Ball.h"
#include <vector>

class Board
{
	public:
		Board();
		Board(int,int,int);

		int GetDimensionX();
		int GetDimensionY();
		int GetNumberBalls ();
		vector<Ball> GetVectorBalls();
		Ball GetBallFromId (int);

		string GetBoardInformation();

		void SetDimensionX(int);
		void SetDimensionY(int);
		void SetNumberOfBalls(int);
		void SetVectorBalls(vector<Ball>);
		void SetBallFromId(int,Ball);

		void AddBallToBoard(Ball);
		void RemoveBallFromBoard();
		
		void UpdateBoard(int);

	private:
		int dimension_x;
		int dimension_y;
		int number_balls;
		vector<Ball> vector_of_balls;
};

#endif