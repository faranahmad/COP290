#include "Color.h"

Color::Color()
{
	R=1.0;
	G=215.0/255.0;		
	B=0.0;
}

Color::Color(int r,int g,int b)
{
	R=((float) r)/255.0;
	G=((float) g)/255.0;
	B=((float) b)/255.0;
}


float Color::GetR()
{
	return R;
}

float Color::GetG()
{
	return G;
}

float Color::GetB()
{
	return B;
}

void Color::SetR(int r)
{
	R=((float) r)/255.0;
}

void Color::SetG(int g)
{
	G=((float) g)/255.0;
}

void Color::SetB(int b)
{
	B=((float) b)/255.0;
}

void Color::SetRGB(int r,int g,int b)
{
	R=((float) r)/255.0;
	G=((float) g)/255.0;
	B=((float) b)/255.0;
}

// std::vector<Color> GoodColors;

// GoodColors.push_back(Color());