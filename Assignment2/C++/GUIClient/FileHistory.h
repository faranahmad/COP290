#ifndef FILEHISTORY_H
#define FILEHISTORY_H
 
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <utility>
#include <string>
#include <ctime>
#include <fstream>
// #include "UserFiles.h"



class FileHistory
{
	public:
		FileHistory();
		FileHistory(std::string);

		std::string GetFolder();
		std::vector< std::pair<std::string, int> > GetFileTimeBase();
		int GetDataTime(); 
		int GetNumberOfFiles();
		std::pair<std::string, int> GetNthInfo(int);
		std::string GetNthName(int);
		int GetNthTime(int);

		void SetDataTime(int);
		void SetFolderLocation(std::string);
		void SetFileTimeBase(std::vector< std::pair<std::string, int> >);
		void SetNthInfo(int,std::string, int);
		void SetNthFile(int, std::string);
		void SetNthTime(int, int);

		bool ExistsFile(std::string);

		void LoadFileTimeBase();

		void LoadFromFileBase(std::string);
		void StoreToFileBase(std::string);

		void RemoveFile(std::string);

	private:
		std::string FolderLocation;
		int TimeOfData;
		std::vector< std::pair<std::string, int> > FileTimeBase;
};

std::vector< std::pair<std::string, int> > GetVectorFiles(std::string);
FileHistory GetFilesOnDisc(std::string);

#endif