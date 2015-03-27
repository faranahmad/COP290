#include "Bullet.h" 



Bullet::Bullet()
{
	//by default would take everything
}

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

Color Bullet::GetColorOfBullet()
{
	return ColorOfBullet;
} 


int Bullet::GetShipId()
{
	return ShipId;
}

bool Bullet::GetTypeAI()
{
	return TypeAI;
}

bool Bullet::GetTypePlayer()
{
	return TypePlayer;
}

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

void Bullet::SetShipID(int ship_id)
{
	ShipId = ship_id;
}

void Bullet::SetTypeAI(bool AI)
{
	TypeAI = AI;
	TypePlayer = !AI;
}

void Bullet::SetTypePlayer(bool type_player)
{
	TypePlayer = type_player;
	TypeAI = !type_player;
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

float Bullet::GetAngle()
{
	if (VelX == 0.0)
	{
		return (float) PI/2.0;
	} 
	else
	{
		return (float) atan(VelY / VelX) * 180/PI;
	}
}