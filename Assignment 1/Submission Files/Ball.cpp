#include "Ball.h"
#include <cstdlib>

Ball::Ball(int x,int y)
{
	// Constructor for Ball Data Type
	// Default Radius is 1.0
	// Default color is blue
	// Default Velocity is 0
	coord_x=x;
	coord_y=y;
	radius=1;
	velocity_x=0;
	velocity_y=0;
	color = std::vector<float> (3,0.5f);
}

Ball::Ball(int limx,int limy,int random)
{
	// Gives a random ball within  -limx to +limx and -limy to +limy
	radius = (rand() % 100) + 100;
	coord_x = (rand() % (2* (limx-radius))) - (limx-radius);
	coord_y = (rand() % (2* (limy-radius))) - (limy-radius);
	velocity_x=(rand() % 50) -25;
	velocity_y=(rand() % 50) -25;
	color = std::vector<float> (3,0.5f);
	color[0] = (rand() %256) /255.0;
	color[1] = (rand() %256) /255.0;
	color[2] = (rand() %256) /255.0;
}

int Ball::GetX()
{
	// Returns the X coordinate of the ball
	return coord_x;
}

int Ball::GetY()
{
	// Returns the Y coordinate of the ball
	return coord_y;
}

int Ball::GetVelocityX()
{
	// Returns Velocity X of the ball
	return velocity_x;
}

int Ball::GetVelocityY()
{
	// Returns Velocity Y of the ball
	return velocity_y;
}

int Ball::GetRadius()
{
	// Returns the Radius of the Ball
	return radius;
}

std::vector<float> Ball::GetColor()
{
	// Returns the color of the ball
	return color;
}

string Ball::GetBallInformation()
{
	// Returns the information about the ball
	// Format is "radius \t coord_x \t coord_y \t velocity_x \t velocity_y \t color"
	return "radius:"+std::to_string(radius)+"  xcoord:"+std::to_string(coord_x)+"  ycoord:"+std::to_string(coord_y)+"  velocityx:"+std::to_string(velocity_x)+"  velocityy:"+std::to_string(velocity_y)+"  color:"+ std::to_string(color[0])+" "+std::to_string(color[1]) +" " +std::to_string(color[2]);	
}

void Ball::SetRadius(int radius_value)
{
	// Updates the Radius of the ball
	radius=radius_value;
}

void Ball::SetPosition(int x_value,int y_value)
{
	// Updates the position of the ball
	coord_x=x_value;
	coord_y=y_value;
}

void Ball::SetVelocity(int velocityx,int velocityy)
{
	// Updates the velocity of the ball
	velocity_x=velocityx;
	velocity_y=velocityy;
}

void Ball::SetColor(std::vector<float> color_new)
{
	// Updates the color of the ball
	color=color_new;
}

void Ball::SetX(int x_new)
{
	// Updates the x coordinate of a ball
	coord_x=x_new;
}

void Ball::SetY(int y_new)
{
	// Updates the y coordinate of a ball
	coord_y=y_new;
}

void Ball::SetVelocityX(int vx_new)
{
	// Updates the X velocity of the ball
	velocity_x=vx_new;
}

void Ball::SetVelocityY(int vy_new)
{
	// Updates the Y velocity of the ball
	velocity_y=vy_new;
}

void Ball::UpdateBall(int time_elapsed)
{
	// Updates the position of the ball after a time time_elapsed has elapsed using the velocity of the ball
	coord_x += time_elapsed*velocity_x;
	coord_y += time_elapsed*velocity_y;
}
