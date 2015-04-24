#ifndef COMPCOMBINED_H
#define COMPCOMBINED_H


#include "CompetitiveBoard.h"
#include "udp.h"
#include <time.h>
#include "OPAI.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <pthread.h>
#include <GL/freeglut.h>
#include <fstream>
#include "Image.h"
#include "CompHighscore.h"

#define NUM_PARTICLES    1000          /* Number of particles  */
#define NUM_DEBRIS       70            /* Number of debris     */

struct Faces
{
	Points p1,p2,p3;
};

struct particleData
{
  float   position[3];
  float   speed[3];
  float   color[3];
};

struct debrisData
{
  float   position[3];
  float   speed[3];
  float   orientation[3];        /* Rotation angles around x, y, and z axes */
  float   orientationSpeed[3];
  float   color[3];
  float   scale[3];
};

struct Expl
{
	particleData 	particles[NUM_PARTICLES];
	debrisData 		debris[NUM_DEBRIS];   
	int         	fuel = 0;                /* "fuel" of the explosion */
	float 			angle = 0.0;             /* camera rotation angle */
};

struct GamePlay
{
	Board PlayerBoard;
	int PlayerId;
	int LastBulletTime;
	int LastMissileTime;
	bool IsActive;
};

struct Graph 
{
    // Struct used for passing data via thread
    int x1;
    char **s1;
};

struct SmokePoint
{
	float 	position[3];
	float 	speed[3];
	float 	color[3];
	float 	radius;
	int 	life;
	float 	initpos[3];
};

struct FirePoint
{
	float position[3];
	float color[4];
	int life;
	float radius;
};


std::vector<Faces> alien1gun;
std::vector<Faces> alien1col;
std::vector<Faces> alien1top;
std::vector<Faces> alien1mid;

std::vector<Faces> alien2gun;
std::vector<Faces> alien2eye;
std::vector<Faces> alien2body;
std::vector<Faces> alien2top;


std::vector<Faces> shipcol;
std::vector<Faces> shipmid;
std::vector<Faces> shipfir;

std::vector<Faces> missiletop;
std::vector<Faces> missilemid;
std::vector<Faces> missileend;

std::vector<Faces> bullettop;
std::vector<Faces> bulletmid;

std::vector<Points> Stars;
std::vector<Expl> Explosions;
std::vector<SmokePoint> SmokePoints;
std::vector<SmokePoint> SmokePointsMissile;
std::vector<FirePoint> FirePoints;
std::queue<Bullet> BulletsToAdd;
int presentf;

bool viewtotake;
extern std::queue<std::string> Instructions;
extern bool playersReady;
extern bool isOffline;
bool Is_SoundExpl;
bool Is_SoundBullet;
float PX,PY,NX,NY;
int POSX,POSY,NEGX,NEGY;
std::string IPAddress;


bool NewHighScore;
int ID;

unsigned char *titleptr;

bool Keys[9];
int SpaceBarFree;

GamePlay newg;

bool GameActive;
bool GameOver;
bool doneonce;
bool SingleMode;
bool MultiMode;
bool OnFrontScreen;
std::vector<std::string> highscorestodisplay;
std::vector<std::string> rankingtodisplay;

std::vector<Faces> loadOBJ(char * path);
void ProcessKeys();
void specialKeys(int key, int x, int y);
void specialKeysUp(int key, int x, int y);
void handleKeypress(unsigned char key, int x, int y);
void handleKeypressUp(unsigned char key, int x, int y);
void mouseclick(int,int,int,int);
void ShowObject(std::vector<Faces> &);
void ShowBullet(Bullet &);
void ShowMissile(Bullet &);
void ShowShip(Ship &);
void ShowBorders();
void ShowTitle();
void ShowIp();
void ShowLives();
void ShowScores();
void ShowAllText();
void ShowBoard(Board &);
Expl newExplosion (float x, float y, float z);
void AddNewExplosion(float x, float y, float z);
void UpdateFireExplosions();
void ShowExplosion(Expl &);
void UpdateAllExplosions();
void ShowSmokePoint(SmokePoint &);
SmokePoint NewSmokePoint(float,float);
void UpdateSmokePoint(SmokePoint &);
void UpdateAllSmokePoints(std::vector<SmokePoint> &);
void DisplaySmokePoints(std::vector<SmokePoint> &);
void DisplayExplosions(std::vector<Expl> &);
void *networkmainhelper(void*);
void display(void);

#endif