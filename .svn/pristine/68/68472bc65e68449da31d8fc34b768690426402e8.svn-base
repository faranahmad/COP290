#ifndef OPAI_H
#define OPAI_H
#include "CompetitiveBoard.h"
#include <cstdlib>
#include <time.h>
#include <limits.h>

//change these defines for ship and alien for different levels of difficulty
#define theta 15
#define minDistanceforRotation 5000000 //important to set this	//decides whether an alien should turn or move i.e affects nearEnough
#define minAngleofRotation 5	//should be same as angular velocity shouldnt it??
#define angularvelocity 5 		//turning velocity of ship / alien
//#define maximumdistance 100000 //not required 
#define RIGHTANGLE 90		//for moving alien/ship
#define ALIENMISSILE -1
extern int POSX;
 		//import these
extern int NEGX;

extern int POSY;
extern int NEGY;
#define NOSHIP -1 	
#define ANGLEOFVIEW 45 //view of ship/alien to decide what to do
//import these defines from somewhere

void OPMoveShipInDirectionOfShip(Ship &ship1, Ship &ship2);
void OPTurnShipInDirectionOfShip(Ship &ship1, Ship &ship2, bool &finished);
void OPUpdateAIBoard(Board &board);
void OPUpdatePlayerAI(Board &board);
void OPUpdateMissile(Board &board);
void OPUpdateShipMissile(Board &board);
float OPRelativeAngleShipFromMissile(Ship &ship,Bullet &actualmissile);

void OPUpdateShipMissileVelocity(Bullet &actualmissile,Ship &ship2);
void OPFireBulletForShip(Ship &ship, Board &board);

std::pair<int,bool> OPFindNearestShip(Ship &ship, std::vector<Ship> &CurrentShips);

float OPDistanceOfShipFromShip(Ship &ship1, Ship &ship2);

float OPRelativeAngleOfShipFromShip(Ship& ship2,Ship &ship1);//returns angles in degrees;

int OPClosestShipEnemy(std::vector<Ship> &Ships,int NumberShips, Bullet &actualmissile, double maxDistance);

bool OPShipInArc(Ship &ship, Bullet &actualmissile);

float OPDistanceOfShipFromMissile(Ship &ship, Bullet &actualmissile);

float OPRelativeAngleShiptoMissilePosition(Ship &ship, Bullet &actualmissile);



#endif