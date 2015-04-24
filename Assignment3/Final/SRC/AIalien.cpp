#include "AI.h" 



void MoveAlienInDirectionOfShip(Alien &alien, Ship &ship)			//Moves Alien in direction of ship
{
	
	float relativeangle;
	relativeangle=RelativeAngleOfShipFromAlien(ship,alien);
	
		alien.SetXPos(alien.GetXPos()-5*sin(PI*relativeangle/180));
		alien.SetYPos(alien.GetYPos()+5*cos(PI*relativeangle/180));
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

void TurnAlienInDirectionOfShip(Alien &alien, Ship &ship,bool &finished)				//Turns alien in direction of ship
{
	float alienAngle;

	float relativeangle=RelativeAngleOfShipFromAlien(ship,alien);
	if (fabs(relativeangle-180.0)<0.2 || fabs(180+relativeangle)<0.2)
	{
		// CHill
	}
	else
	{
	if (alien.GetAngle()<=180)
	 	alienAngle=alien.GetAngle();
	else 
	 	alienAngle =alien.GetAngle()-360;


	
	if (fabs(relativeangle-alienAngle)<= 1 )
	{

		
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
}

void FireBulletForAlien(Alien &alien, Board &board)							//Fires bullet for alien
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

void FireMissileForAlien(Alien &alien, Board &board)					//Fires Missile for ALien
{
	
	Bullet newb = Bullet();
	
	if (alien.GetMissiles()>0)
	{
		
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