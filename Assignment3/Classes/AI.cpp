//#define theta for InArc
//add acceleration for missiles
//define speed of aliens in terms of alien types and levels
//similarly for ships
//also define speed of rotation for the same
// ask faran for getangle of alien and ship
//relativeangles are in radians-correct
//ask faran how he updates position of ship 


/*To think/test
1.minDistanceforRotation
2.minAngleofRotation/angularvelocity
3.relativeangle ki direction
4. angle so that i can shoot, keep this different for different aliens :)
*/ 
#include "AI.h"
#define theta 45
#define minDistanceforRotation 100
#define minAngleofRotation 15
#define angularvelocity 10
#define maximumdistance 100000
 

// srand(time(NULL));

void UpdatePlayerAI(Board &board)
{
	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
	std::vector<Ship> CurrentShips = board.GetVectorShips();
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
	for (int i=0;i<CurrentShips.size();i++)
	{
		if (CurrentShips[i].IfAIControl())
		{
			bool nearEnough = false;
			int nearestAlien = FindNearestAlien(CurrentShips[i],CurrentAliens,nearEnough);
			if (nearEnough == false) //no aliens very near
				MoveInDirectionOf(CurrentShips[i],CurrentAliens[nearestAlien]); //should this also have turn in direction of ? I shoul keep both :O
			else
				TurnInDirectionOf(CurrentShips[i],CurrentAliens[nearestAlien]);
		}
	}
}

void UpdateAlien(Board &board)
{
	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
	std::vector<Ship> CurrentShips = board.GetVectorShips();
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();

	for (int i=0; i<CurrentAliens.size();i++)
	{
		
		bool nearEnough = false;
		int nearestShip = FindNearestShip(CurrentAliens[i],CurrentShips,nearEnough);
		if (nearEnough == false) //no ships very near
		{
			MoveInDirectionOf(CurrentAliens[i],CurrentShips[nearestShip]); //should this also have turn in direction of ? I shoul keep both :O
		}
		else
		{
			TurnInDirectionOf(CurrentAliens[i],CurrentShips[nearestShip]);
		}

		
	}
}

void UpdateAlienMissile(Board &board, int missile)
{
	Bullet CurrentBullet = board.GetNthBullet(missile);
	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
	std::vector<Ship> CurrentShips = board.GetVectorShips();
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
	for (int i=0; i<board.GetNumberBullets(); i++)
	{
		if (CurrentBullets[i].GetTypeAI()==true)
		{
			std::vector<Ship> temp=board.GetVectorShips();
			int target = ClosestShipEnemy(temp,board.GetNumberShips(),CurrentBullets[i]);
			Ship temp2=board.GetNthShip(target);
			UpdateVelocity(CurrentBullets[i] , temp2);
		}
	}
}


void MoveInDirectionOf(Ship &ship, Alien &alien)
{
	Ship tempShip1 = ship;
	Ship tempShip2 = ship;
}

void TurnInDirectionOf(Ship &ship, Alien &alien)
{
	float shipAngle = ship.GetAngle();
	if (abs(relativeAngle(ship,alien)) < minAngleofRotation)
		ship.SetAngle(shipAngle+relativeAngle(ship,alien));//check
	else
		ship.SetAngle(shipAngle+angularvelocity);//change the sign of this according to where the alien is
}

float relativeAngle(Ship &ship,Alien &alien)
{
	return atan((ship.GetYPos()-alien.GetYPos())/(ship.GetXPos()-alien.GetXPos()));
}





void MoveInDirectionOf(Alien &alien, Ship &ship)
{
	Alien tempAlien1 = alien;
	Alien tempAlien2 = alien;
}

void TurnInDirectionOf(Alien &alien, Ship &ship)
{
	float alienAngle = alien.GetAngle();
	if (abs(relativeAngle(alien,ship)) < minAngleofRotation)
	{
		alien.SetAngle(alienAngle+relativeAngle(alien,ship));//check
	}
	else
	{
		alien.SetAngle(alienAngle+angularvelocity);//change the sign of this according to where the alien is
	}

}

float relativeAngle(Alien& alien,Ship &ship)
{
	return atan((alien.GetYPos()-ship.GetYPos())/(alien.GetXPos()-ship.GetXPos()));
}

int FindNearestAlien(Ship &ship, std::vector<Alien> &CurrentAliens,bool nearEnough)
{
	float min = maximumdistance;
	int nearestAlien = -1;
	for (int j=0; j<CurrentAliens.size(); j++)
	{
		float dist = Distance(ship,CurrentAliens[j]);
		if (dist < min)
		{
			min = dist;
			nearestAlien = j;
		}
	}

	if (min<=minDistanceforRotation)
		nearEnough = true;
	else 
		nearEnough = false;

	return nearestAlien;

}

int FindNearestShip(Alien &alien, std::vector<Ship> &CurrentShips,bool nearEnough)
{
	float min = maximumdistance;
	int nearestShip = -1;
	for (int j=0; j<CurrentShips.size(); j++)
	{
		float dist=Distance(CurrentShips[j],alien);
		if (dist < min)
		{
			min = dist;
			nearestShip = j;
		}
	}

	if (min<=minDistanceforRotation)
		nearEnough = true;
	else 
		nearEnough = false;

	return nearestShip;

}

