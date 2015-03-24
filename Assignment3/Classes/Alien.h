#ifndef ALIEN_H
#define ALIEN_H

#include <string>
#include "Color.h"

class Alien
{
	public:
		Alien();
		
		float GetXPos();
		float GetYPos();
		float GetAngle();
		Color GetColor();
		int GetLevel();
		int GetLives();
		int GetBullets();
		int GetMissiles();
		int GetType();
		int GetBullets();
		int GetMissiles();

		void SetXPos(float);
		void SetYPos(float);
		void SetAngle(float);
		void SetColor(Color);
		void SetLevel(int);
		void SetLives(int);
		void SetBullets(int);
		void SetMissiles(int);
		void SetType(int);

		std::string GetSummary();

	private:
		float XPos;
		float YPos;
		float Angle;
		Color ColorOfAlien;
		int Level;
		int PresentLives;
		int NumberBullets;
		int NumberMissiles;
		int AlienType;
};

#endif