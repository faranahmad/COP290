#include "User.h"

User::User()
{
    UserName="";
    Password="";
}

User::User(std::string usname, std::string pwd)
{
    UserName=usname;
    Password=pwd;
}

std::string User::GetUserName()
{
	return UserName;
}

std::string User::GetPassword()
{
	return Password;
}

void User::SetUserName(std::string NewName)
{
	UserName=NewName;
}

void User::SetPassword(std::string NewName)
{
	Password=NewName;
}