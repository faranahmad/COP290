#ifndef FILESHARING_H
#define FILESHARING_H

#include <string>
#include <vector>

struct SharingGiver
{
	std::string FilePath;
	std::string UserName;
	int Permissions;
	// 0 is Read and Write
	// 1 is Write Only
};

class FileSharing
{
	public:
		FileSharing();
		FileSharing(std::vector<SharingGiver>);

		std::vector<SharingGiver> GetGivingList();
		int GetNumberofGiving();
		SharingGiver GetNthGiving(int);

		void SetGivingList(std::vector<SharingGiver>);
		void SetNthGiving(SharingGiver, int);

		void AddNewGiving(SharingGiver);
		void AddNewGivingLocation(std::string,std::string);
		void AddNewGivingLocationType(std::string,std::string, int);

		void LoadGivingFromDisk(std::string);
		void StoreGivingToDisk(std::string);

		void InsertNewGivingInDisk(std::string,SharingGiver);

	private:
		std::vector<SharingGiver> GivingList;
};


#endif