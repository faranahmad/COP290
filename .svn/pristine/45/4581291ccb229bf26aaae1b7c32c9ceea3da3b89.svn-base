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
	float relativeangle;
	relativeangle=RelativeAngleOfAlienFromShip(alien,ship);
	// float angle=ship.GetAngle();
	// if (abs(RelativeAngleOfAlienFromShip(alien,ship)-ship.GetAngle())<RIGHTANGLE)
	// {
		
		ship.SetXPos(ship.GetXPos()-5*sin(relativeangle));
		ship.SetYPos(ship.GetYPos()+5*cos(relativeangle));
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
	// }
	// else
	// {
	// 	ship.SetXPos(ship.GetXPos()-5*cos(angle));
	// 	ship.SetYPos(ship.GetYPos()-5*sin(angle));
	// 	if(ship.GetXPos() < -(NEGX))
	// 	{
	// 		ship.SetXPos(-(NEGX));
	// 	}
	// 	if(ship.GetXPos() > POSX)
	// 	{
	// 		ship.SetXPos(POSX);		
	// 	}
	// 	if(ship.GetYPos() > POSY)
	// 	{
	// 		ship.SetYPos(POSY);
	// 	}
	// 	if(ship.GetYPos() < -(NEGY))
	// 	{
	// 		ship.SetYPos(-(NEGY));
	// 	}
	// }
}
void TurnShipInDirectionOfAlien(Ship &ship, Alien &alien, bool &finished)
{
	// float shipAngle = ship.GetAngle();
	// if (abs(RelativeAngleOfAlienFromShip(alien,ship)) < minAngleofRotation)
	// 	ship.SetAngle(shipAngle+RelativeAngleOfAlienFromShip(alien,ship));//check
	// else
	// 	ship.SetAngle(shipAngle+angularvelocity);//change the sign of this according to where the alien is
	float shipAngle;

	float relativeangle=RelativeAngleOfAlienFromShip(alien,ship);

	if (ship.GetAngle()<180)
	 	shipAngle=ship.GetAngle();
	else 
	 	shipAngle =ship.GetAngle()-360;

	// std::cout<<"Relative Angle "<<relativeangle<<" Ship angle "<<shipAngle<<"\n";
	
	if (fabs(relativeangle-shipAngle)<=5 )
	{

		// std::cout<<"setting finished true \n";
		// std::cout<<"Relative angle "<<relativeangle<<"\n";
		// std::cout<<"Alien angle "<<shipAngle<<"\n";
		finished=true;
	}
	else if (fabs(relativeangle-shipAngle) < minAngleofRotation && fabs(relativeangle-shipAngle)>1)
		{
			if (relativeangle>=0)
				ship.SetAngle(relativeangle);//check
			else
				ship.SetAngle(360+relativeangle);
		}
	else
	{
		float newrelativeangle;
		if (relativeangle>=0)
			newrelativeangle=relativeangle;
		else
			newrelativeangle=360+relativeangle;
		if (newrelativeangle>ship.GetAngle())
			ship.SetAngle(ship.GetAngle()+angularvelocity);
		else
			ship.SetAngle(ship.GetAngle()-angularvelocity);
		//change the sign of this according to where the alien is
	}

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



