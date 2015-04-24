#include "OPAI.h"

void OPMoveShipInDirectionOfShip(Ship &ship1, Ship &ship2)
{
	float relativeangle;
	relativeangle=OPRelativeAngleOfShipFromShip(ship2,ship1);
	// float angle=ship.GetAngle();
	// if (abs(RelativeAngleOfAlienFromShip(alien,ship)-ship.GetAngle())<RIGHTANGLE)
	// {
		
		ship1.SetXPos(ship1.GetXPos()-5*sin(PI*relativeangle/180));
		ship1.SetYPos(ship1.GetYPos()+5*cos(PI*relativeangle/180));
		if(ship1.GetXPos() < -(NEGX))
		{
			ship1.SetXPos(-(NEGX));
		}
		if(ship1.GetXPos() > POSX)
		{
			ship1.SetXPos(POSX);		
		}
		if(ship1.GetYPos() > POSY)
		{
			ship1.SetYPos(POSY);
		}
		if(ship1.GetYPos() < -(NEGY))
		{
			ship1.SetYPos(-(NEGY));
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

void OPTurnShipInDirectionOfShip(Ship &ship1, Ship &ship2, bool &finished)
{
	// float shipAngle = ship.GetAngle();
	// if (abs(RelativeAngleOfAlienFromShip(alien,ship)) < minAngleofRotation)
	// 	ship.SetAngle(shipAngle+RelativeAngleOfAlienFromShip(alien,ship));//check
	// else
	// 	ship.SetAngle(shipAngle+angularvelocity);//change the sign of this according to where the alien is
	float shipAngle;

	float relativeangle=OPRelativeAngleOfShipFromShip(ship2,ship1);

	if (ship1.GetAngle()<180)
	 	shipAngle=ship1.GetAngle();
	else 
	 	shipAngle =ship1.GetAngle()-360;

	// std::cout<<"Relative Angle "<<relativeangle<<" Ship angle "<<shipAngle<<"\n";
	
	if (fabs(relativeangle-shipAngle)<=5 )//FINAL CHANGES HASH DEFINE THIS!!!!
	{

		// std::cout<<"setting finished true \n";
		// std::cout<<"Relative angle "<<relativeangle<<"\n";
		// std::cout<<"Alien angle "<<shipAngle<<"\n";
		finished=true;
	}
	else if (fabs(relativeangle-shipAngle) < minAngleofRotation && fabs(relativeangle-shipAngle)>1)
		{
			if (relativeangle>=0)
				ship1.SetAngle(relativeangle);//check
			else
				ship1.SetAngle(360+relativeangle);
		}
	else
	{
		float newrelativeangle;
		if (relativeangle>=0)
			newrelativeangle=relativeangle;
		else
			newrelativeangle=360+relativeangle;
		if (newrelativeangle>ship1.GetAngle())
			ship1.SetAngle(ship1.GetAngle()+angularvelocity);
		else
			ship1.SetAngle(ship1.GetAngle()-angularvelocity);
		//change the sign of this according to where the alien is
	}

}

void OPFireBulletForShip(Ship &ship, Board &board)
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