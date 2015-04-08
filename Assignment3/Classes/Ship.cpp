#include "Ship.h"

Ship::Ship()
{
	Angle = 0.0;
	NumberMissiles = 500;
	Name = "abc";
	Lives=3;
}

Ship::Ship(int id)
{
	Id = id;
	Angle = 0.0;
	NumberMissiles = 5;
	Name = "abc";
	Lives=3;
	//add something
}

float Ship::GetXPos()
{
	return XPos;
}
float Ship::GetYPos()
{
	return YPos;
}
		
float Ship::GetAngle()
{
	return Angle;
}

std::string Ship::GetName()
{
	return Name;
}

Color Ship::GetColor()
{
	return ColorOfShip;
}
int Ship::GetLives()
{
	return Lives;
}

int Ship::GetScore()
{
	return Score;
}

int Ship::GetMultiplier()
{
	return Multiplier;
}
int Ship::GetKills()
{
	return Kills;
}
int Ship::GetId()
{
	return Id;
}

int Ship::GetNumberBullets()
{
	return NumberBullets;
}

int Ship::GetNumberMissiles()
{
	return NumberMissiles;
}

int Ship::GetAIControlLevel()
{
	return AILevel;
}

void Ship::SetXPos(float posx)
{
	XPos = posx;
}

void Ship::SetYPos(float posy)
{
	YPos = posy;
}
		
void Ship::SetAngle(float angle)
{
	Angle = angle;
}

void Ship::SetName(std::string name)
{
	Name = name;
}
		
void Ship::SetColorOfShip(Color color_ship)
{
	ColorOfShip = color_ship;
}

void Ship::SetColorFloat(int red,int green,int blue)
{
	ColorOfShip.SetRGB(red,green,blue);
}

void Ship::SetColorFloatInp(float r,float g,float b)
{
	ColorOfShip.SetRGBFloat(r,g,b);
}

void Ship::SetLives(int lives)
{
	Lives = lives;
}

void Ship::SetScore(int score)
{
	Score = score;
}

void Ship::SetMultiplier(int mult)
{
	Multiplier = mult;
}

void Ship::SetKills(int kills)
{
	Kills = kills;
}

void Ship::SetId(int id)
{
	Id = id;
}
void Ship::SetNumberBullets(int no_of_bullets)
{
	NumberBullets = no_of_bullets;
}

void Ship::SetNumberMissiles(int no_of_missiles)
{
	NumberMissiles = no_of_missiles;
}

//also sees if it is controlled by humans or not 
void Ship::SetAIControlLevel(int level)
{
	AILevel = level;	
}


bool Ship::IfAIControl()
{
	if(AILevel == -1)
	{
		return false;
	}
	else
	{
		true;
	}
}

bool Ship::IfHumanControl()
{
	if(AILevel < 0)
	{
		return true;
	}
	else 
	{
		false;
	}
}

void Ship::AddLife()
{
	Lives = Lives + 1;
}

void Ship::ReduceLife()
{
	Lives = Lives -1;
}

//has to change game points currently 10
void Ship::IncrementScore()
{
	Score = Score + 10*Multiplier;
}

void Ship::IncrementMultiplier()
{
	Multiplier += 1;
}

void Ship::ResetMultiplier()
{
	Multiplier = 1;
}

void Ship::AddKills()
{
	Kills += 1;
}

void Ship::ResetKills()
{
	Kills = 0;
}

void Ship::AddNumberBullets()
{
	NumberBullets += 1;
}

void Ship::ResetNumberBullets()
{
	NumberBullets = 1;
}

void Ship::AddMissile()
{
	NumberMissiles += 1;
}

void Ship::ReduceMissile()
{
	NumberMissiles -= 1;
}

std::string Ship::GetSummary()
{
	return(
			std::to_string(XPos) + "\t" +
			std::to_string(YPos) + "\t" + 
			std::to_string(Angle) + "\t" + 
			Name + "\t" + 
			std::to_string(ColorOfShip.GetR())+ "," + 
			std::to_string(ColorOfShip.GetG()) + "," + 
			std::to_string(ColorOfShip.GetB()) + "\t" + 
			std::to_string(Lives) + "\t" + 
			std::to_string(Score) + "\t" + 
			std::to_string(Multiplier) + "\t" + 
			std::to_string(Kills) + "\t" + 
			std::to_string(Id) + "\t" +
			std::to_string(NumberBullets) + "\t" +
			std::to_string(NumberMissiles) + "\t" + 
			std::to_string(AILevel)
		);
}
