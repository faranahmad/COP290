#include "OPAI.h"

std::pair<int,bool> OPFindNearestShip(Ship &ship, std::vector<Ship> &CurrentShips) // Finds the nearest ship to given ship
{
	bool nearEnough;
	float min = INT_MAX;
	int nearestShip = -1;
	bool checker=false;
	for (int j=0; j<CurrentShips.size(); j++)
	{
		if(j==ship.GetId())
			continue;
		if (CurrentShips[j].GetLives()>0)
		{
			float dist=OPDistanceOfShipFromShip(CurrentShips[j],ship);
			
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

float OPRelativeAngleShipFromMissile(Ship &ship,Bullet &actualmissile) // Relative angle of ship from missile
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


float OPDistanceOfShipFromShip(Ship &ship1, Ship &ship2) // Finds the distance between two ships
{
	return pow((ship2.GetXPos()-ship1.GetXPos()),2) + pow((ship2.GetYPos()-ship1.GetYPos()),2);

}

float OPRelativeAngleOfShipFromShip(Ship& ship2,Ship &ship1)//returns angles in degrees
{
	float angle;

	if (ship2.GetXPos()-ship1.GetXPos() == 0.0)
	{
		if ((ship2.GetYPos()-ship1.GetYPos())>0)
			angle= (float) 0.0;
		else
			angle= 180.0;
	} 
	else
	{
		if (ship2.GetXPos()-ship1.GetXPos()>0)
			angle= ((float) atan( (ship2.GetYPos()-ship1.GetYPos())/ (ship2.GetXPos()-ship1.GetXPos())) * 180/PI - 90.0);
		else
			angle= ((float) atan((ship2.GetYPos()-ship1.GetYPos()) / (ship2.GetXPos()-ship1.GetXPos())) * 180/PI + 90.0);
	}

	return angle;
}



int OPClosestShipEnemy(std::vector<Ship> &Ships,int NumberShips, Bullet &actualmissile, double maxDistance) // finds closest ship 
{
	int closestShip = -1;
	float leastDistance = maxDistance; //Infinity
	for (int i=0; i<NumberShips;i++)
	{
		if (i==actualmissile.GetShipId())
			continue;

		if (OPShipInArc(Ships[i],actualmissile) && OPDistanceOfShipFromMissile(Ships[i],actualmissile) < leastDistance)
		{
			leastDistance = OPDistanceOfShipFromMissile(Ships[i],actualmissile);
			closestShip = i;
		}
	}
	return closestShip;
}


bool OPShipInArc(Ship &ship, Bullet &actualmissile) //checks whether the ship is in field of view of missile
{
	if (fabs(OPRelativeAngleShipFromMissile(ship,actualmissile)*180/PI)<theta)
		return true;
	else 
		return false;
}

float OPDistanceOfShipFromMissile(Ship &ship, Bullet &actualmissile) // Finds the distance between ship and missile
{
	return pow((ship.GetXPos()-actualmissile.GetXPos()),2) + pow((ship.GetYPos()-actualmissile.GetYPos()),2);
}

float OPRelativeAngleShiptoMissilePosition(Ship &ship, Bullet &actualmissile) // finds the relative angle between ship and missile position
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