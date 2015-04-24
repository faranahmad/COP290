#include "AI.h" 



void MoveShipInDirectionOfAlien(Ship &ship, Alien &alien)			//Moves Ship in Direction of ALien
{
	float relativeangle;
	relativeangle=RelativeAngleOfAlienFromShip(alien,ship);
	
		
		ship.SetXPos(ship.GetXPos()-5*sin(PI*relativeangle/180));
		ship.SetYPos(ship.GetYPos()+5*cos(PI*relativeangle/180));
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
void TurnShipInDirectionOfAlien(Ship &ship, Alien &alien, bool &finished)					//Turns Ship in direction of ALien
{
	
	float shipAngle;

	float relativeangle=RelativeAngleOfAlienFromShip(alien,ship);

	if (ship.GetAngle()<=180)
	 	shipAngle=ship.GetAngle();
	else 
	 	shipAngle =ship.GetAngle()-360;

	
	
	if (fabs(relativeangle-shipAngle)<=5 )
	{

		
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

void FireBulletForShip(Ship &ship, Board &board)				//Fires a bullet for the ship
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

void FireMissileForShip(Ship &ship, Board &board)			//Fires a missile for ship
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



