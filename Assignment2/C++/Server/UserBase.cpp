#include "UserBase.h"
#include <fstream>
#include <iostream>

std::string EncryptDecrypt(std::string InputText)
{
	char key = 'P'; 
    std::string output = InputText;
    
    for (int i = 0; i < InputText.size(); i++)
        output[i] = InputText[i] ^ key;
    
    return output;
}

UserBase::UserBase()
{
	UsersList=std::unordered_map<std::string, std::string> ();
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
	if (CheckUserExists(UserCons))
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
	UsersList[UserCons.GetUserName()]=UserCons.GetPassword();
}

void UserBase::StoreToFile(std::string location)
{
	std::string data="";
	for (auto& x: UsersList) 
	{
    	data += EncryptDecrypt(x.first) + "\n" +  EncryptDecrypt(x.second) + "\n";
	}
	data=data.substr(0,data.size() - 1);
	std::ofstream out(location);
	out << data;
	out.close();
}

void UserBase::LoadFromFile(std::string location)
{
	std::string line1,line2;
	std::ifstream myfile (location);
  	UsersList= std::unordered_map<std::string ,std::string> ();
  	if (myfile.is_open())
  	{
  		//TODO
    	while ( getline (myfile,line1) )
    	{	
    		getline(myfile,line2);
    		UsersList[EncryptDecrypt(line1)]=EncryptDecrypt(line2);
    	}
    	myfile.close();
  	}
}

// int main()
// {
// 	UserBase n1=UserBase();
// 	std::cout<<n1.GetNumberOfUsers()<<"\n";
// 	n1.InsertUser(User("kg","kgpassword"));
// 	std::cout<<n1.GetNumberOfUsers()<<"\n";
// 	n1.LoadFromFile("File.txt");
// 	std::cout <<n1.VerifyUserCredentials(User("faran","kg"))<<"\n";
// 	std::cout <<n1.VerifyUserCredentials(User("faran","soccer"))<<"\n";
// 	n1.InsertUser(User("soccer","prats"));
// 	n1.StoreToFile("File.txt");
// 	std::string s1;
// 	while (1)
// 	{
// 		std::cin >>s1;
// 		std::cout <<"Verifying users : \n" << n1.CheckUserExists(User(s1)) <<"\n";	
// 	}
// 	// n1.StoreToFile("File.txt");
// 	return 0;
// }