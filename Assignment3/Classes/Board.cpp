#include "Board.h"

float RandomFloat(float a, float b) 
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

Board::Board()
{

}

Board::Board(double posx,double negx,double posy,double negy)
{
	DimensionPosX = posx;
	DimensionPosY = posy;
	DimensionNegX = negx;
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

//returns -1 if bullets hits noalien
int Board::CheckBulletHitAlien(int bullet_id)
{
	Bullet bullet_hitting = VectorBullets.at(bullet_id);
	for (int i = 0;i < VectorAliens.size();i++)
	{
		Alien alien_hit = VectorAliens.at(i);
		float xdis = bullet_hitting.GetXPos() - alien_hit.GetXPos();
		float ydis = bullet_hitting.GetYPos() - alien_hit.GetYPos();
		if ((float) sqrt(xdis*xdis + ydis*ydis) < 0.1)
		{
			return i;
		}
	}
	return -1;

}

int Board::CheckBulletHitShip(int id)
{
	Bullet bullet_hitting = VectorBullets.at(id);
	for (int i = 0;i < VectorShips.size();i++)
	{
		Ship ship_hit = VectorShips.at(i);
		float xdis = bullet_hitting.GetXPos() - ship_hit.GetXPos();
		float ydis = bullet_hitting.GetYPos() - ship_hit.GetYPos();
		if ((float) sqrt(xdis*xdis + ydis*ydis) < 0.1)
		{
			return i;
		}
	}
	return -1;
}

void Board::UpdateAllBullets()
{
	int bullet_size = VectorBullets.size();
	for (int i = 0;i < bullet_size ;i++)
	{

	} 
}

void Board::UpdateAliens()
{
	//to do
}

void Board::UpdatePlayerAI()
{
	//to do
}
void Board::UpdateUserPlayer(int id, int type)
{
	//to do 
}

void Board::InsertBullet(Bullet new_bullet)
{
	VectorBullets.push_back(new_bullet);
}

void Board::InsertAlien(Alien new_alien)
{
	VectorAliens.push_back(new_alien);
}

void Board::InsertShip(Ship new_ship)
{
	VectorShips.push_back(new_ship);
}

std::string Board::GetSummary()
{
	std::string get_summary_ship = "";
	std::string get_summary_bullet = "";
	std::string get_summary_alien = "";

	for (int i = 0;i < VectorShips.size();i++)
	{
		get_summary_ship  = get_summary_ship + VectorShips.at(i).GetSummary() + "\t";
	}
	for (int i = 0;i < VectorBullets.size();i++)
	{
		get_summary_ship  = get_summary_bullet + VectorBullets.at(i).GetSummary() + "\t";
	}
	for (int i = 0;i < VectorAliens.size();i++)
	{
		if (i == VectorAliens.size()-1)
		{
			get_summary_ship  = get_summary_bullet + VectorAliens.at(i).GetSummary();
		}
		else
		{
			get_summary_ship  = get_summary_bullet + VectorAliens.at(i).GetSummary() + "\t";	
		}
	}
	return (get_summary_ship + get_summary_bullet + get_summary_alien);
}

void Board::MoveNthShip(int ship_id,int mov_type)
{
	Ship ship_to_move = VectorShips.at(ship_id);
	if(mov_type == 0)
	{
		if(ship_to_move.GetXPos() - 5.0 > -(DimensionNegX))
		{
			ship_to_move.SetXPos(ship_to_move.GetXPos() - 5.0*cos((double) ship_to_move.GetAngle()*PI/180));
			ship_to_move.SetYPos(ship_to_move.GetYPos() - 5.0*sin((double) ship_to_move.GetAngle()*PI/180));			
		}
	}
	else if(mov_type == 1)
	{
		if(ship_to_move.GetXPos() + 5.0 < DimensionPosX)
		{
			ship_to_move.SetXPos(ship_to_move.GetXPos() + 5.0*cos((double) ship_to_move.GetAngle()*PI/180));
			ship_to_move.SetYPos(ship_to_move.GetYPos() + 5.0*sin((double) ship_to_move.GetAngle()*PI/180));
		}
	}
	else if(mov_type == 2)
	{
		if(ship_to_move.GetYPos() + 5.0 < DimensionPosY)
		{
			ship_to_move.SetYPos(ship_to_move.GetYPos() + 5.0*cos((double) ship_to_move.GetAngle()*PI/180));
			ship_to_move.SetXPos(ship_to_move.GetXPos() - 5.0*sin((double) ship_to_move.GetAngle()*PI/180));
		}
	}
	else if(mov_type == 3)
	{
		if(ship_to_move.GetYPos() - 5.0 > -(DimensionNegY))
		{
			ship_to_move.SetYPos(ship_to_move.GetYPos() - 5.0*cos((double) ship_to_move.GetAngle()*PI/180));
			ship_to_move.SetXPos(ship_to_move.GetXPos() + 5.0*sin((double) ship_to_move.GetAngle()*PI/180));
		}
	}
	else if(mov_type == 4)
	{
		ship_to_move.SetAngle(ship_to_move.GetAngle() - 5.0);
		std::cout<<ship_to_move.GetAngle() <<"\n";
	}
	else if(mov_type == 5)
	{
		ship_to_move.SetAngle(ship_to_move.GetAngle() + 5.0);
		std::cout<<ship_to_move.GetAngle() <<"\n";
	}
	VectorShips.at(ship_id) = ship_to_move; 
}
 void Board::AddRandomShip()
{
	Ship random_ship;
	random_ship.SetXPos(RandomFloat(-(DimensionNegX),DimensionPosX));
	random_ship.SetYPos(RandomFloat(-(DimensionNegY),DimensionPosY));
	random_ship.SetColorFloat(rand() % 255,rand() % 255,rand() % 255);
	random_ship.SetAngle(RandomFloat(0.0,360.0));
	VectorShips.push_back(random_ship);
}