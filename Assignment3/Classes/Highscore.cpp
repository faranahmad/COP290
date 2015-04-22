#include "Highscore.h"

/*std::vector<std::string> UpdateHighScores(Board &)
{
	std::string p ="kg";
	p+="\t"; 
	p+= "450";
	std::vector<std::string> answer;
	answer.push_back(p);
	answer.push_back(p);
	answer.push_back(p);
	answer.push_back(p);
	answer.push_back(p);
	return answer;
}*/

//#include "Highscore.h"

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




std::vector<std::string> UpdateHighScores(Board &board)
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
		//std::cout<<"name "<<ThisPlayer.name<<"\n";
		getline(filin,reader);
		score=atoi(reader.c_str());
		//std::cout<<"score "<<score<<"\n";
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

	// for (int i=0;(i<5) && (i<Combined.size());i++)
	// {
	// 	std::cout<<"name1 "<<Combined[i].name<<"\n";
	// }
	for (int i=0;i<Ships.size();i++)
	{
		IDScore CurrentPlayer;
		CurrentPlayer.name= Ships[i].GetName();
		//std::cout<<"name "<<CurrentPlayer.name<<"\n";
		CurrentPlayer.ID =  Ships[i].GetId();
		CurrentPlayer.Score = Ships[i].GetScore();
		Combined.push_back(CurrentPlayer);


	}
	// for (int i=0;(i<5) && (i<Combined.size());i++)
	// {
	// 	std::cout<<"name2 "<<Combined[i].name<<"\n";
	// }
	

	std::sort (Combined.begin(),Combined.end(),sortobject);

	// for (int i=0;(i<5) && (i<Combined.size());i++)
	// {
	// 	std::cout<<"name3 "<<Combined[i].name<<"\n";
	// }

	for (int i=0; (i<Combined.size()) && (i<5); i++)
	{
		// string l1 = board.GetNthPlayerScore(i);
		// score=stoi(l1);

		filout<<Combined[i].name<<"\n";
		filout<<Combined[i].Score<<"\n";
		
	}

	// for (int i=0;(i<5) && (i<Combined.size());i++)
	// {
	// 	std::cout<<"name4 "<<Combined[i].name<<"\n";
	// }

	NewHighScore=false;
	for (int i=0 ; i<5 ; i++)
	{
		if ((Combined[i].ID == ID) && (Combined[i].Score= CurrentShip.GetScore()))
			NewHighScore=true;
	}

	// for (int i=0;(i<5) && (i<Combined.size());i++)
	// {
	// 	std::cout<<"name5 "<<Combined[i].name<<"\n";
	// }

	std::vector<std::string> answer;

	for (int i=0;(i<5) && (i<Combined.size());i++)
	{
		std::string p =Combined[i].name;
		p+="\t"; 
		p+= std::to_string(Combined[i].Score);
		answer.push_back(p);

	}

	for (int i=0;(i<5) && (i<Combined.size());i++)
	{
		std::cout<<answer[i]<<"\n";
	}

	return answer;
	


	//return answer;
}


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