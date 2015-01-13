#ifndef BALL_H
#define BALL_H

#include <string>
#include <vector>

using namespace std;

class Ball
{
	public:
		Ball(double,double);
		Ball(double,double,double,double);

		double GetX();
		double GetY();
		double GetVelocityX();
		double GetVelocityY();
		double GetRadius();
		vector<float> GetColor();

		string GetBallInformation();

		void SetRadius(double);
		void SetPosition(double,double);
		void SetVelocity(double,double);
		void SetColor(vector<float>);
		void SetX(double);
		void SetY(double);
		void SetVelocityX(double);
		void SetVelocityY(double);

		void UpdateBall(double);

	private:
		double radius;
		double coord_x;
		double coord_y;
		double velocity_x;
		double velocity_y;
		vector<float> color;
};

#endif