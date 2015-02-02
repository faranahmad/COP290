#ifndef USERBASE_H
#define USERBASE_H

#include "User.h";
#include <vector>;

class UserBase
{
	public:
		UserBase();

		int GetNumberOfUsers();
		std::vector<User> GetUsersList();
		User GetNthUser(int);
		
		void SetUsersLists(std::vector<User>);
		void SetNthUser(int,User);

		bool VerifyUserCredentials(User);
		bool CheckUserExists(User);

		void InsertUser(User);

	
	private:
		std::vector<User> UsersList;
};


#endif USERBASE_H