#ifndef FILERECEIVING_H
#define FILERECEIVING_H

#include <vector> 
#include <string>

struct Sharing
{
	std::string FilePath;
	int ShareType;
	// 0 is Read and Write
	// 1 is Read Only
};

class FileReceiving
{
	public:
		FileReceiving();
		FileReceiving(std::vector<Sharing>);

		std::vector<Sharing> GetSharingList();
		int GetNumberOfSharing();
		Sharing GetNthSharing(int);

		void SetSharingList(std::vector<Sharing>);
		void SetNthSharing(Sharing, int);

		void AddNewSharing(Sharing);
		void AddNewLocation(std::string);
		void AddNewLocationType(std::string, int);

		void LoadSharingFromDisk(std::string);
		void StoreSharingToDisk(std::string);

		bool CheckIfExists(std::string);

		void InsertNewInDisk(std::string,Sharing);

	private:
		std::vector<Sharing> SharingList;
};

#endif