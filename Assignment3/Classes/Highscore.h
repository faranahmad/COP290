#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <fstream>
#include "Board.h" 

struct ScoreName
{
	std::string Name;
	std::string Score;
};

std::vector<ScoreName> UpdateHighScores(Board &);
// Sorted such that 0 is maximum score
// Make the extern bool true in case of new highscore for this player id
// Restrict the size to 5 entries only

#endif