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
	// 1 is newer modification client,		data1=clpath data2=sepath
	// 2 is newer modification server, 		data1=clpath data2=sepath
	// 3 is new client file, 				data1=clpath data2=sepath
	// 4 is new server file,				data1=clpath data2=sepath
	// 5 is delete file on user				data1=clpath 
	// 6 is remove file from server 		data1=slpath
	// 7 is UserLogin 						data1=usname data2=passwd
	// 8 is New user						data1=usname data2=passwd
	// 9 is User Exists						data1=usname
	// 10 is Exit
	// 11 is GetServerFiles					data1=clfodlerpath data2=sefolderpath
	// 12 is UpdateServerDiskFiles			data1=sefolderpath
	// 13 is SendServerFiles				data1=clfolderpath data2=sefolderpath
	std::string data1;
	std::string data2;
};

struct SyncList
{
	std::vector<std::string> ListOfFiles;
};

bool SyncListContains(SyncList, std::string);

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

		FileHistory GetCurrentClientHistory();

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


Instruction DoLogin(std::string, std::string);
Instruction NewUser(std::string, std::string);
Instruction Exit();
Instruction UserExists(std::string);
Instruction GetServerFiles(std::string, std::string);
Instruction TransferServerToClient(std::string,std::string);
Instruction TransferClientToServer(std::string,std::string);
Instruction DeleteFileOnServer(std::string);
Instruction DeleteFileOnClient(std::string);
Instruction RefreshServerDB(std::string);
Instruction DoNothing();

struct Client
{
	std::string UserName;
	SyncManager mang;
};

#endif