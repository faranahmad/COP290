#ifndef USERFILES_H
#define USERFILES_H

#include <vector>
#include <utility>

class UserFiles
{
	public:
		UserFiles();
	
		std::vector<pair<std::string,std::string>> GetPath();
		// std::vector<std::string> GetGlobalPath();

		std::string GetLocalNth(int);
		std::string GetGlobalNth(int);
		pair<std::string,std::string> GetNth(int);

		void UpdateNth(int,std::string, std::string);
		void UpdateNthLocal(int, std::string);
		void UpdateNthGlobal(int, std::string);

		void AddNew(std::string,std::string);

	private:
		std::vector<pair<std::string,std::string>> Path;
		//std::vector<std::string> GlobalPath;
};


#endif