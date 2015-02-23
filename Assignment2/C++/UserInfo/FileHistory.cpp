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
	        	ans.push_back(std::pair<std::string, int> (v[i].string(), boost::filesystem::last_write_time( v[i] )));
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
	   	std::cout <<"folder dne \n";	 	
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

int main()
{
	FileHistory xyz= GetFilesOnDisc("/home/kartikeya/Desktop/");
	xyz.StoreToFileBase("/home/kartikeya/Desktop/pokemon.txt");
	return 0;
}

// std::vector<Instruction> ChangeDetectionGlobal(FileHistory client,FileHistory server)
// {
// 	std::vector<Instruction> answer;
// 	int numclient, numclienty;

// 	bool fileclient [client.GetNumberOfFiles()];
// 	bool fileserver [client.GetNumberOfFiles()];

// 	for (int i=0; i<client.GetNumberOfFiles(); i++)
// 	{
// 		fileclient[i]=false;
// 	}
	
// 	for (int i=0; i<server.GetNumberOfFiles(); i++)
// 	{
// 		fileserver[i]=false;
// 	}

// 	for (int i=0; i<client.GetNumberOfFiles(); i++)
// 	{
// 		for (int j=0; (j< server.GetNumberOfFiles()) && !(fileclient[i]) ; j++ )
// 		{
// 			if (client.GetNthName(i)==server.GetNthName(j))
// 			{
// 				fileclient[i]=true;
// 				fileserver[j]=true;
// 				if (client.GetNthTime(i) < server.GetNthTime(j))
// 				{
// 					Instruction a;
// 					a.modification = 2;
// 					a.filename = client.GetNthName(i);
// 					answer.push_back(a)	;
// 				}
// 				else if (client.GetNthTime(i) > server.GetNthTime(j))
// 				{
// 					Instruction a;
// 					a.modification = 1;
// 					a.filename = client.GetNthName(i);
// 					answer.push_back(a);
// 				}
// 				else
// 				{
// 					// No change taking place
// 					Instruction a;
// 					a.modification = 0;
// 					a.filename = client.GetNthName(i);
// 					answer.push_back(a);
// 				}
// 			}
// 		}
// 	}

// 	for (int i=0; i<client.GetNumberOfFiles(); i++)
// 	{
// 		if (!fileclient[i])
// 		{
// 			if (client.GetDataTime() < server.GetDataTime())
// 			{
// 				Instruction a;
// 				a.modification = 5;
// 				a.filename = client.GetNthName(i);
// 				answer.push_back(a);
// 			}
// 			else
// 			{
// 				Instruction a;
// 				a.modification = 3;
// 				a.filename = client.GetNthName(i);
// 				answer.push_back(a);	
// 			}		
// 		}
// 	}

	
// 	for (int i=0; i<server.GetNumberOfFiles(); i++)
// 	{
// 		if (!fileserver[i])
// 		{
// 			if (client.GetDataTime() < server.GetDataTime())
// 			{
// 				Instruction a;
// 				a.modification = 4;
// 				a.filename = server.GetNthName(i);
// 				answer.push_back(a);
// 			}		
// 			else
// 			{
// 				Instruction a;
// 				a.modification = 6;
// 				a.filename = server.GetNthName(i);
// 				answer.push_back(a);
// 			}
// 		}
// 	}
// 	return answer;
// }

// void SaveInstructionVectorToFile(std::vector<Instruction> InstructionVector, std::string location)
// {
// 	std::string data="";
// 	for (int i=0; i<InstructionVector.size() ; i++)
// 	{
// 		data += InstructionVector[i].filename +"\n"+std::to_string(InstructionVector[i].modification)+"\n";
// 	}
// 	data=data.substr(0,data.size()-1);
// 	std::ofstream out(location);
// 	out << data;
// 	out.close();
// }


// std::vector<Instruction> LoadInstructionVectorFromFile(std::string location)
// {
// 	// TODO File DNE
// 	std::string line1,line2;
// 	std::ifstream myfile (location);
//   	std::vector<Instruction> answer;
//   	if (myfile.is_open())
//   	{
//   		while ( getline (myfile,line1) )
//     	{	
//     		getline(myfile,line2);
  			
//   			Instruction a;
//   			a.filename= line1;
//   			a.modification= std::stoi(line2);

//     		answer.push_back(a);
//     	}
//     	myfile.close();
//   	}	
//   	return answer;
// }


// int main()
// {
// 	FileHistory x=FileHistory("here/");
// 	FileHistory y=FileHistory("here2/");
// 	x.LoadFileTimeBase();
// 	y.LoadFileTimeBase();
// 	// std::vector<Instruction> v= ChangeDetectionGlobal(x,y);
// 	// SaveInstructionVectorToFile(v, "instructions.txt");
// 	x.StoreToFileBase("datadump.txt");
// 	y.StoreToFileBase("datadump2.txt");

// 	return 0;
// }