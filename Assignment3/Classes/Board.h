#ifndef BOARD_H
#define BOARD_H

#include "Alien.h"
#include "Color.h"
#include "Bullet.h"
#include "Ship.h"
#include <vector>

class Board
{
	public:
		Board();
		
		// SET GET

		int GetNumberShips();
		int GetNumberAliens();
		int GetNumberBullets();

		Bullet GetNthBullet(int);
		Alien GetNthAlien(int);
		Ship GetNthShip(int);

		void RemoveNthAlien(int);
		void RemoveNthBullet(int);
		void RemoveNthShip(int);

		int CheckBulletHitAlien(int); 			// Return id of alien
		int CheckBulletHitShip(int); 			// Return id of ship

		void UpdateAllBullets(); 				// Move bullets to next position, Call AI function
												// Check bullet collisions
												// Check bullet out of board
		
		void UpdateAliens(); 					// Call AI function for aliens

		void UpdatePlayerAI();					// Update AI players
		void UpdateUserPlayer(int id,int type); // type =1 then move right etc (6 cases)

		std::string GetSummary();

	private:
		std::vector<Ship> VectorShips;
		std::vector<Bullet> VectorBullets;		
		std::vector<Alien> VectorAliens;
		double DimensionPosX;
		double DimensionPosY;
		double DimensionNegX;
		double DimensionNegY;		
};

#endif