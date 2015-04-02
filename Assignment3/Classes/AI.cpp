//#define theta for InArc
//add acceleration for missiles
//define speed of aliens in terms of alien types and levels
//similarly for ships
//also define speed of rotation for the same
// ask faran for getangle of alien and ship
//relativeangles are in radians-correct
//ask faran how he updates position of ship 


/*To think/test
1.minDistanceforRotation
2.minAngleofRotation/angularvelocity
3.relativeangle ki direction
4. angle so that i can shoot, keep this different for different aliens :)
*/ 
#include "AI.h"
#define theta 45
#define minDistanceforRotation 100
#define minAngleofRotation 15
#define angularvelocity 10
#define maximumdistance 100000
 

// srand(time(NULL));

void UpdateAIBoard(Board &board)
{
	UpdatePlayerAI(board);
	UpdateAlien(board);
	UpdateMissile(board);
		
	
}

void UpdatePlayerAI(Board &board)
{
	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
	std::vector<Ship> CurrentShips = board.GetVectorShips();
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
	for (int i=0;i<CurrentShips.size();i++)
	{
		if (CurrentShips[i].IfAIControl())
		{
			bool nearEnough = false;
			int nearestAlien = FindNearestAlien(CurrentShips[i],CurrentAliens,nearEnough);
			if (nearEnough == false) //no aliens very near
				MoveInDirectionOf(CurrentShips[i],CurrentAliens[nearestAlien]); //should this also have turn in direction of ? I shoul keep both :O
			else
				TurnInDirectionOf(CurrentShips[i],CurrentAliens[nearestAlien]);
		}
	}
}

void UpdateAlien(Board &board)
{
	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
	std::vector<Ship> CurrentShips = board.GetVectorShips();
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();

	for (int i=0; i<CurrentAliens.size();i++)
	{
		
		bool nearEnough = false;
		int nearestShip = FindNearestShip(CurrentAliens[i],CurrentShips,nearEnough);
		if (nearEnough == false) //no ships very near
		{
			MoveInDirectionOf(CurrentAliens[i],CurrentShips[nearestShip]); //should this also have turn in direction of ? I shoul keep both :O
		}
		else
		{
			TurnInDirectionOf(CurrentAliens[i],CurrentShips[nearestShip]);
		}

		
	}
}

void UpdateAlienMissile(Board &board)
{
	
	//std::cout<<"breakpoint1\n";
	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
	std::vector<Ship> CurrentShips = board.GetVectorShips();
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
	//std::cout<<"breakpoint1\n";
	for (int i=0; i<board.GetNumberBullets(); i++)
	{
		if (CurrentBullets[i].GetTypeAI()==true && CurrentBullets[i].GetShipId()==-1)
		{
			std::vector<Ship> temp=board.GetVectorShips();
			int target = ClosestShipEnemy(temp,board.GetNumberShips(),CurrentBullets[i]);
			if (target==-1)
			{

			}
			else
			{
				//std::cout<<"Target "<<target<<"\n";
				//std::cout<<"Alien Missile target Acquired\n";
				Ship temp2=board.GetNthShip(target);
				UpdateVelocity(CurrentBullets[i] , temp2);
			}
			
		}
	}
	board.SetVectorBullets(CurrentBullets);
}

void UpdateShipMissile(Board &board)
{
		
	
		
	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
	std::vector<Ship> CurrentShips = board.GetVectorShips();
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
		
	for (int i=0; i<board.GetNumberBullets(); i++)
	{
			
		if (CurrentBullets[i].GetTypeAI()==true && CurrentBullets[i].GetShipId()!=-1)
		{
				
			std::vector<Alien> temp=board.GetVectorAliens();
			int target = ClosestAlienEnemy(temp,board.GetNumberAliens(),CurrentBullets[i],board.MaxDistance());
				
			if (target==-1)
			{
				std::cout<<"No target acquired, velocity remains same \n";
			}
			else
			{
				//std::cout<<"Target "<<target<<"\n";
				//std::cout<<"Ship Missile target Acquired\n";
				Alien temp2=board.GetNthAlien(target);
			    // 	std::cout<<"breakpoint11\n";
			UpdateVelocity(CurrentBullets[i],temp2);
				//std::cout<<"breakpoint12\n";
			}
			
		}
	}
	board.SetVectorBullets(CurrentBullets);

}

int ClosestAlienEnemy(std::vector<Alien> &Aliens,int NumberAliens, Bullet &actualmissile, double maxDistance)
{
	//return -1 if none in range
	int closestAlien = -1;
	float leastDistance = maxDistance; //Infinity
	for (int i=0; i<NumberAliens;i++)
	{
		std::cout<<"Inarc "<<InArc(Aliens[i],actualmissile)<<" Distance "<<Distance(Aliens[i],actualmissile)<<"\n";
		if (InArc(Aliens[i],actualmissile)==true && Distance(Aliens[i],actualmissile) < leastDistance)
		{
			leastDistance=Distance(Aliens[i],actualmissile);
			closestAlien = i;
			//std::cout<<"closest alien "<<closestAlien<<"\n";
		}
	}
	return closestAlien;

}

bool InArc(Alien &alien, Bullet &actualmissile)
{
	if (abs(relativeAngle(alien,actualmissile)*180/PI)<theta)
		return true;
	else 
		return false;
}

bool InArc(Ship &ship, Bullet &actualmissile)
{
	if (abs(relativeAngle(ship,actualmissile)*180/PI)<theta)
		return true;
	else 
		return false;
}




