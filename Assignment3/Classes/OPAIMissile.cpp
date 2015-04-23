void OPUpdateShipMissile(Board &board)
{
	// std::cout<<"Update Ship missile called\n";
	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
	std::vector<Ship> CurrentShips = board.GetVectorShips();
	//std::vector<Alien> CurrentAliens = board.GetVectorAliens();
		
	for (int i=0; i<board.GetNumberBullets(); i++)
	{
		if (CurrentBullets[i].GetTypeAI()==true)// && CurrentBullets[i].GetShipId()!=ALIENMISSILE)
		{
			
			int target = OPClosestShipEnemy(CurrentShips,board.GetNumberShips(),CurrentBullets[i],board.MaxDistance());
			// std::cout<<"Target of Missile "<<target<<"\n";
			if (target==-1)
			{
				// std::cout<<"No target acquired, velocity remains same \n";
			}
			else
			{
				// std::cout<<"Target Acquired "<<target<<"\n";
				Ship temp2=board.GetNthShip(target);
				OPUpdateShipMissileVelocity(CurrentBullets[i],temp2);
			}
		}
	}
	board.SetVectorBullets(CurrentBullets);
}

void OPUpdateShipMissileVelocity(Bullet &actualmissile,Ship &ship2)
{
	// std::cout<<"Update Ship Missile velocity called\n";
	float angle=OPRelativeAngleShiptoMissilePosition(ship2,actualmissile);
	angle+=90;
	angle*=PI/180;
	// std::cout<<"Relative angle between alien and missile "<<angle<<"\n";
	float speed=actualmissile.GetSpeed();
	actualmissile.SetVelX(speed*cos(angle));
	// std::cout<<"Setting velocity along X "<<speed*cos(angle)<<"\n";
	actualmissile.SetVelY(speed*sin(angle));
	// std::cout<<"Setting velocity along Y "<<speed*sin(angle)<<"\n";
}