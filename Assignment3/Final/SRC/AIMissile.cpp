
#include "AI.h"



void UpdateAlienMissile(Board &board)								//Updates the velocity of all missiles fired by aliens
{
	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
	std::vector<Ship> CurrentShips = board.GetVectorShips();
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
	for (int i=0; i<board.GetNumberBullets(); i++)
	{
		if (CurrentBullets[i].GetTypeAI()==true && CurrentBullets[i].GetShipId()==ALIENMISSILE)
		{
			
			int target = ClosestShipEnemy(CurrentShips,board.GetNumberShips(),CurrentBullets[i], board.MaxDistance());
			if (target==-1)
			{

			}
			else
			{
				Ship temp2=board.GetNthShip(target);
				UpdateAlienMissileVelocity(CurrentBullets[i] , temp2);
			}
		}
	}
	board.SetVectorBullets(CurrentBullets);
}

void UpdateShipMissile(Board &board)							//Updates the velocity of all missiles fired from ship
{
	
	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
	std::vector<Ship> CurrentShips = board.GetVectorShips();
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
		
	for (int i=0; i<board.GetNumberBullets(); i++)
	{
		if (CurrentBullets[i].GetTypeAI()==true && CurrentBullets[i].GetShipId()!=ALIENMISSILE)
		{
			
			int target = ClosestAlienEnemy(CurrentAliens,board.GetNumberAliens(),CurrentBullets[i],board.MaxDistance());
			
			if (target==-1)
			{
				
			}
			else
			{
				
				Alien temp2=board.GetNthAlien(target);
				UpdateShipMissileVelocity(CurrentBullets[i],temp2);
			}
		}
	}
	board.SetVectorBullets(CurrentBullets);
}

void UpdateAlienMissileVelocity(Bullet &actualmissile,Ship &ship)			//Updates velocity of single missile
{
	float angle=RelativeAngleShiptoMissilePosition(ship,actualmissile);
	float speed=actualmissile.GetSpeed();
	actualmissile.SetVelX(speed*cos(angle));
	actualmissile.SetVelY(speed*sin(angle));
}

void UpdateShipMissileVelocity(Bullet &actualmissile,Alien &alien)			//Updates velocity of single missile
{
	
	float angle=RelativeAngleAlientoMissilePosition(alien,actualmissile);
	angle+=90;
	angle*=PI/180;
	
	float speed=actualmissile.GetSpeed();
	actualmissile.SetVelX(speed*cos(angle));
	
	actualmissile.SetVelY(speed*sin(angle));
	
}























