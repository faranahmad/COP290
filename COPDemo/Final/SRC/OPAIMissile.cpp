#include "OPAI.h"

void OPUpdateShipMissile(Board &board)	//Updates all ship missiles
{
	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
	std::vector<Ship> CurrentShips = board.GetVectorShips();
		
	for (int i=0; i<board.GetNumberBullets(); i++)
	{
		if (CurrentBullets[i].GetTypeAI()==true)
		{
			
			int target = OPClosestShipEnemy(CurrentShips,board.GetNumberShips(),CurrentBullets[i],board.MaxDistance());
			if (target==-1)
			{
			}
			else
			{
				Ship temp2=board.GetNthShip(target);
				OPUpdateShipMissileVelocity(CurrentBullets[i],temp2);
			}
		}
	}
	board.SetVectorBullets(CurrentBullets);
}

void OPUpdateShipMissileVelocity(Bullet &actualmissile,Ship &ship2) //updates velocity of all ship missiles
{
	float angle=OPRelativeAngleShiptoMissilePosition(ship2,actualmissile);
	angle+=90;
	angle*=PI/180;
	float speed=actualmissile.GetSpeed();
	actualmissile.SetVelX(speed*cos(angle));
	actualmissile.SetVelY(speed*sin(angle));
}