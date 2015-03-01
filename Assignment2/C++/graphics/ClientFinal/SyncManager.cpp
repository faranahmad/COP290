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
	MainFiles=FileChanges("/home/kartikeya/Desktop/DeadDrop/"+n1, "/home/skipper/Desktop/DeadDropServer/"+n1);
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

FileHistory SyncManager::GetCurrentClientHistory()
{
	// TODO:
	// Open folder
	// Files discover kare le ao
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
	std::vector<std::string>::iterator position = std::find(FilesToSync.ListOfFiles.begin(), FilesToSync.ListOfFiles.end(), nfile);
	
	if (position == FilesToSync.ListOfFiles.end())
	{	
		FilesToSync.ListOfFiles.push_back(nfile);
	}
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
	std::cout <<"Loading se history\n";
	MainFiles.LoadServerHistory(location);
}

void SyncManager::StoreSyncList(std::string location)
{
	std::cout <<"Store sync list location: " <<location <<"\n";
	std::string data="";
	for (int i=0; i<FilesToSync.ListOfFiles.size() ; i++) 
	{
		data += FilesToSync.ListOfFiles[i] + "\n";
	}
	data=data.substr(0,data.size() - 1);
	std::ofstream out(location);
	out << data;
	out.close();
	std::cout <<"File stored \n";
	std::cout << data <<"\n";
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
	std::cout <<"Loading db " << location << "\n";
	LoadSyncList(location+ "/" + Username+"/.data/synclist.txt");
	LoadReceiving(location+ "/" + Username+"/.data/receiving.txt");
	LoadGiving(location+ "/" + Username+"/.data/giving.txt");
	std::cout <<"Done giving\n";
	LoadClServerMap(location+ "/" + Username+"/.data/clserver.txt");
	LoadSeClientMap(location+ "/" + Username+"/.data/seclient.txt");
	LoadClHistory(location+ "/" + Username+"/.data/clhistory.txt");
	std::cout <<"Done giving\n";
	LoadSeHistory(location+ "/" + Username + "/.data/sehistory.txt");	
	std::cout <<"Done giving\n";
}

void SyncManager::StoreToDiskDB(std::string location)
{
	std::cout <<"Storing files to disk: " << location <<"\n";
	StoreSyncList( location + "/" + Username + "/.data/synclist.txt");
	StoreReceiving( location + "/" + Username + "/.data/receiving.txt");
	StoreGiving( location +"/" + Username + "/.data/giving.txt" );
	StoreClServerMap( location + "/" + Username + "/.data/clserver.txt");
	StoreSeClientMap( location + "/" + Username + "/.data/seclient.txt");
	StoreClHistory( location + "/" + Username + "/.data/clhistory.txt");
	StoreSeHistory( location + "/" + Username + "/.data/sehistory.txt");		
}

std::string SyncManager::GetClientMappingForFile(std::string serverfilename)
{
	// Gives the server file name for input
	return MainFiles.GetCLMapping(serverfilename);
}

std::string SyncManager::GetServerMappingForFile(std::string serverfilename)
{
	// Gives the client file name for input
	return MainFiles.GetSEMapping(serverfilename);
}


void SyncManager::RemoveFromServerBase(std::string serverfilename)
{
	// Remove from sehistory
	// Remove from clhistory
	MainFiles.RemoveFromServer(serverfilename);
	std::string clientfilename = GetClientMappingForFile(serverfilename);
	MainFiles.RemoveFromClient(clientfilename);
}

void SyncManager::RemoveFromClientBase(std::string clientfilename)
{
	// Remove from sehistory
	// Remove from clhistory
	MainFiles.RemoveFromClient(clientfilename);
	std::string serverfilename = GetServerMappingForFile(clientfilename);
	MainFiles.RemoveFromServer(serverfilename);
}


