#include "Highscore.h"



struct IDScore
{
	int ID;
	int Score;
	std::string name;
	IDScore() 
	{
		ID=-2;
		name="Nop";
		Score=-1;
	}
};

struct sortclass
{
	bool operator() (IDScore a, IDScore b) { return (a.Score>b.Score);}
} sortobject;


std::string ToFour1(std::string x)
{
	if(x.length() == 0) 
		return ("0000"); 
	else if(x.length() == 1) 
		return (("000") + x);
	else if(x.length() == 2) 
		return (("00") + x);
	else if(x.length() == 3) 
		return (("0") + x);
	else  
		return x;
}

std::vector<std::string> UpdateHighScores(Board &board) // Updates the high scores
{
	

	Ship CurrentShip = board.GetNthShip(ID);
	std::ifstream filin;
	filin.open("highscores.txt");
	std::string reader;
	int score;
	std::vector<IDScore> HighScores;
	std::vector<IDScore> NewHighScores;
	std::vector<IDScore> Combined;

	while(getline(filin,reader))
	{
		IDScore ThisPlayer; 
		ThisPlayer.name=reader;
		
		getline(filin,reader);
		score=atoi(reader.c_str());
		ThisPlayer.Score=score;

		HighScores.push_back(ThisPlayer);
		
	}

	filin.close();
	std::ofstream filout;
	filout.open("highscores.txt");
	std::vector<Ship> Ships=board.GetVectorShips();
	

	for (int i=0;i<HighScores.size();i++)
	{
		Combined.push_back(HighScores[i]);
	}

	
	for (int i=0;i<Ships.size();i++)
	{
		IDScore CurrentPlayer;
		CurrentPlayer.name= Ships[i].GetName();
		//std::cout<<"name "<<CurrentPlayer.name<<"\n";
		CurrentPlayer.ID =  Ships[i].GetId();
		CurrentPlayer.Score = Ships[i].GetScore();
		Combined.push_back(CurrentPlayer);


	}
	
	

	std::sort (Combined.begin(),Combined.end(),sortobject);

	

	for (int i=0; (i<Combined.size()) && (i<5); i++)
	{
		

		filout<<Combined[i].name<<"\n";
		filout<<Combined[i].Score<<"\n";
		
	}

	

	NewHighScore=false;
	for (int i=0 ; i<5 ; i++)
	{
		if ((Combined[i].ID == ID) && (Combined[i].Score= CurrentShip.GetScore()))
			NewHighScore=true;
	}


	std::vector<std::string> answer;
	std::string  rank1 = "Rank";
	std::string name1 = "Name";
	std::string score1 = "Score";
	answer.push_back(rank1 + "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + score1 + "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + name1);
	for (int i=0;(i<5) && (i<Combined.size());i++)
	{
		answer.push_back(std::to_string(i+1) + "."  + "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + "\t" +"\t" +"\t" + ToFour1(std::to_string(Combined[i].Score)) +  "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + "\t" +  Combined.at(i).name );
	
		

	}

	for (int i=0;(i<5) && (i<Combined.size());i++)
	{
		std::cout<<answer[i]<<"\n";
	}

	return answer;
	


	//return answer;
}


