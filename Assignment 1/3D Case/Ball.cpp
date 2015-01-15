#include "Ball.h"
#include <cstdlib>

Ball::Ball(double x,double y,double z)
{
	// Constructor for Ball Data Type
	// Default Radius is 1.0
	// Default color is blue
	// Default Velocity is 0
	coord_x=x;
	coord_y=y;
	coord_z=z;
	radius=1;
	velocity_x=0;
	velocity_y=0;
	velocity_z=0;
	color = Color();
}


Ball::Ball(double limx,double limy,double limz,double random)
{
	std::vector<Color> GoodColors;

	GoodColors.push_back(Color());
	GoodColors.push_back(Color(46,204,113));
	GoodColors.push_back(Color(0,255,0));
	GoodColors.push_back(Color(0,0,255));
	GoodColors.push_back(Color(241,196,15));
	
	// Gives a random ball within  -limx to +limx and -limy to +limy
	radius = (rand() % 50) + 50;
	coord_x = (rand() % (int) (2* (limx-radius))) - (limx-radius);
	coord_y = (rand() % (int) (2* (limy-radius))) - (limy-radius);
	coord_z = (rand() % (int) (2* (limz-radius))) - (limz-radius);
	velocity_x=(rand() % 50) -25;
	velocity_y=(rand() % 50) -25;
	velocity_z=(rand() % 50) -25;
	color =GoodColors[rand() %GoodColors.size()];
	// color[0] = (rand() %256) /255.0;
	// color[1] = (rand() %256) /255.0;
	// color[2] = (rand() %256) /255.0;
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

double Ball::GetZ()
{
	// Returns the Z coordinate of the ball
	return coord_z;
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

double Ball::GetVelocityZ()
{
	// Returns Velocity Y of the ball
	return velocity_z;
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
	// Format is "coord_x coord_y coord_z velocity_x velocity_y velocity_z color"
	return "radius:"+std::to_string(radius)+"  xcoord:"+std::to_string(coord_x)+"  ycoord:"+std::to_string(coord_y)+"  zcoord:"+std::to_string(coord_z)+"   velocityx:"+std::to_string(velocity_x)+"  velocityy:"+std::to_string(velocity_y)+"  velocityz:"+std::to_string(velocity_z)+"  color:"+ std::to_string(color.GetR())+" "+std::to_string(color.GetG()) +" " +std::to_string(color.GetB());	
}

void Ball::SetRadius(double radius_value)
{
	// Updates the Radius of the ball
	radius=radius_value;
}

void Ball::SetPosition(double x_value,double y_value,double z_value)
{
	// Updates the position of the ball
	coord_x=x_value;
	coord_y=y_value;
	coord_z=z_value;
}

void Ball::SetVelocity(double velocityx,double velocityy,double velocityz)
{
	// Updates the velocity of the ball
	velocity_x=velocityx;
	velocity_y=velocityy;
	velocity_z=velocityz;
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

void Ball::SetZ(double z_new)
{
	// Updates the y coordinate of a ball
	coord_z=z_new;
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

void Ball::SetVelocityZ(double vz_new)
{
	// Updates the Y velocity of the ball
	velocity_z=vz_new;
}

void Ball::UpdateBall(double time_elapsed)
{
	// Updates the position of the ball after a time time_elapsed has elapsed using the velocity of the ball
	coord_x += time_elapsed*velocity_x;
	coord_y += time_elapsed*velocity_y;
}
