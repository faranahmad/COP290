#include "AI.h" 




void UpdateAIBoard(Board &board)
{

	UpdatePlayerAI(board);
	UpdateAlien(board);
	// if (board.GetVectorBullets().size()>0)
	UpdateMissile(board);
}

 void UpdatePlayerAI(Board &board)
 {
 	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
 	std::vector<Ship> CurrentShips = board.GetVectorShips();
 	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
// 	WhatItShouldDo action;
	bool nearEnough;
 	int nearestAlien;
 	for (int i=0;i<CurrentShips.size();i++)
 	{
 		if (CurrentShips[i].GetLives()==0)
 			continue;
 		if (CurrentShips[i].IfAIControl())
 		{
			
 			std::pair<int,bool> NearestAlienPair = FindNearestAlien(CurrentShips[i],CurrentAliens);
			
 			nearEnough = NearestAlienPair.first;
 			nearestAlien= NearestAlienPair.second;

 			if (nearEnough==1)
			{
				bool finished=false;
				TurnShipInDirectionOfAlien(CurrentShips[i],CurrentAliens[nearestAlien],finished);
		//		std::cout<<"Turning Alien in Direction of Ship \n";
				if (finished==true)
				{
					// std::cout<<"Finished set to true \n";
					if(rand()%3==1)
						MoveShipInDirectionOfAlien(CurrentShips[i],CurrentAliens[nearestAlien]);
					else if (rand()%10==9)
						FireBulletForShip(CurrentShips[i],board);
					
				}


			}


// 			action = DecideActionForShip(board,CurrentShips[i],nearEnough);
// 			switch (action)
// 			{
// 				case Move:
// 					MoveShipInDirectionOfAlien(CurrentShips[i],CurrentAliens[nearestAlien]);
// 					break;
// 				case Turn:
// 					TurnShipInDirectionOfAlien(CurrentShips[i],CurrentAliens[nearestAlien]);
// 					break;
// 				case FireBullet:
// 					FireBulletForShip(CurrentShips[i],board);
// 					break;
// 				case FireMissile:
// 					FireMissileForShip(CurrentShips[i],board);
// 					break;

 //			}
				
 		}
 	}
 	board.SetVectorShips(CurrentShips); 	//actual updation
}

void UpdateAlien(Board &board)
{
	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
	std::vector<Ship> CurrentShips = board.GetVectorShips();
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
	WhatItShouldDo action;
	bool nearEnough;
	int nearestShip;
	//std::cout<<"starting for loop on aliens\n";
	for (int i=0; i<CurrentAliens.size(); i++)
	{

		std::pair<int, bool> NearestShipPair= FindNearestShip(CurrentAliens[i],CurrentShips);
		// std::cout<< " Nearest Ship "<<NearestShipPair.first<<" for alien "<<i<<"\n";
		nearestShip=NearestShipPair.first;
	//	std::cout<<"Nearest Ship "<< NearestShipPair.first<<"\n";
		// std::cout<<"Near Enough "<<NearestShipPair.second<<"\n";
		nearEnough=NearestShipPair.second;
	//	std::cout<<"got near enough\n";
		// std::cout<<" Distance of Nearest Ship from alien is "<<DistanceOfShipFromAlien(CurrentShips[nearestShip], CurrentAliens[i]);
		if (nearEnough==1)
		{
			bool finished=false;
			TurnAlienInDirectionOfShip(CurrentAliens[i],CurrentShips[nearestShip],finished);
	//		std::cout<<"Turning Alien in Direction of Ship \n";
			MoveAlienInDirectionOfShip(CurrentAliens[i],CurrentShips[nearestShip]);
			if (finished==true)
			{
				// std::cout<<"Finished set to true \n";
				//if(rand()%3==1)
				if (rand()%(120/(CurrentAliens[i].GetLevel()))==9)
					FireBulletForAlien(CurrentAliens[i],board);
				
			}


		}
		
	}

	// for (int i=0; i<CurrentAliens.size(); i++)
	// {
	// 	std::pair<int, bool> NearestShipPair= FindNearestShip(CurrentAliens[i],CurrentShips,nearEnough);
	// 	nearEnough = NearestShipPair.first;
	// 	nearestShip = NearestShipPair.second;
	// 	action = DecideActionForAlien(board,CurrentAliens[i],nearEnough);
	// 	std::cout<<"Nearest ship for Alien "<<i<<" is Ship "<<nearestShip<<"\n";
		
	// 	switch (action)
	// 		{
	// 			case Move:
	// 				MoveAlienInDirectionOfShip(CurrentAliens[i],CurrentShips[nearestShip]);
	// 				break;
	// 			case Turn:
	// 				TurnAlienInDirectionOfShip(CurrentAliens[i],CurrentShips[nearestShip]);
	// 				break;
	// 			case FireBullet:
	// 				FireBulletForAlien(CurrentAliens[i],board);
	// 				break;
	// 			case FireMissile:
	// 				FireMissileForAlien(CurrentAliens[i],board);
	// 				break;
	// 		}
	// }
	board.SetVectorAliens(CurrentAliens); //actual updation
}

void UpdateMissile(Board &board)
{
	// std::cout<<"Update Missile called\n";
	UpdateAlienMissile(board);
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
	board.SetVectorBullets(VectorBullets); //actual updation
}