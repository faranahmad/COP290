#include "FileHistory.h"

FileHistory::FileHistory()
{
	FolderLocation="";
	TimeOfData=0;
	FileTimeBase = std::vector< std::pair<std::string, int> > ();
	// FileLinking = UserFiles();
}

FileHistory::FileHistory(std::string location)
{
	TimeOfData=0;
	FolderLocation=location;
	FileTimeBase = std::vector< std::pair<std::string, int> > ();
	// FileLinking = UserFiles();
}

std::string FileHistory::GetFolder()
{
	return FolderLocation;
}

std::vector< std::pair< std::string, int> > FileHistory::GetFileTimeBase()
{
	return FileTimeBase;
}

int FileHistory::GetDataTime()
{
	return TimeOfData;
}

int FileHistory::GetNumberOfFiles()
{
	return FileTimeBase.size();
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

// UserFiles FileHistory::GetFileLinking()
// {
// 	return FileLinking;
// }

void FileHistory::SetDataTime(int newtime)
{
	TimeOfData=newtime;
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

// void FileHistory::SetFileLinking(UserFiles newdb)
// {
// 	FileLinking=newdb;
// }

// void FileHistory::LoadFileLinkingClient(std::string location)
// {
// 	FileLinking.LoadClientServerFile(location);
// }

// void FileHistory::LoadFileLinkingServer(std::string location)
// {
// 	FileLinking.LoadServerClientFile(location);
// }


// void FileHistory::StoreFileLinkingClient(std::string location)
// {
// 	FileLinking.StoreClientServerFile(location);	
// }

// void FileHistory::StoreFileLinkingServer(std::string location)
// {
// 	FileLinking.StoreServerClientFile(location);	
// }

void FileHistory::LoadFileTimeBase()
{
	// Detects the files and their time from the folder
	boost::filesystem::path p (FolderLocation);   // p reads clearer than argv[1] in the following code
	TimeOfData =std::time(0);
	FileTimeBase = GetVectorFiles(FolderLocation);
	// if (exists(p))    // does p actually exist?
	// {
	// 	std::cout <<"folder exists, refreshing\n";
	// 	std::vector<boost::filesystem::path> v;
 //        std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), back_inserter(v));
 //        std::sort(v.begin(), v.end());
 //        for (int i=0; i<v.size() ; i++ )
 //        // for (std::vector<boost::filesystem::path>::const_iterator it (v.begin()); it != v.end(); ++it)
 //        {
 //        	FileTimeBase.push_back(std::pair<std::string, int> (v[i].string(), boost::filesystem::last_write_time( v[i] )));
 //        	// cout << "   " << *it << '\n';
 //        }
 //    }
 //    else
 //    {
 //    	std::cout <<FolderLocation <<"\n";
	//    	std::cout <<"folder dne \n";	 	
 //    }
}

bool FileHistory::ExistsFile(std::string tofine)
{
	bool found1=false;
	for (int i=0; (i<FileTimeBase.size()) && (!found1) ; i++ )
	{
		if (FileTimeBase[i].first == tofine)
		{
			found1=true;
		}
	}
	return found1;
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
  		getline (myfile, line2);
  		TimeOfData=std::stoi(line2);
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
	data = FolderLocation +"\n" + std::to_string(TimeOfData)+"\n";
	for (int i=0; i<FileTimeBase.size() ; i++)
	{
		data += FileTimeBase[i].first +"\n"+std::to_string(FileTimeBase[i].second)+"\n";
	}
	data=data.substr(0,data.size()-1);
	std::ofstream out(location);
	out << data;
	out.close();
}

void FileHistory::RemoveFile(std::string location)
{
	bool done=false;
	for (int i=0; (i< FileTimeBase.size()) && !(done); i++ )	
	{
		if (FileTimeBase[i].first == location)
		{
			done = true;
			FileTimeBase.erase(FileTimeBase.begin() + i);
		}
	}
}

void FileHistory::AddFileToHistory(std::string sadd, int time1)
{
	bool done=false;
	for (int i=0; (i< FileTimeBase.size()) && !(done); i++ )	
	{
		if (FileTimeBase[i].first == sadd)
		{
			done = true;
			FileTimeBase[i].second = time1;
		}
	}
	if (!done)
	{
		FileTimeBase.push_back(std::pair<std::string, int>  (sadd,time1) );
	}
}

std::vector< std::pair<std::string, int> > GetVectorFiles(std::string location)
{
	boost::filesystem::path p (location);
	std::vector< std::pair<std::string, int> > ans= std::vector< std::pair<std::string, int> > ();		
	if (exists(p))    // does p actually exist?
	{
		// std::cout <<"folder exists, loading\n";
		std::vector<boost::filesystem::path> v;
        std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), back_inserter(v));
        std::sort(v.begin(), v.end());
        for (int i=0; i<v.size() ; i++ )
        // for (std::vector<boost::filesystem::path>::const_iterator it (v.begin()); it != v.end(); ++it)
        {
        	if (is_regular_file(v[i]))
        	{
        		if (v[i].string().find("/.data/") != std::string::npos) 
        		{
#ifdef DEBUG
 				   std::cout << "found!" << '\n';
#endif
				}
				else if (v[i].string().find(".temp") != std::string::npos) 
        		{
#ifdef DEBUG
 				   std::cout << "found temp!" << '\n';
#endif
				}
				else if (v[i].string().find("/Shared/") != std::string::npos)
				{
#ifdef DEBUG
					std::cout <<"Shared file\n";
#endif
				}
				else
				{
	        		ans.push_back(std::pair<std::string, int> (v[i].string(), boost::filesystem::last_write_time( v[i] )));
				}
        	}
        	else
        	{
        		std::vector<std::pair<std::string,int > > Merged = ans;
        		std::vector<std::pair<std::string,int > > Subset = GetVectorFiles(v[i].string());
				Merged.insert(Merged.end(), Subset.begin(), Subset.end());
        		ans = Merged;
        	}
        	// cout << "   " << *it << '\n';
        }
    }
    else
    {
    	// std::cout <<FolderLocation <<"\n";
	   	// std::cout <<"folder dne \n";	 	
    }
    return ans;
}


FileHistory GetFilesOnDisc(std::string location)
{
	boost::filesystem::path p (location);   // p reads clearer than argv[1] in the following code
	int TimeOfData =std::time(0);
	std::vector< std::pair<std::string, int> > FileTimeBase = std::vector< std::pair<std::string, int> > ();
	if (exists(p))    // does p actually exist?
	{
		FileTimeBase=GetVectorFiles(location);
	}
    else
    {
    	// std::cout <<FolderLocation <<"\n";
	   	std::cout <<"folder dne \n";	 	
    }
    FileHistory answer= FileHistory(location);
    answer.SetDataTime(TimeOfData);
    answer.SetFileTimeBase(FileTimeBase);
    return answer;
}
