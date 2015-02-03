#include "UserFiles.h"

UserFiles::UserFiles()
{
	PathVector = std::vector<pair<std::string,std::string>>;
}

std::vector<pair<std::string,std::string>> UserFiles::GetPathVector()
{
	return PathVector;
}

int UserFiles::GetNumberOfFiles()
{
	return PathVector.size()
}

std::string UserFiles::GetLocalNth(int n)
{
	if (n<)
}
