#ifndef SYNCMANAGER_H
#define SYNCMANAGER_H

#include "FileSharing.h"
#include "FileReceiving.h"
#include "FileChanges.h"
#include "FileHistory.h"
#include "UserFiles.h"

struct SyncList
{
	std::vector<std::string> ListOfFiles;
};

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

	private:
		std::string Username;
		SyncList FilesToSync;
		FileChanges MainFiles;
		FileReceiving ReceivingFiles;
		FileSharing GivingFiles;
};

#endif