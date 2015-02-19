#include "UserFiles.h"
#include <fstream>

UserFiles::UserFiles()
{
	PathVector = std::vector<std::pair<std::string,std::string> > ();
}

std::vector<std::pair<std::string,std::string> > UserFiles::GetPathVector()
{
	return PathVector;
}

int UserFiles::GetNumberOfFiles()
{
	return PathVector.size();
}

std::string UserFiles::GetLocalNth(int n)
{
	if (n<PathVector.size())
	{
		return PathVector[n].first;
	}
	else
	{
		return "";
	}
}

std::string UserFiles::GetGlobalNth(int n)
{
	if (n<PathVector.size())
	{
		return PathVector[n].second;
	}
	else
	{
		return "";
	}
}

std::pair<std::string, std::string> UserFiles::GetNth(int n)
{
	if (n<PathVector.size())
	{
		return PathVector[n];
	}
	else
	{
		return std::pair<std::string,std::string> ("","");
	}
}

void UserFiles::UpdateNth(int n, std::string localnew, std::string globalnew)
{
	if (n<PathVector.size())
	{
		PathVector[n]=std::pair<std::string,std::string> (localnew,globalnew);
	}
}

void UserFiles::UpdateNthLocal(int n, std::string localnew)
{
	if (n<PathVector.size())
	{
		PathVector[n].first=localnew;
	}
}

void UserFiles::UpdateNthGlobal(int n, std::string globalnew)
{
	if (n<PathVector.size())
	{
		PathVector[n].second=globalnew;
	}
}

void UserFiles::AddNew(std::string localnew,std::string globalnew)
{
	PathVector.push_back(std::pair<std::string, std::string> (localnew,globalnew));
}

void UserFiles::AddNewLocal(std::string localnew)
{
	PathVector.push_back(std::pair<std::string, std::string> (localnew,""));
}

void UserFiles::AddNewGlobal(std::string globalnew)
{
	PathVector.push_back(std::pair<std::string, std::string> ("",globalnew));
}

void UserFiles::DumpFileDataToSRC(std::string src)
{
	// TODO: Check for file existance
	std::string data="";
	for (int i=0; i<PathVector.size() ; i++) 
	{
    	data += PathVector[i].first + "\n" + PathVector[i].second + "\n";
	}
	data=data.substr(0,data.size() - 1);
	const char * c = src.c_str();
	std::ofstream out(c);
	out << data;
	out.close();
}

void UserFiles::LoadFileDataFromSRC(std::string src)
{
	// TODO: Check for file existance
	std::string line1,line2;
	const char * c = src.c_str();
	std::ifstream myfile (c);
  	PathVector =std::vector<std::pair<std::string, std::string> > ();
  	if (myfile.is_open())
  	{
    	while ( getline (myfile,line1) )
    	{	
    		getline(myfile,line2);
    		PathVector.push_back(std::pair<std::string, std::string > (line1,line2));
    	}
    	myfile.close();
  	}
}

void UserFiles::LoadFileDataFromDisc()
{
	// TODO KG
}