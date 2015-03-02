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
	if (ClientServer.find(clf) == ClientServer.end())
	{
		return "";
	}
	else 
	{
		return ClientServer[clf];
	}
}

std::string UserFiles::GetServerFileName(std::string clf)
{
	if (ServerClient.find(clf)==ServerClient.end())
	{
		return "";
	}
	else
	{	
		return ServerClient[clf];
	}
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