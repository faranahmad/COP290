#ifndef SYNCMANAGER_H
#define SYNCMANAGER_H

#include "FileSharing.h"
#include "FileReceiving.h"
#include "FileChanges.h"
#include "FileHistory.h"
#include "UserFiles.h"
#include <algorithm>

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
	// 7 is UserLogin 
	// 8 is New user
	// 9 is user exists
	// 10 is exit
	// 11 is GetServerFiles
	std::string clientfilename;
	std::string serverfilename;
};

struct SyncList
{
	std::vector<std::string> ListOfFiles;
};

bool SyncListContains(SyncList, std::string)

class SyncManager
{
	public:
		SyncManager();
		SyncManager(std::string); //Starts for a particular user

		FileChanges GetMainFiles();
		FileReceiving GetReceivingFiles();
		FileSharing GetGivingFiles();
		SyncList GetFilesToSync();
		std::string GetUsername();

		void SetUsername(std::string);
		void SetMainFiles(FileChanges);
		void SetReceivingFiles(FileReceiving);
		void SetGivingFiles(FileSharing);
		void SetFilesToSync(SyncList);

		void AddFileToSync(std::string);
		void RemoveFileFromSync(std::string);

		void RefreshClientFolder();

		void LoadSyncList(std::string);
		void LoadReceiving(std::string);
		void LoadGiving(std::string);
		void LoadClServerMap(std::string);
		void LoadSeClientMap(std::string);
		void LoadClHistory(std::string);
		void LoadSeHistory(std::string);
		
		void StoreSyncList(std::string);
		void StoreReceiving(std::string);
		void StoreGiving(std::string);
		void StoreClServerMap(std::string);
		void StoreSeClientMap(std::string);
		void StoreClHistory(std::string);
		void StoreSeHistory(std::string);

		void LoadFromDiskDB(std::string);
		void StoreToDiskDB(std::string);

		std::vector<Instruction> GetSyncingInstructions();
		void SaveInstructionVector(std::vector<Instruction>, std::string);
		std::vector<Instruction> LoadInstructionVector(std::string);

	private:
		std::string Username;
		SyncList FilesToSync;
		FileChanges MainFiles;
		FileReceiving ReceivingFiles;
		FileSharing GivingFiles;
};

#endif