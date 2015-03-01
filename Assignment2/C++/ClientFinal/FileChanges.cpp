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

FileHistory FileChanges::GetClientFiles()
{
	return ClientHistory;
}

FileHistory FileChanges::GetServerFiles()
{
	return ServerHistory;
}

void FileChanges::SetFileLinking(UserFiles usfiles)
{
	FileLinking=usfiles;
}


void FileChanges::SetClientFiles(FileHistory x)
{
	ClientHistory = x;
}

void FileChanges::SetServerFiles(FileHistory x)
{
	ServerHistory = x;
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
	std::cout << "Loading serve history\n";
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

std::string FileChanges::GetCLMapping(std::string serverfilename)
{
	return FileLinking.GetClientFileName(serverfilename);
}

std::string FileChanges::GetSEMapping(std::string clientfilename)
{
	return FileLinking.GetServerFileName(clientfilename);
}

void FileChanges::RemoveFromClient(std::string location)
{
	ClientHistory.RemoveFile(location);
}

void FileChanges::RemoveFromServer(std::string location)
{
	ServerHistory.RemoveFile(location);
}

void FileChanges::AddFilesToFileChanges(std::string s1, std::string s2)
{
	int lmtime = boost::filesystem::last_write_time(s1);
	ClientHistory.AddFileToHistory(s1,lmtime);
	ServerHistory.AddFileToHistory(s2,lmtime);
}

void FileChanges::SetTimeChanges(int ntime)
{
	ClientHistory.SetDataTime(ntime);
	ServerHistory.SetDataTime(ntime);
}
