#include "OPAI.h" 




void OPUpdateAIBoard(Board &board)
{

	OPUpdatePlayerAI(board);
	OPUpdateAlien(board);
	// if (board.GetVectorBullets().size()>0)
	OPUpdateMissile(board);
}

void OPUpdateAlien(Board &board)
{
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
	for (int i=0;i<CurrentAliens.size();i++)
	{
		OPMoveAlien(CurrentAliens[i]);
	}
	board.SetVectorAliens(CurrentAliens);
}

 void OPUpdatePlayerAI(Board &board)
 {
 	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
 	std::vector<Ship> CurrentShips = board.GetVectorShips();
 	//std::vector<Alien> CurrentAliens = board.GetVectorAliens();
// 	WhatItShouldDo action;
	bool nearEnough;
 	//int nearestAlien;
 	int nearestShip;
 	for (int i=0;i<CurrentShips.size();i++)
 	{
 		if (CurrentShips[i].GetLives()==0)
 			continue;
 		if (CurrentShips[i].IfAIControl())
 		{
			
 			std::pair<int,bool> NearestShipPair = OPFindNearestShip(CurrentShips[i],CurrentShips);
			
 			nearEnough = NearestShipPair.second;
 			nearestShip= NearestShipPair.first;

 			if (nearEnough==1)
			{
				bool finished=false;
				OPTurnShipInDirectionOfShip(CurrentShips[i],CurrentShips[nearestShip],finished);
	
				OPMoveShipInDirectionOfShip(CurrentShips[i],CurrentShips[nearestShip]);
		//		std::cout<<"Turning Alien in Direction of Ship \n";
				if (finished==true)
				{
					// std::cout<<"Finished set to true \n";
					
					if (rand()%10==9)
						OPFireBulletForShip(CurrentShips[i],board);
					
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

void OPUpdateMissile(Board &board)
{
	// std::cout<<"Update Missile called\n";
	//UpdateAlienMissile(board);
	OPUpdateShipMissile(board);
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