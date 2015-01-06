#ifndef BALL_H
#define BALL_H

#include <string>

using namespace std;

class Ball
{
	public:
		Ball(float,float);

		float GetX();
		float GetY();
		float GetVelocityX();
		float GetVelocityY();
		float GetRadius();
		string GetColor();

		void SetRadius(float);
		void SetPosition(float,float);
		void SetVelocity(float,float);
		void SetColor(string);

	private:
		float radius;
		float coord_x;
		float coord_y;
		float velocity_x;
		float velocity_y;
		string color;
};

#endif