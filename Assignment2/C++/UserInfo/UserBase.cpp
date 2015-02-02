#include "UserBase.h"
#include <fstream>

UserBase::UserBase()
{
	UsersList=std::unordered_map<std::string, std::string> ;
}

int UserBase::GetNumberOfUsers()
{
	return UsersList.size();
}

std::unordered_map<std::string, std::string> UserBase::GetUsersList()
{
	return UsersList;
}

void UserBase::SetUsersLists(std::unordered_map<std::string, std::string> NewList)
{
	UsersList=NewList;
}

bool UserBase::CheckUserExists(User UserCons)
{
	if (UsersList.find(UserCons.GetUserName()) == UsersList.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool UserBase::VerifyUserCredentials(User UserCons)
{
	if (this.CheckUserExists(UserCons))
	{
		return (UsersList[UserCons.GetUserName()]==UserCons.GetPassword()); 
	}	
	else
	{
		return false;
	}
}

void UserBase::InsertUser(User UserCons)
{
	UsersList[UserCons.GetUserName()]=UsersList[UserCons.GetPassword()];
}

void UserBase::StoreToFile(std::string location)
{
	std::string data="";
	for (auto& x: UsersList) 
	{
    	data += x.first + "\n" +  x.second + "\n";
	}
	data=data.substr(0,data.size() - 1);
	std::ofstream out(location);
	out << data;
	out.close();
}

void UserBase::LoadFromFile(std::string location)
{
	std::string line1,line2;
	ifstream myfile (location);
  	UsersList= std::unordered_map<std::string ,std::string>;
  	if (myfile.is_open())
  	{
  		//TODO
    	while ( getline (myfile,line1) )
    	{	
    		getline(myfile,line2);
    		UsersList[line1]=line2;
    	}
    	myfile.close();
  	}
}
