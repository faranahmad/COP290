#include "Alien.h" 

Alien::Alien()
{
	XPos = 0.0;
	YPos = 0.0;
	Angle = 0.0;
	Level = 1;
	PresentLives = 1;
	NumberBullets = 2;
	NumberMissiles = 3;
	AlienType = 0;
}

float Alien::GetXPos()
{
	return XPos;
}

float Alien::GetYPos()
{
	return YPos;
}

float Alien::GetAngle()
{
	return Angle;
}

Color Alien::GetColor()
{
	return ColorOfAlien;
}

int Alien::GetLives()
{
	return PresentLives;
}

int Alien::GetLevel()
{
	return Level;
}

int Alien::GetType()
{
	return AlienType;
}

int Alien::GetBullets()
{
	return NumberBullets;
}

int Alien::GetMissiles()
{
	return NumberMissiles;
}


void Alien::SetXPos(float xposition)
{
	XPos = xposition;
}

void Alien::SetYPos(float yposition)
{
	YPos = yposition;
}

void Alien::SetAngle(float inclination_angle)
{
	Angle = inclination_angle;
}

void Alien::SetColor(Color alien_color)
{
	ColorOfAlien = alien_color;
}

void Alien::SetColorFloat(int red,int green,int blue)
{
	ColorOfAlien.SetRGB(red,green,blue);
}

void Alien::SetColorFloat2(float r,float g,float b)
{
	ColorOfAlien.SetRGBFloat(r,g,b);
}

void Alien::SetLevel(int alien_level)
{
	Level = alien_level;
}

void Alien::SetLives(int alien_lives)
{
	PresentLives = alien_lives;
}

void Alien::SetBullets(int bullet_number)
{
	NumberBullets = bullet_number;
}

void Alien::SetMissiles(int missile_number)
{
	NumberMissiles = missile_number;
}

void Alien::SetType(int type_alien)
{
	AlienType = type_alien;
}

void Alien::ReduceMissile()
{
	if (NumberMissiles > 0)
	{
		NumberMissiles -= 1;
	}
}
std::string Alien::GetSummary()
{
	return std::to_string(XPos) + "\t" + 
			std::to_string(YPos) + "\t" + 
			std::to_string(Angle) + "\t" + 
			std::to_string(ColorOfAlien.GetR()) + "," +
			std::to_string(ColorOfAlien.GetB()) + "," +
			std::to_string(ColorOfAlien.GetG()) + "\t" +
			std::to_string(Level) + "\t" +
			std::to_string(PresentLives) + "\t" +
			std::to_string(NumberBullets) + "\t" +
			std::to_string(NumberMissiles) + "\t" + 
			std::to_string(AlienType);
}