#include "FileHistory.h"

FileHistory::FileHistory()
{
	FolderLocation="";
	FileTimeBase = std::vector< std::pair<std::string, int> > ();
}

FileHistory::FileHistory(std::string location)
{
	FolderLocation=location;
	FileTimeBase = std::vector< std::pair<std::string, int> > ();
}

std::string FileHistory::GetFolder()
{
	return FolderLocation;
}

std::vector< std::pair< std::string, int> > FileHistory::GetFileTimeBase()
{
	return FileTimeBase;
}

std::pair<std::string, int> FileHistory::GetNthInfo(int n)
{
	if (n<FileTimeBase.size())
	{
		return FileTimeBase[n];
	}
	else
	{
		return std::pair<std::string, int> ("",0);
	}
}

std::string FileHistory::GetNthName(int n)
{
	if (n < FileTimeBase.size())
	{
		return FileTimeBase[n].first;
	}
	else
	{
		return "";
	}
}

int FileHistory::GetNthTime(int n)
{
	if (n < FileTimeBase.size())
	{
		return FileTimeBase[n].second;
	}
	else
	{
		return 0;
	}	
}

void FileHistory::SetFolderLocation(std::string location)
{
	FolderLocation=location;
}

void FileHistory::SetFileTimeBase(std::vector< std::pair< std::string, int> > newvector)
{
	FileTimeBase=newvector;
}

void FileHistory::SetNthInfo(int n,std::string newname, int newtime)
{
	// n < length
	FileTimeBase[n].first=newname;
	FileTimeBase[n].second=newtime;
}

void FileHistory::SetNthFile(int n,std::string s1)
{
	FileTimeBase[n].first=s1;
}

void FileHistory::SetNthTime(int n, int newtime)
{
	FileTimeBase[n].second=newtime;
}

void FileHistory::LoadFileTimeBase()
{
	// TODO
	boost::filesystem::path p (FolderLocation);   // p reads clearer than argv[1] in the following code
	FileTimeBase = std::vector< std::pair<std::string, int> > ();
	if (exists(p))    // does p actually exist?
	{
		std::vector<boost::filesystem::path> v;
        std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), back_inserter(v));
        std::sort(v.begin(), v.end());
        for (int i=0; i<v.size() ; i++ )
        // for (std::vector<boost::filesystem::path>::const_iterator it (v.begin()); it != v.end(); ++it)
        {
        	FileTimeBase.push_back(std::pair<std::string, int> (v[i].string(), boost::filesystem::last_write_time( v[i] )));
        	// cout << "   " << *it << '\n';
        }
    }
}

void FileHistory::LoadFromFileBase(std::string location)
{
	// TODO File DNE
	std::string line1,line2;
	std::ifstream myfile (location);
  	FileTimeBase = std::vector< std::pair<std::string, int> > ();
  	if (myfile.is_open())
  	{
  		//TODO
  		getline (myfile, line1);
  		FolderLocation= line1;
    	while ( getline (myfile,line1) )
    	{	
    		getline(myfile,line2);
    		FileTimeBase.push_back(std::pair<std::string, int> (line1,std::stoi(line2)));
    	}
    	myfile.close();
  	}
}

void FileHistory::StoreToFileBase(std::string location)
{
	std::string data="";
	data = FolderLocation +"\n";
	for (int i=0; i<FileTimeBase.size() ; i++)
	{
		data += FileTimeBase[i].first +"\n"+std::to_string(FileTimeBase[i].second)+"\n";
	}
	data=data.substr(0,data.size()-1);
	std::ofstream out(location);
	out << data;
	out.close();
}

int main()
{
	FileHistory x=FileHistory("here/");
	x.LoadFileTimeBase();
	x.StoreToFileBase("datadump.txt");
	x= FileHistory("yo/");
	x.LoadFromFileBase("datadump.txt");
	x.StoreToFileBase("datadump2.txt");
	return 0;
}