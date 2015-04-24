#include "AI.h" 




void UpdateAIBoard(Board &board)			//Calls the update functions of the entire board
{

	UpdatePlayerAI(board);
	UpdateAlien(board);
	UpdateMissile(board);
}

 void UpdatePlayerAI(Board &board)		//Updates all AI ships
 {
 	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
 	std::vector<Ship> CurrentShips = board.GetVectorShips();
 	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
	bool nearEnough;
 	int nearestAlien;
 	for (int i=0;i<CurrentShips.size();i++)
 	{
 		if (CurrentShips[i].GetLives()==0)
 			continue;
 		if (CurrentShips[i].IfAIControl())
 		{
			
 			std::pair<int,bool> NearestAlienPair = FindNearestAlien(CurrentShips[i],CurrentAliens);
			
 			nearEnough = NearestAlienPair.second;
 			nearestAlien= NearestAlienPair.first;

 			

 			if (nearEnough==1)
			{
				bool finished=false;
				TurnShipInDirectionOfAlien(CurrentShips[i],CurrentAliens[nearestAlien],finished);			//Turns Ship in direction of nearest Alien
				MoveShipInDirectionOfAlien(CurrentShips[i],CurrentAliens[nearestAlien]);					//Moves ship in direction of nearest alien
		
				if (finished==true)
				{	
					if (rand()%10==9)
						FireBulletForShip(CurrentShips[i],board);											//Fires bullet from ship
					
				}


			}



				
 		}
 	}
 	board.SetVectorShips(CurrentShips); 	//actual updation of ships
}

void UpdateAlien(Board &board)				//Updates all aliens in the Board
{
	std::vector<Bullet> CurrentBullets = board.GetVectorBullets();
	std::vector<Ship> CurrentShips = board.GetVectorShips();
	std::vector<Alien> CurrentAliens = board.GetVectorAliens();
	bool nearEnough;
	int nearestShip;
	for (int i=0; i<CurrentAliens.size(); i++)
	{

		std::pair<int, bool> NearestShipPair= FindNearestShip(CurrentAliens[i],CurrentShips);
		nearestShip=NearestShipPair.first;
		nearEnough=NearestShipPair.second;

		if (nearEnough==1)
		{
			bool finished=false;
		
			
			TurnAlienInDirectionOfShip(CurrentAliens[i],CurrentShips[nearestShip],finished);				//Turns aliens towards nearest ship
			MoveAlienInDirectionOfShip(CurrentAliens[i],CurrentShips[nearestShip]);							//Moves aliens in direction of nearest ship

		
			if (finished==true)
			{
				
				if (rand()%(60/(CurrentAliens[i].GetLevel()))==9)
					FireBulletForAlien(CurrentAliens[i],board);												//Fires a bullet for alien with the given probability
				
			}


		}
		
	}


	board.SetVectorAliens(CurrentAliens); //actual updation
}

void UpdateMissile(Board &board)											//Updates all missiles on the board
{
	UpdateAlienMissile(board);												//Updates all alien missile velocities
	UpdateShipMissile(board);												//Updates all ship missile velocities
	std::vector<Bullet> VectorBullets=board.GetVectorBullets();
			
	for (int i=0;i<VectorBullets.size();i++)
	{
		if(VectorBullets.at(i).GetTypeAI() == true)
		{
			VectorBullets.at(i).SetXPos(VectorBullets.at(i).GetXPos()+VectorBullets.at(i).GetVelX());		//Updates All positions of missiles
			VectorBullets.at(i).SetYPos(VectorBullets.at(i).GetYPos()+VectorBullets.at(i).GetVelY());
		}
	}
	board.SetVectorBullets(VectorBullets); //actual updation of bullets
}