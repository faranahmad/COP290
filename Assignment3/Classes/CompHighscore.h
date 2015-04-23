#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include "CompetitiveBoard.h" 

extern bool NewHighScore;
extern int ID;

std::vector<std::string> UpdateHighScores(Board &);
// Sorted such that 0 is maximum score
// Make the extern bool true in case of new highscore for this player id
// Restrict the size to 5 entries only
// Return a vector of strings in which each string is a name \t score

#endif