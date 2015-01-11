#ifndef BALL_H
#define BALL_H

#include <string>
#include <vector>

using namespace std;

class Ball
{
	public:
		Ball(int,int);
		Ball(int,int,int);

		int GetX();
		int GetY();
		int GetVelocityX();
		int GetVelocityY();
		int GetRadius();
		vector<float> GetColor();

		string GetBallInformation();

		void SetRadius(int);
		void SetPosition(int,int);
		void SetVelocity(int,int);
		void SetColor(vector<float>);
		void SetX(int);
		void SetY(int);
		void SetVelocityX(int);
		void SetVelocityY(int);

		void UpdateBall(int);

	private:
		int radius;
		int coord_x;
		int coord_y;
		int velocity_x;
		int velocity_y;
		vector<float> color;
};

#endif