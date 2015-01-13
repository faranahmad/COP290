#ifndef BALL_H
#define BALL_H

#include <string>
#include <vector>

using namespace std;

class Ball
{
	public:
		Ball(double,double);
		Ball(double,double,double);

		double GetX();
		double GetY();
		double GetZ();
		double GetVelocityX();
		double GetVelocityY();
		double GetVelocityZ();
		double GetRadius();
		vector<float> GetColor();

		string GetBallInformation();

		void SetRadius(double);
		void SetPosition(double,double,double);
		void SetVelocity(double,double,double);
		void SetColor(vector<float>);
		void SetX(double);
		void SetY(double);
		void SetZ(double);
		void SetVelocityX(double);
		void SetVelocityY(double);
		void SetVelocityZ(double);

		void UpdateBall(double);

	private:
		double radius;
		double coord_x;
		double coord_y;
		double coord_z;
		double velocity_x;
		double velocity_y;
		double velocity_z;
		vector<float> color;
};

#endif