std::vector<Instruction> SyncManager::GetSyncingInstructions()
{
	// Get current client files in temp storage
	// Reload client db files
	// See for files in sync list which are no longer on disc
	// See for files in sync list which are in disc and changed
	// See for files in sync list which are not changed on disc
	// See for files not in sync list but are in temp storage

	// TODO: Receiving and giving files

	std::vector<Instruction> answer;
	FileHistory CLH = MainFiles.GetClientFiles();
	FileHistory SEH = MainFiles.GetServerFiles();
	UserFiles USF = MainFiles.GetFileLinking();

	FileHistory PresentFiles= GetFilesOnDisc(CLH.GetFolder());
	// CLH = PresentFiles;

	int numclient = CLH.GetNumberOfFiles();
	int numcpresent = PresentFiles.GetNumberOfFiles();
	int numserver = SEH.GetNumberOfFiles();

	bool fileClient [numclient];
	bool filePresent [numcpresent];
	bool fileServer [numserver];

	int ClientPresent [numclient];

	for (int i=0; i<numclient; i++)
	{
		fileClient[i]=false;
		ClientPresent[i]= -1;
	}
	
	for (int i=0; i<numserver; i++)
	{
		fileServer[i]=false;
	}

	for (int i=0; i<numcpresent; i++)
	{
		filePresent[i]=false;
	}

	for (int i=0; i< numclient ; i++)
	{
		std::string ClData = CLH.GetNthName(i);
		for (int j=0; (j<numcpresent) && !(fileClient[i]); j++)
		{
			if (ClData == PresentFiles.GetNthName(j))
			{
				filePresent[j]=true;
				fileClient[i]=true;
				ClientPresent[i]=j;
			}
		}
	}

	for (int i=0; i < numclient ; i++)
	{
		if (fileClient[i])
		{
			// File was there on last sync and now as well
			// If change occured then do work
			int positionlocal=ClientPresent[i];
			// if (SyncListContains(FilesToSync, CLH.GetNthName(i)))
			if (true)
			{
				std::string servername = USF.GetClientFileName(CLH.GetNthName(i)); 
				bool d1=false;
				for (int k=0; (k<numserver); k++)
				{
					if (servername == SEH.GetNthInfo(k).first)
					{
						fileServer[k]=true;
						d1=true;
						if (PresentFiles.GetNthTime(positionlocal) > CLH.GetNthTime(i))
						{
							Instruction a;
							a.modification=3;
							a.data1= CLH.GetNthName(i);
							a.data2= SEH.GetNthName(k);
							answer.push_back(a);
						}
						else
						{
							if (SEH.GetNthTime(k)>PresentFiles.GetNthTime(positionlocal))
							{
								Instruction a;
								a.modification = 2;
								a.data1=PresentFiles.GetNthName(positionlocal);
								a.data2=SEH.GetNthName(k);
								answer.push_back(a);
								CLH.SetNthTime( i , SEH.GetNthTime(k));
							}
						}
					}
				}
				if (!d1)
				{
					Instruction a;
					a.modification = 5;
					a.data1=CLH.GetNthName(i);
					answer.push_back(a);
					CLH.RemoveFile(a.data1);
					// Delete file on local
					// Remove from mappings and history
				}
			}
			else
			{
				// Might cause issue with shared files
				Instruction a;
				a.modification = 5;
				a.data1 = CLH.GetNthName(i);
				answer.push_back(a);
				CLH.RemoveFile(CLH.GetNthName(i));		
			}
		}
		else
		{
			// File was there at last sync but not anymore
			// Delete this file from cloud
			// Remove from db
			// Remove file from synclist
			Instruction a;
			a.modification = 6;
			a.data2 = CLH.GetNthName(i);
			std::string servername = USF.GetClientFileName(CLH.GetNthName(i)); 
			RemoveFileFromSync (CLH.GetNthName(i));
			RemoveFromClientBase(CLH.GetNthName(i));
			CLH.RemoveFile(CLH.GetNthName(i));
			SEH.RemoveFile(servername);
			a.data1 = servername;
			answer.push_back(a);	
		}
	}
	for (int i=0; i < numcpresent ; i++)
	{
		if (!(filePresent[i]))
		{
			// New file has appeared on client
			// Send this to the server
			Instruction a;
			//AddFileToSync(PresentFiles.GetNthName(i));
			a.modification=3;
			a.data1= PresentFiles.GetNthName(i);
			std::string sname=a.data1;
			int lenpath= CLH.GetFolder().size();
			sname=sname.substr(lenpath);
			a.data2=SEH.GetFolder()+sname;
			USF.AddNew(a.data1,a.data2);
			answer.push_back(a);
		}
	}
	for (int i=0; i < numserver ; i++)
	{
		if (!fileServer[i])
		{
			// New file on server
			// Get it to client
			Instruction a;
			a.modification = 2;
			a.data2=SEH.GetNthName(i);
			
			std::string mainpath(getenv("HOME")); 
			std::string foldername=mainpath + "/Desktop/DeadDrop/" + GetUsername()  + "/";
			std::string serverfoldername="/home/skipper/Desktop/DeadDropServer/" + GetUsername() +"/";

			std::string clpath1= foldername + a.data2.substr(serverfoldername.size());
			std::cout <<"NEW CL PATH\n" << clpath1 <<"\n";

			a.data1=clpath1;
			answer.push_back(a);
			CLH.AddFileToHistory(clpath1, SEH.GetNthTime(i));
			AddFileToLinking(a.data1,a.data2);
		}
	}

	// std::vector<Sharing> RecvFiles = ReceivingFiles.GetSharingList();
	// for (int i=0; i<RecvFiles.size(); i++)
	// {
	// 	if (SEH.ExistsFile(RecvFiles[i].FilePath))
	// 	{
	// 		// The file exists on the server history, clh etc.

	// 	}
	// 	else
	// 	{
	// 		// Get the files from server
	// 		// Add to CLH, SEH, CLL, SEL
	// 		std::string serverfname = RecvFiles[i].FilePath;
	// 		unsigned found = serverfname.find_last_of("/");
	// 		std::string clfname = serverfname.substr(found + 1);
	// 		std::string mainpath(getenv("HOME")); 
	// 		std::string filefoldername=mainpath + "/Desktop/DeadDrop/" + Username + "/" + clfname;
	// 		Instruction a;
	// 		a.modification = 2;
	// 		a.data1 = filefoldername;
	// 		a.data2 = serverfname;
	// 		answer.push_back(a);
	// 	}
	// }

	// File in prev sync, File in present, no change in TS, if change in server ts then pull else no change
	// File in prev sync, File in present and newer TS, if change in server ts then decide and give pull/push
	// File not in prev syn, File in present, if there on server then decide and give pull push
	// File 

	// for (int i=0; i<numclient; i++)
	// {
	// 	int PrevAndNow = 0;
	// 	std::pair<std::string, int> ClData= CLH.GetNthInfo(i);
	// 	for (int j=0; (j<numcpresent) && !fileClient[i] ; j++)
	// 	{
	// 		if (PresentFiles.GetNthInfo(j).first==ClData.first)
	// 		{
	// 			fileClient[i]=true;
	// 			// filePresent[j]=true;
	// 			previd=i;
	// 			PrevAndNow = 3;
	// 			// presentid=j;
	// 			j -=1 ;
	// 		}
	// 	}
	// 	if !(fileClient[i])
	// 	{
	// 		PrevAndNow = 2;
	// 	}

	// 	if (PrevAndNow == 3)
	// 	{
	// 		// File there at prev sync and now
	// 		if (SyncListContains(FilesToSync,ClData.first))
	// 		{	
	// 			std::string servername = USF.GetClientFileName(ClData.first); 
	// 			for (int k=0; (k<numserver) && !(filePresent[j]) ; k++)
	// 			{
	// 				if (servername == SEH.GetNthInfo(k).first)
	// 				{
	// 					if (PresentFiles.GetNthTime(j) < SEH.GetNthTime(k))
	// 					{
	// 						// TODO: fix client path
	// 						// newer file is there on cloud
	// 						Instruction a;
	// 						a.modification= 2;
	// 						a.data2=servername;
	// 						a.data1=CLH.GetNthName(i);
	// 						answer.push_back(a);
	// 					}
	// 					else if (PresentFiles.GetNthTime(j) > SEH.GetNthTime(k))
	// 					{
	// 						// TODO: Fix client path
	// 						// newer file on client
	// 						Instruction a;
	// 						a.data1=CLH.GetNthName(i);
	// 						a.data2=servername;
	// 						a.modification=1;
	// 						answer.push_back(a);
	// 					}
	// 					else
	// 					{
	// 						// No changes;
	// 						Instruction a;
	// 						a.modification=0;
	// 						a.data1=CLH.GetNthName(i);
	// 						a.data2=servername;
	// 						answer.push_back(a);
	// 					}
	// 					fileServer[k]=true;
	// 					filePresent[j]=true;
	// 					k -=1 ;
	// 				}
	// 			}
	// 			if !(fileServer[k])
	// 			{
	// 				// Delete file on client
	// 				// TODO: Fix path
	// 				Instruction a;
	// 				a.modification = 5;
	// 				a.data1 = CLH.GetNthName(i);
	// 				a.data2 = "";
	// 				answer.push_back(a);
	// 			}
	// 		}
	// 		else
	// 		{
	// 			// Delete file on client
	// 			// TODO: Fix path
	// 			Instruction a;
	// 			a.modification = 5;
	// 			a.data1 = CLH.GetNthName(i);
	// 			a.data2 = "";
	// 			answer.push_back(a);	
	// 		}
	// 	}
	// 	else if (PrevAndNow==2)
	// 	{
	// 		// File there previously but not now
	// 		if (SyncListContains(FilesToSync,ClData.first))
	// 		{
	// 			std::string servername = USF.GetClientFileName(ClData.first);
					
	// 		}
	// 		else
	// 		{

	// 		}
	// 	}
	// 		else if (PrevAndNow==1)
	// 		{
	// 			// File not there previously but there now

	// 		}

	// 	}
	// 	else if (PrevAndNow == 2)
	// 	{

	// 	}

	// 	if (USF.CheckExistsClientServer(ClData.first) && (SyncListContains(FilesToSync,ClData.first)))
	// 	{
	// 		std::string servername=USF.GetClientFileName(ClData.first);
			
	// 		for (int j=0; (j<numserver) && !(fileClient[i]) ; j++ )
	// 		{
	// 			if (servername==SEH.GetNthName(j))
	// 			{
	// 				fileClient[i]=true;
	// 				fileServer[j]=true;

	// 				if (CLH.GetNthTime(i) < SEH.GetNthTime(j))
	// 				{
	// 					// newer file is there on cloud
	// 					Instruction a;
	// 					a.modification= 2;
	// 					a.data2=servername;
	// 					a.data1=CLH.GetNthName(i);
	// 					answer.push_back(a);
	// 				}
	// 				else if (CLH.GetNthTime(i) > SEH.GetNthTime(j))
	// 				{
	// 					// newer file on client
	// 					Instruction a;
	// 					a.data1=CLH.GetNthName(i);
	// 					a.data2=servername;
	// 					a.modification=1;
	// 					answer.push_back(a);
	// 				}
	// 				else
	// 				{
	// 					// No changes;
	// 					Instruction a;
	// 					a.modification=0;
	// 					a.data1=CLH.GetNthName(i);
	// 					a.data2=servername;
	// 					answer.push_back(a);
	// 				}


	// 				// File found now detect changes based on time
	// 			}
	// 		}
	// 	}
	// }

	// for (int i=0; i< numclient; i++)
	// {
	// 	if (!fileClient[i])
	// 	{
	// 		if (CLH.GetDataTime() < SEH.GetDataTime())
	// 		{
	// 			// File has to be deleted on client
	// 			// TODO: Remove from sync list
	// 			Instruction a;
	// 			a.modification=5;
	// 			a.data1=CLH.GetNthName(i);
	// 			a.data2=" ";
	// 			answer.push_back(a);
	// 		}
	// 		else
	// 		{
	// 			// File has been created on client
	// 			FilesToSync.ListOfFiles.push_back(CLH.GetNthName(i));
	// 			Instruction a;
	// 			a.modification=3;
	// 			a.data1=CLH.GetNthName(i);
	// 			std::string sname=a.data1;
	// 			int lenpath= CLH.GetFolder().size();
	// 			sname=sname.substr(lenpath);
	// 			a.data2=SEH.GetFolder()+sname;
	// 			answer.push_back(a);	
	// 			USF.AddNew(a.data1, a.data2);
	// 		}
	// 	}
	// }

	// for (int i=0; i< numserver; i++)
	// {
	// 	if (!fileServer[i])
	// 	{
	// 		if (CLH.GetDataTime() < SEH.GetDataTime())
	// 		{
	// 			// File has to be transferred to client
	// 			// TODO: Remove the always addition to sync list
	// 			Instruction a;
	// 			a.modification=4;
	// 			a.data2= SEH.GetNthName(i);
	// 			int lenpath = SEH.GetFolder().size();
	// 			std::string clname = a.data2;
	// 			clname = clname.substr(lenpath);
	// 			a.data1= CLH.GetFolder() + clname ;
	// 			FilesToSync.ListOfFiles.push_back(a.data1);
	// 			answer.push_back(a);
	// 			USF.AddNew(a.data1, a.data2);
	// 		}
	// 		else
	// 		{
	// 			// File has to be deleted from server
	// 			// TODO: Remove from sync list
	// 			Instruction a;
	// 			a.modification= 6;
	// 			a.data1= SEH.GetNthName(i);
	// 			a.data2= "TO delete file on server ";
	// 			answer.push_back(a);
	// 		}
	// 	}
	// }
	MainFiles.SetFileLinking(USF);
	MainFiles.SetClientFiles(CLH);
	MainFiles.SetServerFiles(SEH);
	std::string mainpath(getenv("HOME")); 
	std::string foldername=mainpath + "/Desktop/DeadDrop/" + Username  + "/";
	StoreToDiskDB(mainpath+"/Desktop/DeadDrop/");
	return answer;
}


