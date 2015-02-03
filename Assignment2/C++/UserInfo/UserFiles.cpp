#include "UserFiles.h"

UserFiles::UserFiles()
{
	PathVector = std::vector<std::pair<std::string,std::string>>;
}

std::vector<std::pair<std::string,std::string>> UserFiles::GetPathVector()
{
	return PathVector;
}

int UserFiles::GetNumberOfFiles()
{
	return PathVector.size()
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
		return "":
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