#include "OPAI.h"

void OPMoveAlien(Alien &alien) // Moves the rocks downwards
{
	if (alien.GetLevel()==0)
	{
		alien.SetYPos(alien.GetYPos()-(5));
		alien.SetXPos(alien.GetXPos()+3);
	}
	else if (alien.GetLevel()==1)
	{
		alien.SetYPos(alien.GetYPos()-(10));
		alien.SetXPos(alien.GetXPos() -5);
	}
	else if (alien.GetLevel()==2)
	{
		alien.SetYPos(alien.GetYPos()-(7));
		alien.SetXPos(alien.GetXPos() );
	}
}