void SyncManager::SaveInstructionVector(std::vector<Instruction> InstructionVector, std::string location)
{
	std::string data="";
	for (int i=0; i<InstructionVector.size() ; i++)
	{
		data += InstructionVector[i].data1 + "\n" + InstructionVector[i].data2 +"\n" + std::to_string(InstructionVector[i].modification)+"\n";
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
  			a.data1= line1;
  			a.data2= line2;
  			a.modification= std::stoi(line3);
    		answer.push_back(a);
    	}
    	myfile.close();
  	}	
  	return answer;
}

void SyncManager::AddFileToLocalFiles(std::string locpath, std::string gpath)
{
	MainFiles.AddFilesToFileChanges(locpath,gpath);
}

void SyncManager::UpdateSyncTimes()
{
	MainFiles.SetTimeChanges(std::time(0));
}

void SyncManager::AddFileToLinking(std::string cl, std::string se)
{
	UserFiles USF = MainFiles.GetFileLinking();
	USF.AddNew(cl,se);
	MainFiles.SetFileLinking(USF);
}

Instruction DoLogin(std::string us,std::string pwd)
{
	Instruction p;
	p.modification=7;
	p.data1=us;
	p.data2=pwd;
	return p;
}

Instruction NewUser(std::string us, std::string pwd)
{
	Instruction p;
	p.modification=8;
	p.data1=us;
	p.data2=pwd;
	return p;
}

