#include "AI.h" 

//set parameters for nearEnough
//make a dodge bullet

WhatItShouldDo DecideActionForAlien(Board &board, Alien &alien, bool nearEnough)
{
	//herein lies the magic
	// std::cout<<"Trying to Decide \n";
	bool InView = ShipIsInViewOfAlien(board,alien);
	if (InView)
		{
			// std::cout<<"Alien has acquired its target\n";
			// std::cout<<"Angle of Alien "<<alien.GetAngle()<<"\n";
		}
	else
	{
		// std::cout<<"No ship in Field of View of Alien\n";
	}
	WhatItShouldDo action;
	// if ( InView && alien.GetMissiles() > 0) // add some randomness here
	// 	action = FireMissile;
	// else 
	if (nearEnough==true)	// add some randomness here
	{	
		// std::cout<<"Ship is near enough to the alien \n";
		if ( InView )
			action = FireBullet;
		else
			action = Turn;
	}
	else 
	{
		// std::cout<<"Ship isnt near enough to the alien \n";
		action = Move;
	}
	
	return action;	
	
}

void MoveAlienInDirectionOfShip(Alien &alien, Ship &ship)
{
	//float angle;
	float relativeangle;
	relativeangle=RelativeAngleOfShipFromAlien(ship,alien);
	// if (alien.GetAngle()<180)
	// 	angle=alien.GetAngle();
	// else 
	// 	angle =360-alien.GetAngle();
	//std::cout<<"Angle of alien"<<angle<<"\n";
	// std::cout<<"Relative angle"<<relativeangle<<"\n";
	//if (fabs(RelativeAngleOfShipFromAlien(ship,alien)-angle)<RIGHTANGLE)
	//{
		alien.SetXPos(alien.GetXPos()-5*sin(relativeangle));
		alien.SetYPos(alien.GetYPos()+5*cos(relativeangle));
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
	//}
	// else
	// {
	// 	alien.SetXPos(alien.GetXPos()+5*sin(angle));
	// 	alien.SetYPos(alien.GetYPos()-5*cos(angle));
	// 	if(alien.GetXPos() < -(NEGX))
	// 	{
	// 		alien.SetXPos(-(NEGX));
	// 	}
	// 	if(alien.GetXPos() > POSX)
	// 	{
	// 		alien.SetXPos(POSX);		
	// 	}
	// 	if(alien.GetYPos() > POSY)
	// 	{
	// 		alien.SetYPos(POSY);
	// 	}
	// 	if(alien.GetYPos() < -(NEGY))
	// 	{
	// 		alien.SetYPos(-(NEGY));
	// 	}
	// }
}

void TurnAlienInDirectionOfShip(Alien &alien, Ship &ship,bool &finished)
{
	float alienAngle;

	float relativeangle=RelativeAngleOfShipFromAlien(ship,alien);

	if (alien.GetAngle()<180)
	 	alienAngle=alien.GetAngle();
	else 
	 	alienAngle =alien.GetAngle()-360;

	// std::cout<<"Relative Angle "<<relativeangle<<" Alien angle "<<alienAngle<<"\n";
	
	if (fabs(relativeangle-alienAngle)<=5 )
	{

		// std::cout<<"setting finished true \n";
		// std::cout<<"Relative angle "<<relativeangle<<"\n";
		// std::cout<<"Alien angle "<<alienAngle<<"\n";
		finished=true;
	}
	else if (fabs(relativeangle-alienAngle) < minAngleofRotation && fabs(relativeangle-alienAngle)>1)
		{
			if (relativeangle>=0)
				alien.SetAngle(relativeangle);//check
			else
				alien.SetAngle(360+relativeangle);
		}
	else
	{
		float newrelativeangle;
		if (relativeangle>=0)
			newrelativeangle=relativeangle;
		else
			newrelativeangle=360+relativeangle;
		if (newrelativeangle>alien.GetAngle())
			alien.SetAngle(alien.GetAngle()+angularvelocity);
		else
			alien.SetAngle(alien.GetAngle()-angularvelocity);
		//change the sign of this according to where the alien is
	}
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