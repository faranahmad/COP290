#ifndef BULLET_H
#define BULLET_H

#include "Color.h"
#include <string>
#include <math.h>
#include <algorithm>

#define PI 3.14159265

class Bullet
{
	public:
		Bullet();

		float GetXPos();
		float GetYPos();
		float GetVelX();
		float GetVelY();
		float GetSpeed();
		Color GetColorOfBullet();
		int GetShipId();
		bool GetTypeAI();
		bool GetTypePlayer();

		void SetXPos(float);
		void SetYPos(float);
		void SetVelX(float);
		void SetVelY(float);
		void SetColorOfBullet(Color);
		void SetColorOfBulletfloat(int,int,int);
		void SetColorFloat(float,float,float);
		void SetShipID(int);
		void SetTypeAI(bool);
		void SetTypePlayer(bool);

		void ResetBulletState();

		std::string GetSummary();

		float GetAngle();  // TODO faran, return angle in degrees.

	private:
		float XPos;
		float YPos;
		float VelX;
		float VelY;
		Color ColorOfBullet;
		int ShipId;				//-1 if from alien
		bool TypeAI;			//true if Missile, AI has to be active on this
		bool TypePlayer;		//true if Player Bullet
};


#endif