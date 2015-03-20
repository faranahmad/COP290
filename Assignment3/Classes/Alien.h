#ifndef ALIEN_H
#define ALIEN_H

#include <string>
#include "Color.h"

class Alien
{
	public:
		Alien();
		
		// TODO FARAN

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
};

#endif