#include "OPAI.h" 




void OPUpdateAIBoard(Board &board) //Calls the update functions of the entire board
{

	OPUpdatePlayerAI(board);
	OPUpdateAlien(board);
	// if (board.GetVectorBullets().size()>0)
	OPUpdateMissile(board);
}

void OPUpdateAlien(Board &board) // Updates aliens
{
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
	for (int i=0;i<CurrentAliens.size();i++)
	{
		OPMoveAlien(CurrentAliens[i]);
	}
	board.SetVectorAliens(CurrentAliens);
}

 void OPUpdatePlayerAI(Board &board) // Updates all AI ships
 {
 	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
 	std::vector<Ship> CurrentShips = board.GetVectorShips();
 	
	bool nearEnough;
 	
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
				OPTurnShipInDirectionOfShip(CurrentShips[i],CurrentShips[nearestShip],finished); // turns ship in direction of other ship
	
				OPMoveShipInDirectionOfShip(CurrentShips[i],CurrentShips[nearestShip]); // moves ship in direction of other ship
				if (finished==true)
				{
					
					if (rand()%10==9)
						OPFireBulletForShip(CurrentShips[i],board);
					
				}


			}



				
 		}
 	}
 	board.SetVectorShips(CurrentShips); 	//actual updation
}

void OPUpdateMissile(Board &board) //Updates all missiles on board
{
	
	OPUpdateShipMissile(board);
	std::vector<Bullet> VectorBullets=board.GetVectorBullets();
			
	for (int i=0;i<VectorBullets.size();i++)
	{
		if(VectorBullets.at(i).GetTypeAI() == true)
		{
			VectorBullets.at(i).SetXPos(VectorBullets.at(i).GetXPos()+VectorBullets.at(i).GetVelX()); //setting new position of missiles
			VectorBullets.at(i).SetYPos(VectorBullets.at(i).GetYPos()+VectorBullets.at(i).GetVelY());
		}
	}
	board.SetVectorBullets(VectorBullets); //actual updation
}