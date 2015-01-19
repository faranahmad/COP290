#include "Ball.h"
#include <cstdlib>
#include <iostream>

Ball::Ball(double x,double y)
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
	color = Color();
}

Ball::Ball(double limx,double limposy,double limnegy,double random)
{
	// Gives a random ball within  -limx to +limx and -limy to +limy

	std::vector<Color> GoodColors;
	GoodColors.push_back(Color(26,188,156));
	// GoodColors.push_back(Color(rand()%256,rand()%256,rand()%256));
	GoodColors.push_back(Color(192, 57, 43));
	GoodColors.push_back(Color(142, 68, 173));
	GoodColors.push_back(Color(243, 156, 18));
	GoodColors.push_back(Color(25,25,112));
	GoodColors.push_back(Color(139,0,0));
	GoodColors.push_back(Color(0,100,0));
	GoodColors.push_back(Color(0,139,69));
	GoodColors.push_back(Color(225, 215,0));
	GoodColors.push_back(Color(0, 0, 238));
	GoodColors.push_back(Color(85, 26, 139));
	GoodColors.push_back(Color(176, 23,21));
	GoodColors.push_back(Color(128, 0,0));
	GoodColors.push_back(Color(2, 2, 2));
	
	radius = (rand() % 50) + 50;
	coord_x = (rand() % (int) (2* (limx-radius))) - (limx-radius);
	double coord_y_1 = rand() % (int) (limposy-radius);
	double coord_y_2 = rand() % (int) (limnegy-radius);
	int x = rand() % 2;
	if(x == 0)
	{
		coord_y = coord_y_1;
	}
	else 
	{
		coord_y = 0-coord_y_2;	
		std::cout <<"In neg case\t"<<coord_y<<"\t"<<limnegy<<"\n";
	}
	//coord_y = (rand() % (int) (2* (limy-radius))) - (limy-radius);
	velocity_x=(rand() % 50) -25;
	velocity_y=(rand() % 50) -25;
	color =GoodColors[rand() % GoodColors.size()];
}

double Ball::GetX()
{
	// Returns the X coordinate of the ball
	return coord_x;
}

double Ball::GetY()
{
	// Returns the Y coordinate of the ball
	return coord_y;
}

double Ball::GetVelocityX()
{
	// Returns Velocity X of the ball
	return velocity_x;
}

double Ball::GetVelocityY()
{
	// Returns Velocity Y of the ball
	return velocity_y;
}

double Ball::GetRadius()
{
	// Returns the Radius of the Ball
	return radius;
}

Color Ball::GetColor()
{
	// Returns the color of the ball
	return color;
}

string Ball::GetBallInformation()
{
	// Returns the information about the ball
	// Format is "radius \t coord_x \t coord_y \t velocity_x \t velocity_y \t color"
	return "radius:"+std::to_string(radius)+"  xcoord:"+std::to_string(coord_x)+"  ycoord:"+std::to_string(coord_y)+"  velocityx:"+std::to_string(velocity_x)+"  velocityy:"+std::to_string(velocity_y)+"  color:"+ std::to_string(color.GetR())+" "+std::to_string(color.GetG()) +" " +std::to_string(color.GetB());	
}

void Ball::SetRadius(double radius_value)
{
	// Updates the Radius of the ball
	radius=radius_value;
}

void Ball::SetPosition(double x_value,double y_value)
{
	// Updates the position of the ball
	coord_x=x_value;
	coord_y=y_value;
}

void Ball::SetVelocity(double velocityx,double velocityy)
{
	// Updates the velocity of the ball
	velocity_x=velocityx;
	velocity_y=velocityy;
}

void Ball::SetColor(Color color_new)
{
	// Updates the color of the ball
	color=color_new;
}

void Ball::SetX(double x_new)
{
	// Updates the x coordinate of a ball
	coord_x=x_new;
}

void Ball::SetY(double y_new)
{
	// Updates the y coordinate of a ball
	coord_y=y_new;
}

void Ball::SetVelocityX(double vx_new)
{
	// Updates the X velocity of the ball
	velocity_x=vx_new;
}

void Ball::SetVelocityY(double vy_new)
{
	// Updates the Y velocity of the ball
	velocity_y=vy_new;
}

void Ball::UpdateBall(double time_elapsed)
{
	// Updates the position of the ball after a time time_elapsed has elapsed using the velocity of the ball
	coord_x += time_elapsed*velocity_x;
	coord_y += time_elapsed*velocity_y;
}
