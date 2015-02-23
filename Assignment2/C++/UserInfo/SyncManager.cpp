#include "SyncManager.h"

bool SyncListContains(SyncList cons, std::string tofind)
{
	bool found=false;
	for (int i=0; (i<cons.ListOfFiles.size()) && !(found) ; i++)
	{
		if (cons.ListOfFiles[i]==tofind)
		{
			found=true;
		}
	}
	return found;
}


SyncManager::SyncManager()
{
	Username="";
	SyncList x;
	x.ListOfFiles = std::vector<std::string> ();
	FilesToSync =x;
	MainFiles=FileChanges();
	ReceivingFiles=FileReceiving();
	GivingFiles = FileSharing();
}

SyncManager::SyncManager(std::string n1)
{
	Username=n1;
	SyncList x;
	x.ListOfFiles = std::vector<std::string> ();
	FilesToSync =x;
	MainFiles=FileChanges("here3/"+n1+"/client/", "here3/"+n1+"/server/");
	ReceivingFiles=FileReceiving();
	GivingFiles = FileSharing();	
}

FileChanges SyncManager::GetMainFiles()
{
	return MainFiles;
}

FileReceiving SyncManager::GetReceivingFiles()
{
	return ReceivingFiles;
}

FileSharing SyncManager::GetGivingFiles()
{
	return GivingFiles;
}

SyncList SyncManager::GetFilesToSync()
{
	return FilesToSync;
}

std::string SyncManager::GetUsername()
{
	return Username;
}

void SyncManager::SetUsername(std::string n)
{
	Username=n;
}

void SyncManager::SetMainFiles(FileChanges Newf)
{
	MainFiles =Newf;
}

void SyncManager::SetReceivingFiles(FileReceiving Recf)
{
	ReceivingFiles = Recf;
}

void SyncManager::SetGivingFiles(FileSharing files)
{
	GivingFiles = files;
}

void SyncManager::SetFilesToSync(SyncList slist)
{
	FilesToSync = slist;
}

void SyncManager::AddFileToSync(std::string nfile)
{
	FilesToSync.ListOfFiles.push_back(nfile);
}

void SyncManager::RemoveFileFromSync(std::string nfile)
{
	std::vector<std::string>::iterator position = std::find(FilesToSync.ListOfFiles.begin(), FilesToSync.ListOfFiles.end(), nfile);
	if (position != FilesToSync.ListOfFiles.end()) // == vector.end() means the element was not found
	{
 	   FilesToSync.ListOfFiles.erase(position);
	}
}

void SyncManager::RefreshClientFolder()
{
	MainFiles.RefreshClient();
}

void SyncManager::LoadSyncList(std::string location)
{
	std::string line1;
	std::ifstream myfile (location);
	FilesToSync.ListOfFiles = std::vector<std::string> ();
	if (myfile.is_open())
	{
		while ( getline (myfile,line1) )
		{	
			FilesToSync.ListOfFiles.push_back(line1);
		}
		myfile.close();
	}
}

void SyncManager::LoadReceiving(std::string location)
{
	ReceivingFiles.LoadSharingFromDisk(location);
}

void SyncManager::LoadGiving(std::string location)
{
	GivingFiles.LoadGivingFromDisk(location);
}

void SyncManager::LoadClServerMap(std::string location)
{
	MainFiles.LoadFileLinkingClient(location);
}

void SyncManager::LoadSeClientMap(std::string location)
{
	MainFiles.LoadFileLinkingServer(location);
}

void SyncManager::LoadClHistory(std::string location)
{
	MainFiles.LoadClientHistory(location);
}

void SyncManager::LoadSeHistory(std::string location)
{
	MainFiles.LoadServerHistory(location);
}

void SyncManager::StoreSyncList(std::string location)
{
	std::string data="";
	for (int i=0; i<FilesToSync.ListOfFiles.size() ; i++) 
	{
		data += FilesToSync.ListOfFiles[i] + "\n";
	}
	data=data.substr(0,data.size() - 1);
	std::ofstream out(location);
	out << data;
	out.close();
}

