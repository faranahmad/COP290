#include "ball.h"

Ball::Ball(float x,float y)
{
	// Constructor for Ball Data Type
	// Default Radius is 1.0
	// Default color is blue
	// Default Velocity is 0
	coord_x=x;
	coord_y=y;
	radius=1.0;
	velocity_x=0.0;
	velocity_y=0.0;
	color="blue";
}

float Ball::GetX()
{
	// Returns the X coordinate of the ball
	return coord_x;
}

float Ball::GetY()
{
	// Returns the Y coordinate of the ball
	return coord_y;
}

float Ball::GetVelocityX()
{
	// Returns Velocity X of the ball
	return velocity_x;
}

float Ball::GetVelocityY()
{
	// Returns Velocity Y of the ball
	return coord_y;
}

float Ball::GetRadius()
{
	// Returns the Radius of the Ball
	return radius;
}

string Ball::GetColor()
{
	// Returns the color of the ball
	return color;
}

void Ball::SetRadius(float radius_value)
{
	// Updates the Radius of the ball
	radius=radius_value;
}

void Ball::SetPosition(float x_value,float y_value)
{
	// Updates the position of the ball
	coord_x=x_value;
	coord_y=y_value;
}

void Ball::SetVelocity(float velocityx,float velocityy)
{
	// Updates the velocity of the ball
	velocity_x=velocityx;
	velocity_y=velocityy;
}

void Ball::SetColor(string color_new)
{
	// Updates the color of the ball
	color=color_new;
}

void Ball::UpdateBall(float time_elapsed)
{
	// Updates the position of the ball after a time time_elapsed has elapsed using the velocity of the ball
	coord_x += time_elapsed*velocity_x;
	coord_y += time_elapsed*velocity_y;
}
