#include "OPAI.h"

std::pair<int,bool> OPFindNearestShip(Ship &ship, std::vector<Ship> &CurrentShips)
{
	bool nearEnough;
	//std::cout<<"Entered here \n";
	float min = INT_MAX;
	//std::cout<<"maximumdistance = "<<min<<"\n";
	int nearestShip = -1;
	bool checker=false;
	for (int j=0; j<CurrentShips.size(); j++)
	{
		if(j==ship.GetId())
			continue;
		if (CurrentShips[j].GetLives()>0)
		{
			//std::cout<<"Entered Ship loop \n";
			float dist=OPDistanceOfShipFromShip(CurrentShips[j],ship);
			//std::cout<<"Distance "<<dist<<"\n";
			//std::cout<<"Distance is "<<dist<<" \n";
			if (dist < min)
			{
				checker=true;
				//std::cout<<"Updating min \n";
				min = dist;
				nearestShip = j;
			}
		}
	}
	//std::cout<<"minimum dist "<<min<<"\n";
	//std::cout<<"minDistanceforRotation "<<minDistanceforRotation<<"\n";

	if (checker==true)
			nearEnough = true;
	else 
		nearEnough = false;

	return std::pair<int,bool> (nearestShip,nearEnough);

}

float OPRelativeAngleShipFromMissile(Ship &ship,Bullet &actualmissile)
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


float OPDistanceOfShipFromShip(Ship &ship1, Ship &ship2)
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

// int OPClosestShipEnemy(std::vector<Ship> &Ships,int NumberShips, Bullet &actualmissile, double maxDistance)
// {
// 	int closestAlien = -1;
// 	float leastDistance = maxDistance; //Infinity
// 	for (int i=0; i<NumberShips;i++)
// 	{
// 		if (i==actualmissile.GetShipId())
// 			continue;
// 		// std::cout<<"AlienInarc "<<AlienInArc(Aliens[i],actualmissile)<<" Distance of alien from missile "<<DistanceOfAlienFromMissile(Aliens[i],actualmissile)<<"\n";
// 		if (ShipInArc(Aliens[i],actualmissile)==true && DistanceOfAlienFromMissile(Aliens[i],actualmissile) < leastDistance)
// 		{
// 			leastDistance=DistanceOfAlienFromMissile(Aliens[i],actualmissile);
// 			closestAlien = i;
// 			//std::cout<<"closest alien "<<closestAlien<<"\n";
// 		}
// 	}
// 	return closestAlien;
// }

int OPClosestShipEnemy(std::vector<Ship> &Ships,int NumberShips, Bullet &actualmissile, double maxDistance)
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


bool OPShipInArc(Ship &ship, Bullet &actualmissile)
{
	if (fabs(OPRelativeAngleShipFromMissile(ship,actualmissile)*180/PI)<theta)
		return true;
	else 
		return false;
}

float OPDistanceOfShipFromMissile(Ship &ship, Bullet &actualmissile)
{
	//include math.h
	return pow((ship.GetXPos()-actualmissile.GetXPos()),2) + pow((ship.GetYPos()-actualmissile.GetYPos()),2);
}

float OPRelativeAngleShiptoMissilePosition(Ship &ship, Bullet &actualmissile)
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