void SyncManager::StoreReceiving(std::string location)
{
	ReceivingFiles.StoreSharingToDisk(location);
}

void SyncManager::StoreGiving(std::string location)
{
	GivingFiles.StoreGivingToDisk(location);
}

void SyncManager::StoreClServerMap(std::string location)
{
	MainFiles.StoreFileLinkingClient(location);
}

void SyncManager::StoreSeClientMap(std::string location)
{
	MainFiles.StoreFileLinkingServer(location);
}

void SyncManager::StoreClHistory(std::string location)
{
	MainFiles.StoreClientHistory(location);
}

void SyncManager::StoreSeHistory(std::string location)
{
	MainFiles.StoreServerHistory(location);
}

void SyncManager::LoadFromDiskDB(std::string location)
{
	LoadSyncList(location+ "/" + Username+"/synclist.txt");
	LoadReceiving(location+ "/" + Username+"/receiving.txt");
	LoadGiving(location+ "/" + Username+"/giving.txt");
	LoadClServerMap(location+ "/" + Username+"/clserver.txt");
	LoadSeClientMap(location+ "/" + Username+"/seclient.txt");
	LoadClHistory(location+ "/" + Username+"/clhistory.txt");
	LoadSeHistory(location+ "/" + Username+"/sehistory.txt");	
}

void SyncManager::StoreToDiskDB(std::string location)
{
	StoreSyncList(location+ "/" + Username + "/synclist.txt");
	StoreReceiving(location+ +"/"+ Username+"/receiving.txt");
	StoreGiving(location+"/"+ Username+"/giving.txt");
	StoreClServerMap(location+"/"+ Username+"/clserver.txt");
	StoreSeClientMap(location+"/"+ Username+"/seclient.txt");
	StoreClHistory(location+"/"+ Username+"/clhistory.txt");
	StoreSeHistory(location+"/"+ Username+"/sehistory.txt");		
}