Instruction Exit()
{
	Instruction p;
	p.modification=10;
	return p;
}

Instruction UserExists(std::string usname)
{
	Instruction p;
	p.modification=9;
	p.data1=usname;
	p.data2="";
	return p;
}

Instruction GetServerFiles(std::string clpath,std::string sepath)
{
	Instruction p;
	p.modification=11;
	p.data1=clpath;
	p.data2=sepath;
	return p;
}

Instruction TransferServerToClient(std::string clpath,std::string sepath)
{
	Instruction p;
	p.modification=2;
	p.data1=clpath;
	p.data2=sepath;
	return p;
}

Instruction TransferClientToServer(std::string clpath, std::string sepath)
{
	Instruction p;
	p.modification=1;
	p.data1=clpath;
	p.data2=sepath;
	return p;
}

Instruction DeleteFileOnServer(std::string location)
{
	Instruction p;
	p.modification=6;
	p.data1=location;
	p.data2=location;
	return p;	
}

Instruction DeleteFileOnClient(std::string location)
{
	Instruction p;
	p.modification=5;
	p.data1=location;
	p.data2=location;
	return p;	
}

Instruction RefreshServerDB(std::string location)
{
	Instruction p;
	p.modification=12;
	p.data1=location;
	p.data2=location;
	return p;	
}

Instruction DoNothing()
{
	Instruction p;
	p.modification=0;
	p.data1="";
	p.data2="";
	return p;
}

Instruction DoNormalSending(std::string s1, std::string s2)
{
	Instruction p;
	p.modification=14;
	p.data1=s1;
	p.data2=s2;
	return p;	
}

Instruction ChangePasswordIns(std::string usname, std::string opwd, std::string npwd)
{
	Instruction p;
	p.modification=16;
	p.data1=usname;
	p.data2=opwd;
	p.data3=npwd;
	return p;
}

