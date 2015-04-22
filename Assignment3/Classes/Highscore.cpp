#include "Highscore.h"

extern bool NewHighScore;
extern int ID;

// void UpdateHighScores(Board &board)
// { 
// 	ifstream filin;
// 	filin.open("highscores.txt");
// 	string reader;
// 	int score;
// 	vector<int> HighScores;
// 	vector<int> NewHighScores;

// 	while(!filin.eof())
// 	{
// 		filin>>reader;
// 		filin>>reader;
// 		score=std::stoi(reader);
// 		HighScores.push_back(score);
// 	}

// 	filin.close();
// 	ofstream filout;
// 	filout.open("highscores.txt");

// 	for (int i=0; i<board.GetNumberShips(); i++)
// 	{
// 		std::string l1 = board.GetNthPlayerScore(i);
// 		score=std::stoi(l1);
// 		if (i<HighScores.size())
// 		{
// 			if (score>HighScores[i])
// 				NewHighScores=score;
// 			else 
// 				NewHighScores=HighScores[i];
// 		}		
// 		else
// 		{
// 			NewHighScores=score;
// 		}
		
// 	}
// 	for (int i=0;i<NewHighScores.size();i++)
// 	{
// 		filout<<board.GetNthPlayerName(i)<<"\n";
// 		filout<<NewHighScores[i]<<"\n";
// 	}

// }