std::vector<Instruction> SyncManager::GetSyncingInstructions()
{
	// TODO: SyncList include
	// TODO: Sharing and giving files
	std::vector<Instruction> answer;
	FileHistory CLH = MainFiles.GetClientFiles();
	FileHistory SEH = MainFiles.GetServerFiles();
	UserFiles USF = MainFiles.GetFileLinking();

	int numclient = CLH.GetNumberOfFiles();
	int numserver = SEH.GetNumberOfFiles();

	bool fileClient [numclient];
	bool fileServer [numserver];

	for (int i=0; i<numclient; i++)
	{
		fileClient[i]=false;
	}
	
	for (int i=0; i<numserver; i++)
	{
		fileServer[i]=false;
	}

	for (int i=0; i<numclient; i++)
	{
		std::pair<std::string, int> ClData= CLH.GetNthInfo(i);
		if (USF.CheckExistsClientServer(ClData.first) && (SyncListContains(FilesToSync,ClData.first)))
		{
			std::string servername=USF.GetClientFileName(ClData.first);
			
			for (int j=0; (j<numserver) && !(fileClient[i]) ; j++ )
			{
				if (servername==SEH.GetNthName(j))
				{
					fileClient[i]=true;
					fileServer[j]=true;

					if (CLH.GetNthTime(i) < SEH.GetNthTime(j))
					{
						// newer file is there on cloud
						Instruction a;
						a.modification= 2;
						a.serverfilename=servername;
						a.clientfilename=CLH.GetNthName(i);
						answer.push_back(a);
					}
					else if (CLH.GetNthTime(i) > SEH.GetNthTime(j))
					{
						// newer file on client
						Instruction a;
						a.clientfilename=CLH.GetNthName(i);
						a.serverfilename=servername;
						a.modification=1;
						answer.push_back(a);
					}
					else
					{
						// No changes;
						Instruction a;
						a.modification=0;
						a.clientfilename=CLH.GetNthName(i);
						a.serverfilename=servername;
						answer.push_back(a);
					}


					// File found now detect changes based on time
				}
			}
		}
	}

	for (int i=0; i< numclient; i++)
	{
		if (!fileClient[i])
		{
			if (CLH.GetDataTime() < SEH.GetDataTime())
			{
				// File has to be deleted on client
				// TODO: Remove from sync list
				Instruction a;
				a.modification=5;
				a.clientfilename=CLH.GetNthName(i);
				a.serverfilename=" ";
				answer.push_back(a);
			}
			else
			{
				// File has been created on client
				FilesToSync.ListOfFiles.push_back(CLH.GetNthName(i));
				Instruction a;
				a.modification=3;
				a.clientfilename=CLH.GetNthName(i);
				std::string sname=a.clientfilename;
				int lenpath= CLH.GetFolder().size();
				sname=sname.substr(lenpath);
				a.serverfilename=SEH.GetFolder()+sname;
				answer.push_back(a);	
				USF.AddNew(a.clientfilename, a.serverfilename);
			}
		}
	}

	for (int i=0; i< numserver; i++)
	{
		if (!fileServer[i])
		{
			if (CLH.GetDataTime() < SEH.GetDataTime())
			{
				// File has to be transferred to client
				// TODO: Remove the always addition to sync list
				Instruction a;
				a.modification=4;
				a.serverfilename= SEH.GetNthName(i);
				int lenpath = SEH.GetFolder().size();
				std::string clname = a.serverfilename;
				clname = clname.substr(lenpath);
				a.clientfilename= CLH.GetFolder() + clname ;
				FilesToSync.ListOfFiles.push_back(a.clientfilename);
				answer.push_back(a);
				USF.AddNew(a.clientfilename, a.serverfilename);
			}
			else
			{
				// File has to be deleted from server
				// TODO: Remove from sync list
				Instruction a;
				a.modification= 6;
				a.serverfilename= SEH.GetNthName(i);
				a.clientfilename= "TO delete file on server ";
				answer.push_back(a);
			}
		}
	}
	MainFiles.SetFileLinking(USF);
	MainFiles.SetClientFiles(CLH);
	MainFiles.SetServerFiles(SEH);
	return answer;
}


void SyncManager::SaveInstructionVector(std::vector<Instruction> InstructionVector, std::string location)
{
	std::string data="";
	for (int i=0; i<InstructionVector.size() ; i++)
	{
		data += InstructionVector[i].clientfilename + "\n" + InstructionVector[i].serverfilename +"\n" + std::to_string(InstructionVector[i].modification)+"\n";
	}
	data=data.substr(0,data.size()-1);
	std::ofstream out(location);
	out << data;
	out.close();
}

std::vector<Instruction> SyncManager::LoadInstructionVector(std::string location)
{
	std::string line1,line2,line3;
	std::ifstream myfile (location);
	std::vector<Instruction> answer;
	if (myfile.is_open())
	{
		while ( getline (myfile,line1) )
		{	
    		getline(myfile,line2);
    		getline(myfile,line3);
  			Instruction a;
  			a.clientfilename= line1;
  			a.serverfilename= line2;
  			a.modification= std::stoi(line3);
    		answer.push_back(a);
    	}
    	myfile.close();
  	}	
  	return answer;
}



int main(int argc, char const *argv[])
{
	SyncManager p=SyncManager("kg");
	// p.SetUsername("kg");
	p.StoreToDiskDB("here3");
	p.LoadFromDiskDB("here3");
	p.RefreshClientFolder();
	std::vector<Instruction> v= p.GetSyncingInstructions();
	p.SyncManager::SaveInstructionVector(v,"here2/instruction.txt");
	p.StoreToDiskDB("here2");
	return 0;
}