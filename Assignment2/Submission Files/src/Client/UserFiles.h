#ifndef USERFILES_H
#define USERFILES_H

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

class UserFiles
{
	public:
		UserFiles();
	
		std::unordered_map<std::string,std::string> GetClientServerLink();
		std::unordered_map<std::string,std::string> GetServerClientLink();
		int GetNumberOfFilesClient();
		int GetNumberOfFilesServer();

		bool CheckExistsClientServer(std::string);
		bool CheckExistsServerClient(std::string);

		std::string GetClientFileName(std::string);
		std::string GetServerFileName(std::string);

		void UpdateClientServer(std::string, std::string);
		void UpdateServerClient(std::string, std::string);

		void AddNew(std::string,std::string);
		void AddNewClientServer(std::string,std::string);
		void AddNewServerClient(std::string,std::string);
 
		void LoadClientServerFile(std::string);
		void LoadServerClientFile(std::string);

		void StoreClientServerFile(std::string);
		void StoreServerClientFile(std::string);

	private:

		std::unordered_map<std::string, std::string> ClientServer;
		std::unordered_map<std::string, std::string> ServerClient;
};

#endif