#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>

using namespace std;

//#include "Highscore.h"

struct IDScore
{
	int ID;
	int Score;
	string name;
	IDScore() 
	{
		ID=-1;
		name="Nop";
		Score=-1;
	}
};

struct sortclass
{
	bool operator() (IDScore a, IDScore b) { return (a.Score>b.Score);}
} sortobject;




void UpdateHighScores()
{
	// std::string p ="kg";
	// p+="\t"; 
	// p+= "450";
	// std::vector<std::string> answer;
	// answer.push_back(p);
	// answer.push_back(p);
	// answer.push_back(p);
	// answer.push_back(p);
	// answer.push_back(p);

	vector<int> Scores;
	for (int i=0;i<5;i++)
	{
		Scores.push_back(i+2);
	}

	ifstream filin;
	filin.open("highscores.txt");
	string reader;
	int score;
	vector<IDScore> HighScores;
	vector<IDScore> NewHighScores;
	vector<IDScore> Combined;

	while(getline(filin,reader))
	{
		IDScore ThisPlayer; 
		ThisPlayer.name=reader;
		cout<<"name "<<ThisPlayer.name<<endl;
		getline(filin,reader);
		score=atoi(reader.c_str());
		cout<<"score "<<score<<endl;
		ThisPlayer.Score=score;

		HighScores.push_back(ThisPlayer);
		
	}

	filin.close();
	ofstream filout;
	filout.open("highscores.txt");

	for (int i=0;i<HighScores.size();i++)
	{
		Combined.push_back(HighScores[i]);
	}

	for (int i=0;i<NewHighScores.size();i++)
	{
		Combined.push_back(NewHighScores[i]);
	}

	sort (Combined.begin(),Combined.end(),sortobject);

	for (int i=0; (i<Combined.size()) && (i<5); i++)
	{
		// string l1 = board.GetNthPlayerScore(i);
		// score=stoi(l1);

		filout<<Combined[i].name<<"\n";
		filout<<Combined[i].Score<<"\n";
		
	}
	


	//return answer;
}

int main()
{
	UpdateHighScores();
	return 0;
}