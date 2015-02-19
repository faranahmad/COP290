#ifndef USERFILES_H
#define USERFILES_H

#include <string>
#include <vector>
#include <utility>

class UserFiles
{
	public:
		UserFiles();
	
		std::vector<std::pair<std::string,std::string> > GetPathVector();

		int GetNumberOfFiles();
		std::string GetLocalNth(int);
		std::string GetGlobalNth(int);
		std::pair<std::string,std::string> GetNth(int);

		void UpdateNth(int,std::string, std::string);
		void UpdateNthLocal(int, std::string);
		void UpdateNthGlobal(int, std::string);

		void AddNew(std::string,std::string);
		void AddNewLocal(std::string);
		void AddNewGlobal(std::string);

		void LoadFileDataFromSRC(std::string);
		void DumpFileDataToSRC(std::string);

		void LoadFileDataFromDisc();

	private:
		std::vector<std::pair<std::string,std::string> > PathVector;
};

#endif