#ifndef AI_H
#define AI_H
#include "Board.h"
#include <cstdlib>
#include <time.h>

//change these defines for ship and alien for different levels of difficulty
#define theta 45
#define minDistanceforRotation 100	//decides whether an alien should turn or move i.e affects nearEnough
#define minAngleofRotation 15	//should be same as angular velocity shouldnt it??
#define angularvelocity 10 		//turning velocity of ship / alien
#define maximumdistance 100000 //not required 
#define RIGHTANGLE 90		//for moving alien/ship
#define ALIENMISSILE -1
#define POSX 1200 		//import these
#define NEGX 1200
#define POSY 600
#define NEGY 600
#define NOSHIP -1 	
#define ANGLEOFVIEW 45 //view of ship/alien to decide what to do
//import these defines from somewhere

enum WhatItShouldDo  {Move, Turn, FireBullet, FireMissile};

void UpdatePlayerAI(Board &board);
void UpdateAlien(Board &board);
void UpdateMissile(Board &board);
void UpdateAIBoard(Board &board);

void UpdateAlienMissile(Board &board);
void UpdateShipMissile(Board &board);
float DistanceOfAlienFromMissile(Alien &alien, Bullet &actualmissile);
float DistanceOfShipFromMissile(Ship &ship, Bullet &actualmissile);
float DistanceOfShipFromAlien(Ship &ship, Alien &alien);
float DistanceOfAlienFromShip(Alien &alien, Ship &ship);

int ClosestAlienEnemy(std::vector<Alien> &Aliens,int NumberAliens, Bullet &actualmissile, double maxDistance);
int ClosestShipEnemy(std::vector<Ship> &Ships,int NumberShips, Bullet &actualmissile, double maxDistance);
bool ShipInArc(Ship &ship, Bullet &actualmissile);
bool AlienInArc(Alien &alien, Bullet &actualmissile);

float RelativeAngleOfAlienFromShip(Alien& alien,Ship &ship);
float RelativeAngleOfShipFromAlien(Ship &ship,Alien &alien);
float RelativeAngleShiptoMissilePosition(Ship &ship, Bullet &actualmissile);
float RelativeAngleAlientoMissilePosition(Alien &alien, Bullet &actualmissile);
float RelativeAngleShipFromMissile(Ship &ship,Bullet &actualmissile);
float RelativeAngleAlienFromMissile(Alien &alien,Bullet &actualmissile);
void UpdateAlienMissileVelocity(Bullet &actualmissile,Ship &ship);
void UpdateShipMissileVelocity(Bullet &actualmissile,Alien &alien);

std::pair<int,bool> FindNearestShip(Alien &alien, std::vector<Ship> &CurrentShips,bool nearEnough);
std::pair<int,bool> FindNearestAlien(Ship &ship, std::vector<Alien> &CurrentAliens,bool nearEnough);
void MoveAlienInDirectionOfShip(Alien &alien, Ship &ship);
void TurnAlienInDirectionOfShip(Alien &alien, Ship &ship);
void MoveShipInDirectionOfAlien(Ship &ship, Alien &alien);
void TurnShipInDirectionOfAlien(Ship &ship, Alien &alien);

void FireBulletForAlien(Alien &alien, Board &board);
void FireMissileForAlien(Alien &alien, Board &board);

void FireBulletForShip(Ship &ship, Board &board);
void FireMissileForShip(Ship &ship, Board &board);

WhatItShouldDo DecideActionForAlien(Board &board, Alien &alien, bool nearEnough);
WhatItShouldDo DecideActionForShip(Board &board, Ship &ship, bool nearEnough);

bool AlienIsInViewOfShip(Board &board, Ship &ship);
bool ShipIsInViewOfAlien(Board &board, Alien &alien);


#endif
