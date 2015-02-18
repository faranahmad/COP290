#ifndef FILEHISTORY_H
#define FILEHISTORY_H

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <utility>
#include <string>
#include <ctime>
#include <fstream>

struct Instruction
{
	int modification; 
	// 0 is no change,
	// 1 is newer modification client,
	// 2 is newer modification server, 
	// 3 is new client file,
	// 4 is new server file,
	// 5 is delete file on user
	// 6 is remove file from server
	std::string filename;
};

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
		int GetDataTime(); 
		int GetNumberOfFiles();

		void SetDataTime(int);
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
		int TimeOfData;
		std::vector< std::pair<std::string, int> > FileTimeBase;
};


std::vector<Instruction> ChangeDetectionGlobal(FileHistory,FileHistory);
void SaveInstructionVectorToFile(std::vector<Instruction>, std::string);
std::vector<Instruction> LoadInstructionVectorFromFile(std::string);

#endif