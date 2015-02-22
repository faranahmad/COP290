#ifndef FILECHANGES_H
#define FILECHANGES_H

#include "FileHistory.h"
#include "UserFiles.h"
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
	std::string clientfilename;
	std::string serverfilename;
};

class FileChanges
{
	public:
		FileChanges();
		FileChanges(std::string, std::string);
		FileChanges(FileHistory,FileHistory);
		FileChanges(FileHistory,FileHistory, UserFiles);

		UserFiles GetFileLinking();

		void SetFileLinking(UserFiles);

		void LoadFileLinkingClient(std::string);
		void LoadFileLinkingServer(std::string);
		void StoreFileLinkingClient(std::string);
		void StoreFileLinkingServer(std::string);

		void LoadClientHistory(std::string);
		void LoadServerHistory(std::string);

		void StoreClientHistory(std::string);
		void StoreServerHistory(std::string);

		void RefreshClient();

		std::vector<Instruction> ChangeDetectionGlobal();

		void SaveInstructionVectorToFile(std::vector<Instruction>, std::string);
		std::vector<Instruction> LoadInstructionVectorFromFile(std::string);

	private:
		UserFiles FileLinking;	
		FileHistory ClientHistory;
		FileHistory ServerHistory;
};

#endif