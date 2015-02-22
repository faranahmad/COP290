#include "FileChanges.h"

FileChanges::FileChanges()
{
	FileLinking=UserFiles();
	ClientHistory=FileHistory();
	ServerHistory=FileHistory();
}

FileChanges::FileChanges(std::string cl, std::string se)
{
	ClientHistory=FileHistory(cl);
	ServerHistory=FileHistory(se);
}

FileChanges::FileChanges(FileHistory clhist, FileHistory sehist)
{
	ClientHistory=clhist;
	ServerHistory=sehist;
	FileLinking=UserFiles();
}

FileChanges::FileChanges(FileHistory clhist, FileHistory sehist, UserFiles link)
{
	ClientHistory=clhist;
	ServerHistory=sehist;
	FileLinking=link;
}

UserFiles FileChanges::GetFileLinking()
{
	return FileLinking;
}

void FileChanges::SetFileLinking(UserFiles usfiles)
{
	FileLinking=usfiles;
}

void FileChanges::LoadFileLinkingClient(std::string location)
{
	FileLinking.LoadClientServerFile(location);
}

void FileChanges::LoadFileLinkingServer(std::string location)
{
	FileLinking.LoadServerClientFile(location);
}

void FileChanges::StoreFileLinkingClient(std::string location)
{
	FileLinking.StoreClientServerFile(location);
}

void FileChanges::StoreFileLinkingServer(std::string location)
{
	FileLinking.StoreServerClientFile(location);
}

void FileChanges::LoadClientHistory(std::string location)
{
	ClientHistory.LoadFromFileBase(location);
}

void FileChanges::LoadServerHistory(std::string location)
{
	ServerHistory.LoadFromFileBase(location);
}

void FileChanges::StoreClientHistory(std::string location)
{
	ClientHistory.StoreToFileBase(location);
}

void FileChanges::StoreServerHistory(std::string location)
{
	ServerHistory.StoreToFileBase(location);
}

void FileChanges::RefreshClient()
{
	ClientHistory.LoadFileTimeBase();
}


std::vector<Instruction> FileChanges::ChangeDetectionGlobal()
{
	// TODO
	std::vector<Instruction> answer;
	int numclient = ClientHistory.GetNumberOfFiles();
	int numserver = ServerHistory.GetNumberOfFiles();

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
		std::pair<std::string, int> ClData= ClientHistory.GetNthInfo(i);
		if (FileLinking.CheckExistsClientServer(ClData.first))
		{
			std::string servername=FileLinking.GetClientFileName(ClData.first);
			
			for (int j=0; (j<numserver) && !(fileClient[i]) ; j++ )
			{
				if (servername==ServerHistory.GetNthName(j))
				{
					fileClient[i]=true;
					fileServer[j]=true;

					if (ClientHistory.GetNthTime(i) < ServerHistory.GetNthTime(j))
					{
						// newer file is there on cloud
						Instruction a;
						a.modification= 2;
						a.serverfilename=servername;
						a.clientfilename=ClientHistory.GetNthName(i);
						answer.push_back(a);
					}
					else if (ClientHistory.GetNthTime(i) > ServerHistory.GetNthTime(j))
					{
						// newer file on client
						Instruction a;
						a.clientfilename=ClientHistory.GetNthName(i);
						a.serverfilename=servername;
						a.modification=1;
						answer.push_back(a);
					}
					else
					{
						// No changes;
						Instruction a;
						a.modification=0;
						a.clientfilename=ClientHistory.GetNthName(i);
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
			if (ClientHistory.GetDataTime() < ServerHistory.GetDataTime())
			{
				// File has to be deleted on client
				Instruction a;
				a.modification=5;
				a.clientfilename=ClientHistory.GetNthName(i);
				a.serverfilename=" ";
				answer.push_back(a);
			}
			else
			{
				// File has been created on client
				Instruction a;
				a.modification=3;
				a.clientfilename=ClientHistory.GetNthName(i);
				std::string sname=a.clientfilename;
				int lenpath= ClientHistory.GetFolder().size();
				sname=sname.substr(lenpath);
				a.serverfilename=ServerHistory.GetFolder()+sname;
				answer.push_back(a);	
				FileLinking.AddNew(a.clientfilename, a.serverfilename);
			}
		}
	}

	for (int i=0; i< numserver; i++)
	{
		if (!fileServer[i])
		{
			if (ClientHistory.GetDataTime() < ServerHistory.GetDataTime())
			{
				// File has to be transferred to client
				Instruction a;
				a.modification=4;
				a.serverfilename= ServerHistory.GetNthName(i);
				int lenpath = ServerHistory.GetFolder().size();
				std::string clname = a.serverfilename;
				clname = clname.substr(lenpath);
				a.clientfilename= ClientHistory.GetFolder() + clname ;
				answer.push_back(a);
				FileLinking.AddNew(a.clientfilename, a.serverfilename);
			}
			else
			{
				// File has to be deleted from server
				Instruction a;
				a.modification= 6;
				a.serverfilename= ServerHistory.GetNthName(i);
				a.clientfilename= "TO delete file on server ";
				answer.push_back(a);
			}
		}
	}

	return answer;
}

void FileChanges::SaveInstructionVectorToFile(std::vector<Instruction> InstructionVector, std::string location)
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

std::vector<Instruction> FileChanges::LoadInstructionVectorFromFile(std::string location)
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

// int main()
// {
// 	FileHistory x=FileHistory("here/");
// 	FileHistory y=FileHistory("here2/");
// 	x.LoadFileTimeBase();
// 	y.LoadFileTimeBase();
// 	FileChanges p= FileChanges(x,y);
// 	p.LoadFileLinkingClient("ClientServer.txt");
// 	p.LoadFileLinkingServer("ServerClient.txt");
// 	std::vector<Instruction> v= p.ChangeDetectionGlobal();
// 	p.StoreFileLinkingClient("ClientServer.txt");
// 	p.StoreFileLinkingServer("ServerClient.txt");
// 	p.SaveInstructionVectorToFile(v, "instructions.txt");
// 	x.StoreToFileBase("datadump.txt");
// 	y.StoreToFileBase("datadump2.txt");	
// }
