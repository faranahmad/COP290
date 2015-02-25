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
	std::cout <<"Loading db\n";
	LoadSyncList(location+ "/" + Username+"/synclist.txt");
	LoadReceiving(location+ "/" + Username+"/receiving.txt");
	LoadGiving(location+ "/" + Username+"/giving.txt");
	std::cout <<"Done giving\n";
	LoadClServerMap(location+ "/" + Username+"/clserver.txt");
	LoadSeClientMap(location+ "/" + Username+"/seclient.txt");
	LoadClHistory(location+ "/" + Username+"/clhistory.txt");
	std::cout <<"Done giving\n";
	LoadSeHistory(location+ "/" + Username + "/sehistory.txt");	
	std::cout <<"Done giving\n";
}

void SyncManager::StoreToDiskDB(std::string location)
{
	std::cout <<"Storing files to disk: " << location <<"\n";
	StoreSyncList( location + "/" + Username + "/synclist.txt");
	StoreReceiving( location + "/" + Username + "/receiving.txt");
	StoreGiving( location +"/" + Username + "/giving.txt" );
	StoreClServerMap( location + "/" + Username + "/clserver.txt");
	StoreSeClientMap( location + "/" + Username + "/seclient.txt");
	StoreClHistory( location + "/" + Username + "/clhistory.txt");
	StoreSeHistory( location + "/" + Username + "/sehistory.txt");		
}

std::string SyncManager::GetClientMappingForFile(std::string serverfilename)
{
	return MainFiles.GetCLMapping(serverfilename);
}

std::string SyncManager::GetServerMappingForFile(std::string serverfilename)
{
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
			// TODO make cases based on timestamp

		}
		else
		{
			// File was there at last sync but not anymore
			// Delete this file from cloud
			// Remove from db
			// Remove file from synclist

			Instruction a;
			a.modification = 6;
			a.data2 = PresentFiles.GetNthName(i);
			int lenpath = CLH.GetFolder().size();
			std::string sname = a.data2.substr(lenpath);
			a.data1 = SEH.GetFolder() + sname;
			answer.push_back(a);	
			RemoveFileFromSync(a.data2);
		}
	}
	for (int i=0; i < numcpresent ; i++)
	{
		if (!(filePresent[i]))
		{
			// New file has appeared on client
			// Send this to the server
			// TODO: Fix timestamp issue
			FilesToSync.ListOfFiles.push_back(PresentFiles.GetNthName(i));
			Instruction a;
			a.modification=3;
			a.data1= PresentFiles.GetNthName(i);
			std::string sname=a.data1;
			int lenpath= CLH.GetFolder().size();
			sname=sname.substr(lenpath);
			a.data2=SEH.GetFolder()+sname;
			answer.push_back(a);	
			USF.AddNew(a.data1, a.data2);
			answer.push_back(a);
		}
	}

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




// int main(int argc, char const *argv[])
// {
// 	if(argc<3)
// 	{
// 		std::cout<<"Error. Usage : ./tclient ip portnumber\n";
// 	}
// 	else
// 	{
// 	    SSL_CTX *ctx=InitSSL();
// 	    // SSL *ssl;

// 	    int status;                      // Contains the status of the server
// 	    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
// 	    // struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
// 	    struct sockaddr_in server;
// 	    int sock;
// 	    memset(&host_info, 0, sizeof host_info);

//     	host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
//     	host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

// 	    status = getaddrinfo(argv[1], argv[2], &host_info, &host_info_list);
// 	    if (status != 0)  
//     	    std::cout << "Getaddrinfo error" << gai_strerror(status) ;

//     // int sockID ;                        // The socket descripter
//    	 	sockID = socket(host_info_list->ai_family, host_info_list->ai_socktype,host_info_list->ai_protocol);
//     	if (sockID == -1)  
//         	std::cout << "Socket error " ;

//     	int buffs = BUFFSIZE;
//     	setsockopt(sockID, SOL_SOCKET, SO_RCVBUF, &buffs, sizeof(buffs));
//     	std::cout << "Connecting..."  << std::endl;
//     	status = connect(sockID, host_info_list->ai_addr, host_info_list->ai_addrlen);
//     	if (status == -1)  
//     	    std::cout << "Connection error!\n"; 
//     	else 
//     		std::cout<<"Connected\n";
   
//     	uint32_t htonl(uint32_t hostlong);


//     // bool quit =false;

// 	    ssl = SSL_new(ctx);      /* create new SSL connection state */
// 	    SSL_set_fd(ssl, sockID); 
	
// 	    if ( SSL_connect(ssl) <0 )   /* perform the connection */
// 	        ERR_print_errors_fp(stderr);
// 	    else
// 	    {
// 			std::cout << "Connected with ____ encryption " << SSL_get_cipher(ssl) <<"\n";
// 	        ShowCerts(ssl);        /* get any certs */
// 	        SSL_set_connect_state(ssl); 
	
// 			std::string usinp,uspwd;
// 			std::cin >> usinp;
// 			std::cin >> uspwd;
// 			Instruction newus=NewUser(usinp,uspwd);
// 			int k=ExecuteInstruction(newus);
// 			std::cout<<k<<"\n";
// 			ExecuteInstruction(Exit());
// 		}
// 			// SyncManager p=SyncManager("kg");
// 			// // p.SetUsername("kg");
// 			// p.StoreToDiskDB("here3");
// 			// p.LoadFromDiskDB("here3");
// 			// p.RefreshClientFolder();
// 			// std::vector<Instruction> v= p.GetSyncingInstructions();
// 			// p.SyncManager::SaveInstructionVector(v,"here2/instruction.txt");
// 		// p.StoreToDiskDB("here2");
// 	}
// 	return 0;
// }