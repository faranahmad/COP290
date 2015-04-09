#include "AI.h" 

WhatItShouldDo DecideActionForShip(Board &board, Ship &ship, bool nearEnough)
{
	//herein lies the magic
	bool InView = AlienIsInViewOfShip(board,ship);
	WhatItShouldDo action;
	if ( InView && ship.GetNumberMissiles() > 0) // add some randomness here
		action = FireMissile;
	else if (nearEnough==true)	// add some randomness here
	{	
		if ( InView )
			action = FireBullet;
		else
			action = Turn;
	}
	else 
		action = Move;
	
	return action;	
	
}

void MoveShipInDirectionOfAlien(Ship &ship, Alien &alien)
{
	float angle=ship.GetAngle();
	if (abs(RelativeAngleOfAlienFromShip(alien,ship)-ship.GetAngle())<RIGHTANGLE)
	{
		
		ship.SetXPos(ship.GetXPos()+5*cos(angle));
		ship.SetYPos(ship.GetYPos()+5*sin(angle));
		if(ship.GetXPos() < -(NEGX))
		{
			ship.SetXPos(-(NEGX));
		}
		if(ship.GetXPos() > POSX)
		{
			ship.SetXPos(POSX);		
		}
		if(ship.GetYPos() > POSY)
		{
			ship.SetYPos(POSY);
		}
		if(ship.GetYPos() < -(NEGY))
		{
			ship.SetYPos(-(NEGY));
		}
	}
	else
	{
		ship.SetXPos(ship.GetXPos()-5*cos(angle));
		ship.SetYPos(ship.GetYPos()-5*sin(angle));
		if(ship.GetXPos() < -(NEGX))
		{
			ship.SetXPos(-(NEGX));
		}
		if(ship.GetXPos() > POSX)
		{
			ship.SetXPos(POSX);		
		}
		if(ship.GetYPos() > POSY)
		{
			ship.SetYPos(POSY);
		}
		if(ship.GetYPos() < -(NEGY))
		{
			ship.SetYPos(-(NEGY));
		}
	}
}
void TurnShipInDirectionOfAlien(Ship &ship, Alien &alien)
{
	float shipAngle = ship.GetAngle();
	if (abs(RelativeAngleOfAlienFromShip(alien,ship)) < minAngleofRotation)
		ship.SetAngle(shipAngle+RelativeAngleOfAlienFromShip(alien,ship));//check
	else
		ship.SetAngle(shipAngle+angularvelocity);//change the sign of this according to where the alien is
}

void FireBulletForShip(Ship &ship, Board &board)
{
	Bullet newb = Bullet();
	
	float velx = 0- 10*sin(PI*ship.GetAngle()/180);
	float vely = 10* cos(PI*ship.GetAngle()/180);
	newb.SetXPos(ship.GetXPos());
	newb.SetYPos(ship.GetYPos());
	newb.SetVelX(velx);
	newb.SetVelY(vely);
	newb.SetShipID(ship.GetId());
	newb.SetTypeAI(false);
	newb.SetTypePlayer(true);
	board.InsertBullet(newb);
}

void FireMissileForShip(Ship &ship, Board &board)
{
	// Fire Missile 
	Bullet newb = Bullet();
	
	if (ship.GetNumberMissiles()>0)
	{
		ship.ReduceMissile();

		float velx = -10* sin(PI*ship.GetAngle()/180);
		float vely = 10* cos(PI*ship.GetAngle()/180);

		
		newb.SetXPos(ship.GetXPos());
		newb.SetYPos(ship.GetYPos());
		newb.SetVelX(velx);
		newb.SetVelY(vely);
		newb.SetShipID(ship.GetId());
		newb.SetTypeAI(true);
		newb.SetTypePlayer(true);
		//check if updated 
		board.InsertBullet(newb);	
	}
}



