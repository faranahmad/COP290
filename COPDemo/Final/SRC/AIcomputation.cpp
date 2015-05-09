#include "AI.h" 

int ClosestAlienEnemy(std::vector<Alien> &Aliens,int NumberAliens, Bullet &actualmissile, double maxDistance) //Finds the closest alien to a missile in its field of view
{
	int closestAlien = -1;
	float leastDistance = maxDistance; //Infinity
	for (int i=0; i<NumberAliens;i++)
	{
		if (AlienInArc(Aliens[i],actualmissile)==true && DistanceOfAlienFromMissile(Aliens[i],actualmissile) < leastDistance)
		{
			leastDistance=DistanceOfAlienFromMissile(Aliens[i],actualmissile);
			closestAlien = i;
		}
	}
	return closestAlien;
}

int ClosestShipEnemy(std::vector<Ship> &Ships,int NumberShips, Bullet &actualmissile, double maxDistance) //Finds the closest ship to a missile in its field of view
{
	int closestShip = -1;
	float leastDistance = maxDistance; //Infinity
	for (int i=0; i<NumberShips;i++)
	{
		if (ShipInArc(Ships[i],actualmissile) && DistanceOfShipFromMissile(Ships[i],actualmissile) < leastDistance)
		{
			leastDistance = DistanceOfShipFromMissile(Ships[i],actualmissile);
			closestShip = i;
		}
	}
	return closestShip;
}

bool AlienInArc(Alien &alien, Bullet &actualmissile)						//checks if alien is in field of view of missile
{
	if (fabs(RelativeAngleAlienFromMissile(alien,actualmissile)*180/PI)<theta)
		return true;
	else 
		return false;
}

bool ShipInArc(Ship &ship, Bullet &actualmissile)                          //checks if ship is in field of view of missile
{
	if (fabs(RelativeAngleShipFromMissile(ship,actualmissile)*180/PI)<theta)
		return true;
	else 
		return false;
}

float RelativeAngleAlienFromMissile(Alien &alien,Bullet &actualmissile)	//for relative angle between the two
{
	float angle;

	if (alien.GetXPos()-actualmissile.GetXPos() == 0.0)
	{
		if ((alien.GetYPos()-actualmissile.GetYPos())>0)
			angle= (float) 0.0;
		else
			angle= 180.0;
	} 
	else
	{
		if (alien.GetXPos()-actualmissile.GetXPos()>0)
			angle= ((float) atan( (alien.GetYPos()-actualmissile.GetYPos())/ (alien.GetXPos()-actualmissile.GetXPos())) * 180/PI - 90.0);
		else
			angle= ((float) atan((alien.GetYPos()-actualmissile.GetYPos()) / (alien.GetXPos()-actualmissile.GetXPos())) * 180/PI + 90.0);
	}

	
	return (actualmissile.GetAngle()-angle)*PI/180.0;
}

float RelativeAngleShipFromMissile(Ship &ship,Bullet &actualmissile) // for relative angle between the two
{
	float angle;

	if (ship.GetXPos()-actualmissile.GetXPos() == 0.0)
	{
		if ((ship.GetYPos()-actualmissile.GetYPos())>0)
			angle= (float) 0.0;
		else
			angle= 180.0;
	} 
	else
	{
		if (ship.GetXPos()-actualmissile.GetXPos()>0)
			angle= ((float) atan( (ship.GetYPos()-actualmissile.GetYPos())/ (ship.GetXPos()-actualmissile.GetXPos())) * 180/PI - 90.0);
		else
			angle= ((float) atan((ship.GetYPos()-actualmissile.GetYPos()) / (ship.GetXPos()-actualmissile.GetXPos())) * 180/PI + 90.0);
	}

	return (actualmissile.GetAngle()-angle)*PI/180.0;
}

float RelativeAngleAlientoMissilePosition(Alien &alien, Bullet &actualmissile) // angle between alien and missile position
{
	float angle;

	if (alien.GetXPos()-actualmissile.GetXPos() == 0.0)
	{
		if ((alien.GetYPos()-actualmissile.GetYPos())>0)
			angle= (float) 0.0;
		else
			angle= 180.0;
	} 
	else
	{
		if (alien.GetXPos()-actualmissile.GetXPos()>0)
			angle= ((float) atan( (alien.GetYPos()-actualmissile.GetYPos())/ (alien.GetXPos()-actualmissile.GetXPos())) * 180/PI - 90.0);
		else
			angle= ((float) atan((alien.GetYPos()-actualmissile.GetYPos()) / (alien.GetXPos()-actualmissile.GetXPos())) * 180/PI + 90.0);
	}

	return angle;

}


float RelativeAngleShiptoMissilePosition(Ship &ship, Bullet &actualmissile) //angle between ship and missile
{
	float angle;

	if (ship.GetXPos()-actualmissile.GetXPos() == 0.0)
	{
		if ((ship.GetYPos()-actualmissile.GetYPos())>0)
			angle= (float) 0.0;
		else
			angle= 180.0;
	} 
	else
	{
		if (ship.GetXPos()-actualmissile.GetXPos()>0)
			angle= ((float) atan( (ship.GetYPos()-actualmissile.GetYPos())/ (ship.GetXPos()-actualmissile.GetXPos())) * 180/PI - 90.0);
		else
			angle= ((float) atan((ship.GetYPos()-actualmissile.GetYPos()) / (ship.GetXPos()-actualmissile.GetXPos())) * 180/PI + 90.0);
	}

	return angle;

}

