#ifndef BOARD_H
#define BOARD_H

#include "Alien.h"
#include "Color.h"
#include "Bullet.h"
#include "Ship.h"
#include <vector>
#include <string>

class Board
{
	public:
		Board();
		Board(double,double,double,double);

		void SetPosXDimension(double);
		void SetPosYDimension(double);
		void SetNegXDimension(double);
		void SetNegYDimension(double);

		void SetVectorBullets(std::vector<Bullet>);
		void SetVectorShips(std::vector<Ship>);
		void SetVectorAliens(std::vector<Alien>);
		
		void SetNthBullet(int,Bullet);
		void SetNthShip(int,Ship);
		void SetNthAlien(int,Alien);

		std::vector<Bullet> GetVectorBullets();
		std::vector<Ship> GetVectorShips();
		std::vector<Alien> GetVectorAliens();

		double GetPosXDimension();
		double GetPosYDimension();
		double GetNegXDimension();
		double GetNegYDimension();

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

		void InsertBullet(Bullet);
		void InsertAlien(Alien);
		void InsertShip(Ship);
		
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