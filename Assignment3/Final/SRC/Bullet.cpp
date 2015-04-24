#include "Bullet.h" 
#include <cstdlib>


Bullet::Bullet()
{
	XPos = 0.0;
	YPos = 0.0;
	VelX = 0.0;
	VelY = 0.0;
	TimeCreated = time(0);

}
//getting functions

//get the x axis position of bullet
float Bullet::GetXPos()
{
	return XPos;
} 

float Bullet::GetYPos()
{
	return YPos;
}
 
float Bullet::GetVelX()
{
	return VelX;
}

float Bullet::GetVelY()
{
	return VelY;
}


float Bullet::GetSpeed()
{
	return ((float) sqrt(VelX*VelX + VelY*VelY)); 
}

Color Bullet::GetColorOfBullet()
{
	return ColorOfBullet;
} 

//position of the ship in the vectorships from which bullet is fired 
int Bullet::GetShipId()
{
	return ShipId;
}

//for missiles controlled by AI
bool Bullet::GetTypeAI()
{
	return TypeAI;
}

//get if its alien's bullet or player's bullet
bool Bullet::GetTypePlayer()
{
	return TypePlayer;
}

//getting the current system time at which bullet was created
int Bullet::GetTimeCreated()
{
	return TimeCreated;
}


//setting functions
void Bullet::SetXPos(float xposition)
{
	XPos = xposition;
}

void Bullet::SetYPos(float yposition)
{
	YPos = yposition;
}

void Bullet::SetVelX(float xvelocity)
{
	VelX = xvelocity;
}

void Bullet::SetVelY(float yvelocity)
{
	VelY = yvelocity;
}

void Bullet::SetColorOfBullet(Color bulletcolor)
{
	ColorOfBullet = bulletcolor;
}

void Bullet::SetColorOfBulletfloat(int red,int green,int blue)
{
	ColorOfBullet.SetRGB(red,green,blue);	
}

void Bullet::SetColorFloat(float r,float g,float b) 
{
	ColorOfBullet.SetRGBFloat(r,g,b);
}

void Bullet::SetShipID(int ship_id)
{
	ShipId = ship_id;
}

void Bullet::SetTypeAI(bool AI)
{
	TypeAI = AI;
}

void Bullet::SetTypePlayer(bool type_player)
{
	TypePlayer = type_player;
}

void Bullet::SetTimeCreated(int t)
{
	TimeCreated = t;
}

void Bullet::ResetBulletState()
{
	//see later
	XPos = 0.0;
	YPos = 0.0;
	VelX = 0.0;
	VelY = 0.0;
	ColorOfBullet = Color(0.0,0.0,0.0);
	ShipId = -1	;						//right now assuming to come from alien
	TypeAI = true; 						//right now setting it to be controlled by AI
	TypePlayer = false;	
}

std::string Bullet::GetSummary()
{
	return (std::to_string(XPos) + "\t" + std::to_string(YPos) + "\t" 
	+ std::to_string(VelX) + "\t" + std::to_string(VelY) + "\t" 
	+ std::to_string(ColorOfBullet.GetR())+ "," + std::to_string(ColorOfBullet.GetG()) + "," 
	+ std::to_string(ColorOfBullet.GetB()) + "\t" + std::to_string(ShipId) + "\t"
	+ std::to_string(TypeAI) + "\t" + std::to_string(TypePlayer));
}

//return anfle of inclination with xaxis
float Bullet::GetAngle()
{
	if (VelX == 0.0)
	{
		if (VelY>0)
			return (float) 0.0;
		else
			return 180.0;
	} 
	else
	{
		if (VelX>0)
			return ((float) atan(VelY / VelX) * 180/PI - 90.0);
		else
			return ((float) atan(VelY / VelX) * 180/PI + 90.0);
	}
}

