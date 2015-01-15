#include "Color.h"

Color::Color()
{
	R=1.0;
	G=0.0;
	B=0.0;
}

Color::Color(int r,int g,int b)
{
	R=((double) r)/255.0;
	G=((double) g)/255.0;
	B=((double) b)/255.0;
}


double Color::GetR()
{
	return R;
}

double Color::GetG()
{
	return G;
}

double Color::GetB()
{
	return B;
}

void Color::SetR(int r)
{
	R=((double) r)/255.0;
}

void Color::SetG(int g)
{
	G=((double) g)/255.0;
}

void Color::SetB(int b)
{
	B=((double) b)/255.0;
}

void Color::SetRGB(int r,int g,int b)
{
	R=((double) r)/255.0;
	G=((double) g)/255.0;
	B=((double) b)/255.0;
}

// std::vector<Color> GoodColors;

// GoodColors.push_back(Color());