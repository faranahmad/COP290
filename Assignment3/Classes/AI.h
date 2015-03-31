#include "Board.h"
#include <cstdlib>
#include <time.h>

class AI
{
	void UpdatePlayerAI(Board &board);
	void UpdateAlien(Board &board);
	void UpdateMissile(Board &board,int);
	void UpdateAIBoard(Board &board);

	void UpdateAlienMissile(Board &board, int missile);
	void UpdateShipMissile(Board &board, int missile);

	float Distance(Alien &alien, Bullet &actualmissile);
	float Distance(Ship &ship, Bullet &actualmissile);
	float Distance(Ship &ship, Alien &alien);

	int ClosestAlienEnemy(std::vector<Alien> &Aliens,int NumberAliens, Bullet &actualmissile);
	int ClosestShipEnemy(std::vector<Ship> &Ships,int NumberShips, Bullet &actualmissile);

	bool InArc(Alien &alien, Bullet &actualmissile);
	bool InArc(Ship &ship, Bullet &actualmissile);

	

	float relativeAngle(Alien &alien,Bullet &actualmissile);
	float relativeAngle(Ship &ship,Bullet &actualmissile);
	float relativeAngle(Ship &ship,Alien &alien);
	float relativeAngle(Alien& alien,Ship &ship);

	void UpdateVelocity(Bullet &actualmissile,Ship &ship);
	void UpdateVelocity(Bullet &actualmissile,Alien &alien);
	
	
	int FindNearestAlien(Ship &ship, std::vector<Alien> &CurrentAliens,bool nearEnough);
	int FindNearestShip(Alien &alien, std::vector<Ship> &CurrentShips,bool nearEnough);

	void MoveInDirectionOf(Ship &ship, Alien &alien);
	void MoveInDirectionOf(Alien &alien, Ship &ship);

	void TurnInDirectionOf(Ship &ship, Alien &alien);
	void TurnInDirectionOf(Alien &alien, Ship &ship);
	
	
	



};