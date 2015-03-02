#include "FileReceiving.h"
#include <fstream>

FileReceiving::FileReceiving()
{
	SharingList= std::vector<Sharing> ();
}

FileReceiving::FileReceiving(std::vector<Sharing> v)
{
	SharingList = v;
}

std::vector<Sharing> FileReceiving::GetSharingList()
{
	return SharingList;
}

int FileReceiving::GetNumberOfSharing()
{
	return SharingList.size();
}

Sharing FileReceiving::GetNthSharing(int n)
{
	if (n<SharingList.size())
	{
		return SharingList[n];
	}
}

void FileReceiving::SetSharingList(std::vector<Sharing> v)
{
	SharingList = v;
}

void FileReceiving::SetNthSharing(Sharing s, int n)
{
	SharingList[n] = s;
}

void FileReceiving::AddNewSharing(Sharing news)
{
	SharingList.push_back(news);
}

void FileReceiving::AddNewLocation(std::string newloc)
{
	Sharing news;
	news.FilePath= newloc;
	news.ShareType=0;
	SharingList.push_back(news);
}

void FileReceiving::AddNewLocationType(std::string newloc,int type)
{
	Sharing news;
	news.FilePath= newloc;
	news.ShareType=type;
	SharingList.push_back(news);
}

void FileReceiving::LoadSharingFromDisk(std::string location)
{
	std::string line1,line2;
	std::ifstream myfile (location);
	SharingList = std::vector<Sharing> ();
	if (myfile.is_open())
	{
	while ( getline (myfile,line1) )
		{	
			getline(myfile,line2);
			Sharing a;
			a.FilePath= line1;
			a.ShareType= std::stoi(line2);
			SharingList.push_back(a);
		}
		myfile.close();
	}
}

void FileReceiving::StoreSharingToDisk(std::string location)
{
	std::string data="";
	for (int i=0; i<SharingList.size() ; i++) 
	{
    	data += SharingList[i].FilePath + "\n" +  std::to_string(SharingList[i].ShareType) + "\n";
	}
	data=data.substr(0,data.size() - 1);
	std::ofstream out(location);
	out << data;
	out.close();
}

bool FileReceiving::CheckIfExists(std::string tocheck)
{
	bool ans1= false;
	for (int i=0; (i<SharingList.size()) && !(ans1) ; i++)
	{
		if (SharingList[i].FilePath == tocheck)
		{
			ans1 = true;
		}
	}
	return ans1;
}

void FileReceiving::InsertNewInDisk(std::string location,Sharing news)
{
	FileReceiving x;
	x.LoadSharingFromDisk(location);
	x.AddNewSharing(news);
	x.StoreSharingToDisk(location);
}