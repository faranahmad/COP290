#ifndef SHIP_H
#define SHIP_H

#include "Color.h"
#include <string>

class Ship
{
	public:
		Ship();
		Ship(int id);

		float GetXPos();
		float GetYPos();
		float GetAngle();
		Color GetColor();
		int GetLives();
		int GetScore();
		int GetMultiplier();
		int GetKills();
		int GetId();
		int GetNumberBullets();
		int GetNumberMissiles();
		bool GetAIControl();

		void SetXPos(float);
		void SetYPos(float);
		void SetAngle(float);
		void SetColorOfShip(Color);
		void SetColorFloat(float,float,float);
		void SetLives(int);
		void SetScore(int);
		void SetMultiplier(int);
		void SetKills(int);
		void SetId(int);
		void SetNumberBullets(int);
		void SetNumberMissiles(int);
		void SetAIControl(bool);

		void AddLife();
		void ReduceLife();
		void IncrementScore();
		void IncrementMultiplier();
		void ResetMultiplier();
		void AddKills();
		void ResetKills();
		void AddNumberBullets();
		void ResetNumberBullets();
		void AddMissile();
		void ReduceMissile();

		std::string GetSummary();

	private:
		float XPos;
		float YPos;
		float Angle;
		std::string Name;
		Color ColorOfShip;
		int Lives;
		int Score;
		int Multiplier;
		int Kills;
		int Id;
		int NumberBullets;
		int NumberMissiles;
		int AILevel; 				// -1 if human player
};

#endif