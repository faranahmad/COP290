#include "Board.h"

Board::Board()
{

}

Board::Board(double posx,double negx,double posy,double negy)
{
	DimensionPosX = posx;
	DimensionPosY = negx;
	DimensionNegX = posy;
	DimensionNegY = negy;
} 

void Board::SetPosXDimension(double posx)
{
	DimensionPosX = posx;
}

void Board::SetPosYDimension(double posy)
{
	DimensionPosY = posy;
}

void Board::SetNegXDimension(double negx)
{
	DimensionNegX = negx;
}

void Board::SetNegYDimension(double negy)
{
	DimensionNegY = negy;
}

void Board::SetNthBullet(int id,Bullet set_bullet)
{
	VectorBullets.at(id) = set_bullet;
}

void Board::SetNthAlien(int id, Alien set_alien)
{
	VectorAliens.at(id) = set_alien;
}

void Board::SetNthShip(int id, Ship set_ship)
{
	VectorShips.at(id) = set_ship;
}

void Board::SetVectorBullets(std::vector<Bullet> bullet_vector)
{
	VectorBullets = bullet_vector;
}
void Board::SetVectorShips(std::vector<Ship> ship_vector)
{
	VectorShips = ship_vector;
}

void Board::SetVectorAliens(std::vector<Alien> alien_vector)
{
	VectorAliens = alien_vector;
}

std::vector<Bullet> Board::GetVectorBullets()
{
	return VectorBullets;
}

std::vector<Ship> Board::GetVectorShips()
{
	return VectorShips;
}

std::vector<Alien> Board::GetVectorAliens()
{
	return VectorAliens;
}

double Board::GetPosXDimension()
{
	return DimensionPosX;
}

double Board::GetPosYDimension()
{
	return DimensionPosY;
}

double Board::GetNegXDimension()
{
	return DimensionNegX;
}
double Board::GetNegYDimension()
{
	return DimensionNegY;
}

int Board::GetNumberShips()
{
	return VectorShips.size();
}

int Board::GetNumberAliens()
{
	return VectorAliens.size();
}

int Board::GetNumberBullets()
{
	return VectorBullets.size();
}

void Board::RemoveNthAlien(int id)
{
	VectorAliens.erase(VectorAliens.begin() + id);
}

void Board::RemoveNthBullet(int id)
{
	VectorBullets.erase(VectorBullets.begin() + id);
}

void Board::RemoveNthShip(int id)
{
	VectorShips.erase(VectorShips.begin() + id);
}

int Board::CheckBulletHitAlien(int)
{
	//to do
}

int Board::CheckBulletHitShip(int)
{
	//to do
}

void Board::UpdateAllBullets()
{
	//to do 
}

