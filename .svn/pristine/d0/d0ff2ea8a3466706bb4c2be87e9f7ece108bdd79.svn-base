#include "Color.h"

Color::Color()
{
	// Default constructor. Red color
	/**
	 * @brief Constructor for Color
	 * @details Default constructor. Red color
	 * 
	 * @param r red component
	 * @param g green component
	 * @param b blue component	
	 * @return only red color
	 */
	R=1.0;
	G=0.0;
	B=0.0;
}

Color::Color(int r,int g,int b)
{
	// Constructs a color based on user input lying between 0 and 255 
	R=((float) r)/255.0;
	G=((float) g)/255.0;
	B=((float) b)/255.0;
}


float Color::GetR()
{
	// Returns the red component
	return R;
}

float Color::GetG()
{
	// Returns the green component
	return G;
}

float Color::GetB()
{
	// Returns the blue component
	return B;
}


void Color::SetR(int r)
{
	// Sets the red component
	R= ((float) r)/255.0;
}

void Color::SetG(int g)
{
	// Sets the green component
	G=((float) g)/255.0;
}

void Color::SetB(int b)
{
	// Sets the blue component
	B=((float) b)/255.0;
}
void Color::SetRGBFloat(float r,float g,float b)
{
	R = r;
	G = g;
	B = b;
}

void Color::SetRGB(int r,int g,int b)
{
	// Sets the R,G,B components based on input
	R=((float) r)/255.0;
	G=((float) g)/255.0;
	B=((float) b)/255.0;
}
