#include "AI.h" 

//set parameters for nearEnough

WhatItShouldDo DecideActionForAlien(Board &board, Alien &alien, bool nearEnough)
{
	//herein lies the magic
	std::cout<<"Trying to Decide \n";
	bool InView = ShipIsInViewOfAlien(board,alien);
	if (InView)
		{
			std::cout<<"Alien has acquired its target\n";
			std::cout<<"Angle of Alien "<<alien.GetAngle()<<"\n";
		}
	else
		std::cout<<"No ship in Field of View of Alien\n";
	WhatItShouldDo action;
	// if ( InView && alien.GetMissiles() > 0) // add some randomness here
	// 	action = FireMissile;
	// else 
	if (nearEnough==true)	// add some randomness here
	{	
		std::cout<<"Ship is near enough to the alien \n";
		if ( InView )
			action = FireBullet;
		else
			action = Turn;
	}
	else 
	{
		std::cout<<"Ship isnt near enough to the alien \n";
		action = Move;
	}
	
	return action;	
	
}

void MoveAlienInDirectionOfShip(Alien &alien, Ship &ship)
{
	float angle=alien.GetAngle();
	if (abs(RelativeAngleOfShipFromAlien(ship,alien)-alien.GetAngle())<RIGHTANGLE)
	{
		alien.SetXPos(alien.GetXPos()+5*cos(angle));
		alien.SetYPos(alien.GetYPos()+5*sin(angle));
		if(alien.GetXPos() < -(NEGX))
		{
			alien.SetXPos(-(NEGX));
		}
		if(alien.GetXPos() > POSX)
		{
			alien.SetXPos(POSX);		
		}
		if(alien.GetYPos() > POSY)
		{
			alien.SetYPos(POSY);
		}
		if(alien.GetYPos() < -(NEGY))
		{
			alien.SetYPos(-(NEGY));
		}
	}
	else
	{
		alien.SetXPos(alien.GetXPos()-5*cos(angle));
		alien.SetYPos(alien.GetYPos()-5*sin(angle));
		if(alien.GetXPos() < -(NEGX))
		{
			alien.SetXPos(-(NEGX));
		}
		if(alien.GetXPos() > POSX)
		{
			alien.SetXPos(POSX);		
		}
		if(alien.GetYPos() > POSY)
		{
			alien.SetYPos(POSY);
		}
		if(alien.GetYPos() < -(NEGY))
		{
			alien.SetYPos(-(NEGY));
		}
	}
}

void TurnAlienInDirectionOfShip(Alien &alien, Ship &ship)
{
	float alienAngle = alien.GetAngle();
	if (abs(RelativeAngleOfShipFromAlien(ship,alien)) < minAngleofRotation)
		alien.SetAngle(alienAngle+RelativeAngleOfShipFromAlien(ship,alien));//check
	else
		alien.SetAngle(alienAngle+angularvelocity);//change the sign of this according to where the alien is
}

void FireBulletForAlien(Alien &alien, Board &board)
{
	Bullet newb = Bullet();
	float velx = 0- 10*sin(PI*alien.GetAngle()/180);
	float vely = 10* cos(PI*alien.GetAngle()/180);
	newb.SetXPos(alien.GetXPos());
	newb.SetYPos(alien.GetYPos());
	newb.SetVelX(velx);
	newb.SetVelY(vely);
	newb.SetShipID(-1);
	newb.SetTypeAI(false);
	newb.SetTypePlayer(false);
	board.InsertBullet(newb);
}

void FireMissileForAlien(Alien &alien, Board &board)
{
	// Fire Missile 
	Bullet newb = Bullet();
	
	if (alien.GetMissiles()>0)
	{
		//alien.ReduceMissile(); //faran shall make this
		float velx = -10* sin(PI*alien.GetAngle()/180);
		float vely = 10* cos(PI*alien.GetAngle()/180);
		newb.SetXPos(alien.GetXPos());
		newb.SetYPos(alien.GetYPos());
		newb.SetVelX(velx);
		newb.SetVelY(vely);
		newb.SetShipID(-1);
		newb.SetTypeAI(true);
		newb.SetTypePlayer(false);
		board.InsertBullet(newb);	
	}
}