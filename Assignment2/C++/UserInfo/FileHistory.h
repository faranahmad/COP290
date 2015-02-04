#ifndef FILEHISTORY_H
#define FILEHISTORY_H

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <utility>
#include <string>
#include <ctime>
#include <fstream>

class FileHistory
{
	public:
		FileHistory();
		FileHistory(std::string);

		std::string GetFolder();
		std::vector< std::pair<std::string, int> > GetFileTimeBase();
		std::pair<std::string, int> GetNthInfo(int);
		std::string GetNthName(int);
		int GetNthTime(int);

		void SetFolderLocation(std::string);
		void SetFileTimeBase(std::vector< std::pair<std::string, int> >);
		void SetNthInfo(int,std::string, int);
		void SetNthFile(int, std::string);
		void SetNthTime(int, int);

		void LoadFileTimeBase();

		void LoadFromFileBase(std::string);
		void StoreToFileBase(std::string);

	private:
		std::string FolderLocation;
		std::vector< std::pair<std::string, int> > FileTimeBase;
};

#endif