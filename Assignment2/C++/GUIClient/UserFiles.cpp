#include "UserFiles.h"
#include <fstream>

UserFiles::UserFiles()
{
	ClientServer=std::unordered_map<std::string, std::string> ();
	ServerClient=std::unordered_map<std::string, std::string> ();
}

std::unordered_map<std::string,std::string> UserFiles::GetClientServerLink()
{
	return ClientServer;
}

std::unordered_map<std::string,std::string> UserFiles::GetServerClientLink()
{
	return ServerClient;
}

int UserFiles::GetNumberOfFilesClient()
{
	return ClientServer.size();
}


int UserFiles::GetNumberOfFilesServer()
{
	return ServerClient.size();
}


bool UserFiles::CheckExistsClientServer(std::string fname)
{
	if (ClientServer.find(fname) == ClientServer.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool UserFiles::CheckExistsServerClient(std::string fname)
{
	if (ServerClient.find(fname) == ServerClient.end())
	{
		return false;
	}
	else
	{
		return true;
	}	
}

std::string UserFiles::GetClientFileName(std::string clf)
{
	return ClientServer[clf];
}

std::string UserFiles::GetServerFileName(std::string clf)
{
	return ServerClient[clf];
}

void UserFiles::UpdateClientServer(std::string clfile, std::string serfile)
{
	ClientServer[clfile]=serfile;	
}

void UserFiles::UpdateServerClient(std::string serfile, std::string clfile)
{
	ServerClient[serfile]=clfile;	
}

void UserFiles::AddNew(std::string clfile, std::string serfile)
{
	ClientServer[clfile]=serfile;
	ServerClient[serfile]=clfile;
}

void UserFiles::AddNewClientServer(std::string clfile, std::string serfile)
{
	ClientServer[clfile]=serfile;
}

void UserFiles::AddNewServerClient(std::string serfile, std::string clfile)
{
	ServerClient[serfile]=clfile;
}

void UserFiles::LoadClientServerFile(std::string location)
{
	std::string line1,line2;
	std::ifstream myfile (location);
  	ClientServer= std::unordered_map<std::string ,std::string> ();
  	if (myfile.is_open())
  	{
  		//TODO
    	while ( getline (myfile,line1) )
    	{	
    		getline(myfile,line2);
    		ClientServer[line1]=line2;
    	}
    	myfile.close();
  	}
}

void UserFiles::LoadServerClientFile(std::string location)
{
	std::string line1,line2;
	std::ifstream myfile (location);
  	ServerClient= std::unordered_map<std::string ,std::string> ();
  	if (myfile.is_open())
  	{
  		//TODO
    	while ( getline (myfile,line1) )
    	{	
    		getline(myfile,line2);
    		ServerClient[line1]=line2;
    	}
    	myfile.close();
  	}
}

void UserFiles::StoreClientServerFile(std::string location)
{
	std::string data="";
	for (auto& x: ClientServer) 
	{
    	data += x.first + "\n" +  x.second + "\n";
	}
	data=data.substr(0,data.size() - 1);
	std::ofstream out(location);
	out << data;
	out.close();
}

void UserFiles::StoreServerClientFile(std::string location)
{
	std::string data="";
	for (auto& x: ServerClient) 
	{
    	data += x.first + "\n" +  x.second + "\n";
	}
	data=data.substr(0,data.size() - 1);
	std::ofstream out(location);
	out << data;
	out.close();
}

// int main()
// {
// 	UserFiles x= UserFiles();
// 	x.AddNew("pokemon","anupam");
// 	x.AddNew("soccer","prateek");
// 	x.StoreServerClientFile("ServerClient.txt");
// 	x.StoreClientServerFile("ClientServer.txt");
// 	x=UserFiles();
// 	x.LoadClientServerFile("ClientServer.txt");
// 	x.LoadServerClientFile("ServerClient.txt");
// 	x.StoreServerClientFile("ServerClient.txt");
// 	x.StoreClientServerFile("ClientServer.txt");
// }





// std::vector<std::pair<std::string,std::string> > UserFiles::GetPathVector()
// {
// 	return PathVector;
// }

// int UserFiles::GetNumberOfFiles()
// {
// 	return PathVector.size();
// }

// std::string UserFiles::GetLocalNth(int n)
// {
// 	if (n<PathVector.size())
// 	{
// 		return PathVector[n].first;
// 	}
// 	else
// 	{
// 		return "";
// 	}
// }

// std::string UserFiles::GetGlobalNth(int n)
// {
// 	if (n<PathVector.size())
// 	{
// 		return PathVector[n].second;
// 	}
// 	else
// 	{
// 		return "";
// 	}
// }

// std::pair<std::string, std::string> UserFiles::GetNth(int n)
// {
// 	if (n<PathVector.size())
// 	{
// 		return PathVector[n];
// 	}
// 	else
// 	{
// 		return std::pair<std::string,std::string> ("","");
// 	}
// }

// void UserFiles::UpdateNth(int n, std::string localnew, std::string globalnew)
// {
// 	if (n<PathVector.size())
// 	{
// 		PathVector[n]=std::pair<std::string,std::string> (localnew,globalnew);
// 	}
// }

// void UserFiles::UpdateNthLocal(int n, std::string localnew)
// {
// 	if (n<PathVector.size())
// 	{
// 		PathVector[n].first=localnew;
// 	}
// }

// void UserFiles::UpdateNthGlobal(int n, std::string globalnew)
// {
// 	if (n<PathVector.size())
// 	{
// 		PathVector[n].second=globalnew;
// 	}
// }

// void UserFiles::AddNew(std::string localnew,std::string globalnew)
// {
// 	PathVector.push_back(std::pair<std::string, std::string> (localnew,globalnew));
// }

// void UserFiles::AddNewLocal(std::string localnew)
// {
// 	PathVector.push_back(std::pair<std::string, std::string> (localnew,""));
// }

// void UserFiles::AddNewGlobal(std::string globalnew)
// {
// 	PathVector.push_back(std::pair<std::string, std::string> ("",globalnew));
// }

// void UserFiles::DumpFileDataToSRC(std::string src)
// {
// 	// TODO: Check for file existance
// 	std::string data="";
// 	for (int i=0; i<PathVector.size() ; i++) 
// 	{
//     	data += PathVector[i].first + "\n" + PathVector[i].second + "\n";
// 	}
// 	data=data.substr(0,data.size() - 1);
// 	const char * c = src.c_str();
// 	std::ofstream out(c);
// 	out << data;
// 	out.close();
// }

// void UserFiles::LoadFileDataFromSRC(std::string src)
// {
// 	// TODO: Check for file existance
// 	std::string line1,line2;
// 	const char * c = src.c_str();
// 	std::ifstream myfile (c);
//   	PathVector =std::vector<std::pair<std::string, std::string> > ();
//   	if (myfile.is_open())
//   	{
//     	while ( getline (myfile,line1) )
//     	{	
//     		getline(myfile,line2);
//     		PathVector.push_back(std::pair<std::string, std::string > (line1,line2));
//     	}
//     	myfile.close();
//   	}
// }

// void UserFiles::LoadFileDataFromDisc()
// {
// 	// TODO KG
// }