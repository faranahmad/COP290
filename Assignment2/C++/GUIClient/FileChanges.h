#ifndef FILECHANGES_H
#define FILECHANGES_H

#include "FileHistory.h"
#include "UserFiles.h"


class FileChanges
{
	public:
		FileChanges();
		FileChanges(std::string, std::string);
		FileChanges(FileHistory,FileHistory);
		FileChanges(FileHistory,FileHistory, UserFiles);

		UserFiles GetFileLinking();
		FileHistory GetClientFiles();
		FileHistory GetServerFiles();

		void SetFileLinking(UserFiles);
		void SetClientFiles(FileHistory);
		void SetServerFiles(FileHistory);

		void LoadFileLinkingClient(std::string);
		void LoadFileLinkingServer(std::string);
		void StoreFileLinkingClient(std::string);
		void StoreFileLinkingServer(std::string);

		void LoadClientHistory(std::string);
		void LoadServerHistory(std::string);

		void StoreClientHistory(std::string);
		void StoreServerHistory(std::string);

		void RefreshClient();

		// std::vector<Instruction> ChangeDetectionGlobal();

		// void SaveInstructionVectorToFile(std::vector<Instruction>, std::string);
		// std::vector<Instruction> LoadInstructionVectorFromFile(std::string);

	private:
		UserFiles FileLinking;	
		FileHistory ClientHistory;
		FileHistory ServerHistory;
};

#endif