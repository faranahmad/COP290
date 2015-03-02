#include "FileSharing.h"
#include <fstream>

FileSharing::FileSharing()
{
	GivingList= std::vector<SharingGiver> ();
}

FileSharing::FileSharing(std::vector<SharingGiver> v)
{
	GivingList = v;
}

std::vector<SharingGiver> FileSharing::GetGivingList()
{
	return GivingList;
}

int FileSharing::GetNumberofGiving()
{
	return GivingList.size();
}

SharingGiver FileSharing::GetNthGiving(int n)
{
	if (n<GivingList.size())
	{
		return GivingList[n];
	}
}

void FileSharing::SetGivingList(std::vector<SharingGiver> v)
{
	GivingList = v;
}

void FileSharing::SetNthGiving(SharingGiver news, int n)
{
	if (n<GivingList.size())
	{
		GivingList[n]=news;
	}
}

void FileSharing::AddNewGiving(SharingGiver news)
{
	GivingList.push_back(news);
}

void FileSharing::AddNewGivingLocation(std::string filepath, std::string usname)
{
	SharingGiver p;
	p.FilePath=filepath;
	p.UserName=usname;
	p.Permissions=0;
	GivingList.push_back(p);
}

void FileSharing::AddNewGivingLocationType(std::string filepath, std::string usname, int perm)
{
	SharingGiver p;
	p.FilePath=filepath;
	p.UserName=usname;
	p.Permissions=perm;
	GivingList.push_back(p);
}

void FileSharing::LoadGivingFromDisk(std::string location)
{
	std::string line1,line2,line3;
	std::ifstream myfile (location);
	GivingList = std::vector<SharingGiver> ();
	if (myfile.is_open())
	{
	while ( getline (myfile,line1) )
		{	
			getline(myfile,line2);
			getline(myfile,line3);
			SharingGiver a;
			a.FilePath = line1;
			a.UserName = line2;
			a.Permissions = std::stoi(line3);
			GivingList.push_back(a);
		}
		myfile.close();
	}
}

void FileSharing::StoreGivingToDisk(std::string location)
{
	std::string data="";
	for (int i=0; i<GivingList.size() ; i++) 
	{
		data += GivingList[i].FilePath + "\n" + GivingList[i].UserName + "\n"  +  std::to_string(GivingList[i].Permissions) + "\n";
	}
	data=data.substr(0,data.size() - 1);
	std::ofstream out(location);
	out << data;
	out.close();
}

void FileSharing::InsertNewGivingInDisk(std::string location, SharingGiver news)
{
	FileSharing x;
	x.LoadGivingFromDisk(location);
	x.AddNewGiving(news);
	x.StoreGivingToDisk(location);
}
