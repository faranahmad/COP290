#include "Color.h"

Color::Color()
{
	R=255;
	G=0;
	B=0;
}

Color::Color(int r,int g,int b)
{
	R=r;
	G=g;
	B=b;
}


int Color::GetR()
{
	return R;
}

int Color::GetG()
{
	return G;
}

int Color::GetB()
{
	return B;
}

void Color::SetR(int r)
{
	R=r;
}

void Color::SetG(int g)
{
	G=g;
}

void Color::SetB(int b)
{
	B=b;
}

void Color::SetRGB(int r,int g,int b)
{
	R=r;
	G=g;
	B=b;
}

// std::vector<Color> GoodColors;

// GoodColors.push_back(Color());