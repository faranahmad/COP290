#include "UserBase.h"
#include <iostream>

using namespace std;

int main()
{
	while(true)
	{
		int x;
		cin >> x;
		if (x==0)
		{
			// Add User
			cout <<"Adding User\n";
			string username,pwd;
			cin >> username >> pwd;
			cout <<"Username: " << username <<" pwd: " <<pwd <<"\n";
		}
		else if (x==1)
		{
			// Login
			cout <<"Logging in\n";
			string username,pwd;
			cin >> username >> pwd;	
			cout <<"Username: " << username <<" pwd: " <<pwd <<"\n";
		}
		else if (x==2)
		{
			cout <<"Checking if user exists\n";
			// Check User
			string username;
			cin >> username;	
			cout <<"Username: " <<username <<"\n";
		}
		else if (x==3)
		{
			cout <<"Exit Case";
			// Exit case
		}
	}
}