float RelativeAngleOfShipFromAlien(Ship &ship,Alien &alien)//returns angle in degrees between ship and alien 
{
	float angle;

	if (ship.GetXPos()-alien.GetXPos() == 0.0)
	{
		if ((ship.GetYPos()-alien.GetYPos())>0)
			angle= (float) 0.0;
		else
			angle= 180.0;
	} 
	else
	{
		if (ship.GetXPos()-alien.GetXPos()>0)
			angle= ((float) atan( (ship.GetYPos()-alien.GetYPos())/ (ship.GetXPos()-alien.GetXPos())) * 180/PI - 90.0);
		else
			angle= ((float) atan((ship.GetYPos()-alien.GetYPos()) / (ship.GetXPos()-alien.GetXPos())) * 180/PI + 90.0);
	}

	return angle;
}



float RelativeAngleOfAlienFromShip(Alien& alien,Ship &ship)//returns angles in degrees between alien and ship
{
	float angle;

	if (alien.GetXPos()-ship.GetXPos() == 0.0)
	{
		if ((alien.GetYPos()-ship.GetYPos())>0)
			angle= (float) 0.0;
		else
			angle= 180.0;
	} 
	else
	{
		if (alien.GetXPos()-ship.GetXPos()>0)
			angle= ((float) atan( (alien.GetYPos()-ship.GetYPos())/ (alien.GetXPos()-ship.GetXPos())) * 180/PI - 90.0);
		else
			angle= ((float) atan((alien.GetYPos()-ship.GetYPos()) / (alien.GetXPos()-ship.GetXPos())) * 180/PI + 90.0);
	}

	return angle;
}

std::pair<int,bool> FindNearestAlien(Ship &ship, std::vector<Alien> &CurrentAliens) //finds the nearest alien to ship
{
	bool nearEnough;
	float min = INT_MAX;
	int nearestAlien = -1;
	bool checker=false;
	for (int j=0; j<CurrentAliens.size(); j++)
	{
		float dist = DistanceOfAlienFromShip(CurrentAliens[j],ship);
		
		if (dist < min)
		{
			checker=true;
			min = dist;
			nearestAlien = j;
		}
	}

	if (checker==true)
		nearEnough = true;
	else 
		nearEnough = false;

	return std::pair<int,bool> (nearestAlien,nearEnough);

}

std::pair<int,bool> FindNearestShip(Alien &alien, std::vector<Ship> &CurrentShips) // finds nearest ship to alien
{
	bool nearEnough;
	float min = INT_MAX;
	
	int nearestShip = -1;
	bool checker=false;
	for (int j=0; j<CurrentShips.size(); j++)
	{
		if (CurrentShips[j].GetLives()>0)
		{
			
			float dist=DistanceOfShipFromAlien(CurrentShips[j],alien);
			//std::cout<<"Distance "<<dist<<"\n";
			
			if (dist < min)
			{
				checker=true;
				
				min = dist;
				nearestShip = j;
			}
		}
	}
	
	

	if (checker==true)
			nearEnough = true;
	else 
		nearEnough = false;

	return std::pair<int,bool> (nearestShip,nearEnough);

}

float DistanceOfAlienFromMissile(Alien &alien, Bullet &actualmissile) // finds distance of alien from missile
{
	return pow((alien.GetXPos() - actualmissile.GetXPos()),2) + pow((alien.GetYPos()-actualmissile.GetYPos()),2);
}

float DistanceOfShipFromMissile(Ship &ship, Bullet &actualmissile) // finds distance of ship from missile
{
	return pow((ship.GetXPos()-actualmissile.GetXPos()),2) + pow((ship.GetYPos()-actualmissile.GetYPos()),2);
}

float DistanceOfShipFromAlien(Ship &ship, Alien &alien) //finds distance of ship from alien
{
	return pow((alien.GetXPos()-ship.GetXPos()),2) + pow((alien.GetYPos()-ship.GetYPos()),2);

}

float DistanceOfAlienFromShip(Alien &alien, Ship &ship) //same as above
{
	return pow((alien.GetXPos()-ship.GetXPos()),2) + pow((alien.GetYPos()-ship.GetYPos()),2);

}

bool AlienIsInViewOfShip(Board &board, Ship &ship) // checks whether alien is in field of view of ship
{
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
	for (int i=0 ; i< CurrentAliens.size(); i++ )
	{
		if (fabs(RelativeAngleOfAlienFromShip(CurrentAliens[i],ship)-ship.GetAngle()) < ANGLEOFVIEW)
			return true;
	}
	return false;
}

bool ShipIsInViewOfAlien(Board &board, Alien &alien) // checks whether ship is in field of view of alien
{
	std::vector<Ship> CurrentShips = board.GetVectorShips();
	for (int i=0 ; i< CurrentShips.size(); i++ )
	{
		if (fabs(RelativeAngleOfShipFromAlien(CurrentShips[i],alien)-alien.GetAngle()) < ANGLEOFVIEW)
			return true;
	}
	return false;
}

