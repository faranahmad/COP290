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