float relativeAngle(Alien &alien,Bullet &actualmissile)
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

	//std::cout<<"angle "<<angle<<"\n";
	//std::cout<<"relative angle"<<actualmissile.GetAngle()-angle<<"\n";
	return (actualmissile.GetAngle()-angle)*PI/180.0;
}

float relativeAngle(Ship &ship,Bullet &actualmissile)
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



void UpdateMissile(Board &board)
{

	UpdateAlienMissile(board);
	//std::cout<<"breakpoint4\n";
	UpdateShipMissile(board);
	std::vector<Bullet> VectorBullets=board.GetVectorBullets();
			
		
	

	for (int i=0;i<VectorBullets.size();i++)
	{
		if(VectorBullets.at(i).GetTypeAI() == true)
		{
			VectorBullets.at(i).SetXPos(VectorBullets.at(i).GetXPos()+VectorBullets.at(i).GetVelX());
			VectorBullets.at(i).SetYPos(VectorBullets.at(i).GetYPos()+VectorBullets.at(i).GetVelY());
		}
	}
	board.SetVectorBullets(VectorBullets);

}

void UpdateVelocity(Bullet &actualmissile,Ship &ship)
{
	float angle=relativeAngletoMissile(ship,actualmissile);
	float speed=actualmissile.GetSpeed();
	actualmissile.SetVelX(speed*cos(angle));
	actualmissile.SetVelY(speed*sin(angle));
}

void UpdateVelocity(Bullet &actualmissile,Alien &alien)
{
	float angle=relativeAngletoMissile(alien,actualmissile);
	float speed=actualmissile.GetSpeed();
	actualmissile.SetVelX(speed*cos(angle));
	actualmissile.SetVelY(speed*sin(angle));
}

float relativeAngletoMissile(Alien &alien, Bullet &actualmissile)
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

float relativeAngletoMissile(Ship &ship, Bullet &actualmissile)
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




void MoveInDirectionOf(Ship &ship, Alien &alien)
{
	Ship tempShip1 = ship;
	Ship tempShip2 = ship;

}

void TurnInDirectionOf(Ship &ship, Alien &alien)
{
	float shipAngle = ship.GetAngle();
	if (abs(relativeAngle(ship,alien)) < minAngleofRotation)
		ship.SetAngle(shipAngle+relativeAngle(ship,alien));//check
	else
		ship.SetAngle(shipAngle+angularvelocity);//change the sign of this according to where the alien is
}

float relativeAngle(Ship &ship,Alien &alien)
{
	return atan((ship.GetYPos()-alien.GetYPos())/(ship.GetXPos()-alien.GetXPos()));
}





void MoveInDirectionOf(Alien &alien, Ship &ship)
{
	Alien tempAlien1 = alien;
	Alien tempAlien2 = alien;
}

void TurnInDirectionOf(Alien &alien, Ship &ship)
{
	float alienAngle = alien.GetAngle();
	if (abs(relativeAngle(alien,ship)) < minAngleofRotation)
	{
		alien.SetAngle(alienAngle+relativeAngle(alien,ship));//check
	}
	else
	{
		alien.SetAngle(alienAngle+angularvelocity);//change the sign of this according to where the alien is
	}

}

float relativeAngle(Alien& alien,Ship &ship)
{
	return atan((alien.GetYPos()-ship.GetYPos())/(alien.GetXPos()-ship.GetXPos()));
}

int FindNearestAlien(Ship &ship, std::vector<Alien> &CurrentAliens,bool nearEnough)
{
	float min = maximumdistance;
	int nearestAlien = -1;
	for (int j=0; j<CurrentAliens.size(); j++)
	{
		float dist = Distance(ship,CurrentAliens[j]);
		if (dist < min)
		{
			min = dist;
			nearestAlien = j;
		}
	}

	if (min<=minDistanceforRotation)
		nearEnough = true;
	else 
		nearEnough = false;

	return nearestAlien;

}

int FindNearestShip(Alien &alien, std::vector<Ship> &CurrentShips,bool nearEnough)
{
	float min = maximumdistance;
	int nearestShip = -1;
	for (int j=0; j<CurrentShips.size(); j++)
	{
		float dist=Distance(CurrentShips[j],alien);
		if (dist < min)
		{
			min = dist;
			nearestShip = j;
		}
	}

	if (min<=minDistanceforRotation)
		nearEnough = true;
	else 
		nearEnough = false;

	return nearestShip;

}

float Distance(Alien &alien, Bullet &actualmissile)
{
	//include math.h
	return pow((alien.GetXPos() - actualmissile.GetXPos()),2) + pow((alien.GetYPos()-actualmissile.GetYPos()),2);
}

float Distance(Ship &ship, Bullet &actualmissile)
{
	//include math.h
	return pow((ship.GetXPos()-actualmissile.GetXPos()),2) + pow((ship.GetYPos()-actualmissile.GetYPos()),2);
}

float Distance(Ship &ship, Alien &alien)
{
	return pow((alien.GetXPos()-ship.GetXPos()),2) + pow((alien.GetYPos()-ship.GetYPos()),2);

}


int ClosestShipEnemy(std::vector<Ship> &Ships,int NumberShips, Bullet &actualmissile)
{
	int closestShip = -1;
	float leastDistance = 100000; //Infinity
	for (int i=0; i<NumberShips;i++)
	{
		if (InArc(Ships[i],actualmissile) && Distance(Ships[i],actualmissile) < leastDistance)
		{
			leastDistance = Distance(Ships[i],actualmissile);
			closestShip = i;
		}
	}
	return closestShip;
}

