#ifndef USERBASE_H
#define USERBASE_H

#include "User.h"
#include <unordered_map>

std::string EncryptDecrypt(std::string);

class UserBase
{
	public:
		UserBase();

		int GetNumberOfUsers();
		std::unordered_map<std::string,std::string> GetUsersList();
		
		void SetUsersLists(std::unordered_map<std::string, std::string>);

		bool VerifyUserCredentials(User);
		bool CheckUserExists(User);

		void InsertUser(User);

		void StoreToFile(std::string);
		void LoadFromFile(std::string);
	
	private:
		std::unordered_map<std::string, std::string> UsersList;
};


#endif