#ifndef BOARD_H
#define BOARD_H

#include "Alien.h"
#include "Color.h"
#include "Bullet.h"
#include "Ship.h"
#include <vector>
#include <math.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <algorithm>

float RandomFloat(float,float);

struct Points
{
	float x,y,z;
};


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

		double MaxDistance();
		

		int CheckBulletHitAlien(int); 			// Return id of alien
		int CheckBulletHitShip(int); 			// Return id of ship
		std::vector<int> CheckAlienHitShip(int);

		std::vector<Points> UpdateAllBullets(); 				// Move bullets to next position, Call AI function
												// Check bullet collisions
												// Check bullet out of board
		
		void UpdateAliens(); 					// Call AI function for aliens

		void UpdatePlayerAI();					// Update AI players

		void InsertBullet(Bullet);
		void InsertAlien(Alien);
		void InsertShip(Ship);
		
		std::string GetSummary();

		void MoveNthShip(int,int); //first int id secong int if 0 move to left 1 pe right 2 up 3 down 4 rotate clock 5 rotate anti clock
		void AddRandomShip();
		void AddRandomAlien();
	
		std::string GeneratePlayerPositionInstructions(int); 	// String 1_PlayerID_PlayerName_xpos_ypos_angle
		std::string GeneratePlayerBulletInstructions(std::vector<Bullet>); // String 2_
		std::string GeneratePlayerInstructions(int,std::vector<Bullet>); // 1....... \n 2 ....  \t 2..... t 2... \t \n

		
		std::vector<std::string> SplitString(std::string,char);
		void ApplyInsToShip(std::vector<std::string>,Ship);
		void ApplyInsToBullets(std::string);
		
		void ApplyShipInstructions(std::string,int);
		
		std::string GenerateAllBulletInstructions();

		void ApplySingleBulletInstructions(Bullet,std::string);
		void ApplyAllBulletInstructions(std::string);

		std::string GenerateOnlyPlayerInstructions(int,std::vector<Bullet>);
		std::string GenerateAllInstructions(int,std::vector<Points>);


		std::vector<Points> ApplyInstructions(std::string,int);

		std::string GeneratingCount();

		void ApplyInstruction6(std::string);

		std::string GenerateAliensInformation();
		void ApplySingleAlienInstructions(Alien,std::string);
		void ApplyAllAlienInstructions(std::string information);

		void ApplyPlayerBulletInstructions(std::string);
		void UpdateBulletsWithoutKilling(); 

		std::string GetNthPlayerScore(int);
		// std::string GetStringPoints(std::vector<Points>);
		std::vector<Points> GetVectorPoints(std::string);
		std::string GetStringPoints(std::vector<Points>);

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