float Distance(Alien &alien, Bullet &actualmissile)
{
	//include math.h
	return pow((alien.GetXPos() - actualmissile.GetXPos()),2) + pow((alien.GetYPos()-actualmissile.GetYPos()),2);
}

float Distance(Ship &ship, Bullet &actualmissile)
{
	//include math.h
	return pow((ship.GetXPos()-actualmissile.GetXPos()),2) + pow((ship.GetYPos()-actualmissile.GetYPos()),2);
}

float Distance(Ship &ship, Alien &alien)
{
	return pow((alien.GetXPos()-ship.GetXPos()),2) + pow((alien.GetYPos()-ship.GetYPos()),2);

}
int ClosestAlienEnemy(std::vector<Alien> &Aliens,int NumberAliens, Bullet &actualmissile)
{
	//return -1 if none in range
	int closestAlien = -1;
	float leastDistance = 100000; //Infinity
	for (int i=0; i<NumberAliens;i++)
	{
		if (InArc(Aliens[i],actualmissile) && Distance(Aliens[i],actualmissile) < leastDistance)
		{
			leastDistance=Distance(Aliens[i],actualmissile);
			closestAlien = i;
		}
	}
	return closestAlien;

}

int ClosestShipEnemy(std::vector<Ship> &Ships,int NumberShips, Bullet &actualmissile)
{
	int closestShip = -1;
	float leastDistance = 100000; //Infinity
	for (int i=0; i<NumberShips;i++)
	{
		if (InArc(Ships[i],actualmissile) && Distance(Ships[i],actualmissile) < leastDistance)
		{
			leastDistance = Distance(Ships[i],actualmissile);
			closestShip = i;
		}
	}
	return closestShip;
}

bool InArc(Alien &alien, Bullet &actualmissile)
{
	if (abs(atan((alien.GetYPos()-actualmissile.GetYPos())/(alien.GetXPos()-actualmissile.GetXPos()))*180/PI-90.0-actualmissile.GetAngle())<theta)
		return true;
	else 
		return false;
}

bool InArc(Ship &ship, Bullet &actualmissile)
{
	if (abs(atan((ship.GetYPos()-actualmissile.GetYPos())/(ship.GetXPos()-actualmissile.GetXPos()))*180/PI-90.0-actualmissile.GetAngle())<theta)
		return true;
	else 
		return false;
}


void UpdateShipMissile(Board &board, int missile)
{
	Bullet CurrentBullet = board.GetNthBullet(missile);
	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
	std::vector<Ship> CurrentShips = board.GetVectorShips();
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
	for (int i=0; i<board.GetNumberBullets(); i++)
	{
		if (CurrentBullets[i].GetTypeAI()==true)
		{
			std::vector<Alien> temp=board.GetVectorAliens();
			int target = ClosestAlienEnemy(temp,board.GetNumberAliens(),CurrentBullets[i]);
			Alien temp2=board.GetNthAlien(target);

			UpdateVelocity(CurrentBullets[i],temp2);
		}
	}
}

void UpdateMissile(Board &board, int missile)
{
	int NumberBullets=board.GetNumberBullets();
	std::vector<Bullet> VectorBullets = board.GetVectorBullets();
	for (int i=0 ;i<NumberBullets; i++)
	{
		
			if (VectorBullets[i].GetShipId()==-1)
			{
				UpdateAlienMissile(board,i);
			}
			else
			{
				UpdateShipMissile(board,i);
			}
		
	}
}

float relativeAngle(Alien &alien,Bullet &actualmissile)
{
	return atan((alien.GetYPos()-actualmissile.GetYPos())/(alien.GetXPos()-actualmissile.GetXPos()));
}

float relativeAngle(Ship &ship,Bullet &actualmissile)
{
	return atan((ship.GetYPos()-actualmissile.GetYPos())/(ship.GetXPos()-actualmissile.GetXPos()));
}

void UpdateVelocity(Bullet &actualmissile,Ship &ship)
{
	actualmissile.SetVelX(actualmissile.GetSpeed()*cos(relativeAngle(ship,actualmissile)));
	actualmissile.SetVelY(actualmissile.GetSpeed()*sin(relativeAngle(ship,actualmissile)));
}

void UpdateVelocity(Bullet &actualmissile,Alien &alien)
{
	actualmissile.SetVelX(actualmissile.GetSpeed()*cos(relativeAngle(alien,actualmissile)));
	actualmissile.SetVelY(actualmissile.GetSpeed()*sin(relativeAngle(alien,actualmissile)));
}
void UpdateAIBoard(Board &board)
{
	int NumberShips = board.GetNumberShips();
	int NumberAliens = board.GetNumberAliens();
	int NumberBullets = board.GetNumberBullets();
	
	for (int i=0 ; i < NumberShips ; i++)
	{
		Ship CurrentPlayer = board.GetNthShip(i);
		if (CurrentPlayer.GetAIControlLevel() != -1)
		{
			UpdatePlayerAI(board);
		}
	}

	for (int i=0 ; i < NumberAliens ; i++)
	{
		Alien CurrentAlien = board.GetNthAlien(i);
		UpdateAlien(board);
	}

	for (int i=0 ; i < NumberBullets ; i++)
	{
		Bullet CurrentBullet = board.GetNthBullet(i);
		if (CurrentBullet.GetTypeAI() == true)
		{
			UpdateMissile(board,i);
		}
	}
}