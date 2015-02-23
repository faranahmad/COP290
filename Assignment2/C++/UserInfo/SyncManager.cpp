#include "SyncManager.h"
#include <iostream>
#include <cstring>      
#include <sys/socket.h>     
#include <netdb.h>      
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
// #include <sys/SSL_writefile.h>
#include <fcntl.h>
#include <vector>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem.hpp>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define SIZE 10000
#define BUFFSIZE 10000000

int sockID;
SSL* ssl;
struct addrinfo *host_info_list; 

// Soccer part

SSL_CTX* InitSSL(void)
{ 
    SSL_load_error_strings();   /* Bring in and register error messages */
    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_library_init();
    SSL_CTX* ctx = SSL_CTX_new(SSLv3_client_method());   /* Create new context */
    if ( ctx == NULL )
    {
        exit(0);
    }
    return ctx;
}

void ShowCerts(SSL* ssl)
{   X509 *cert;
    char *line;
 
    cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
    if ( cert != NULL )
    {
        std::cout<<"Server certificates:\n";
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        std::cout<<"Subject: "<<line<<std::endl;
        free(line);       /* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        std::cout<<"Issuer: "<<line<<std::endl;
        free(line);       /* free the malloc'ed string */
        X509_free(cert);     /* free the malloc'ed certificate copy */
    }
    else
        std::cout<<"No certificates.\n";
}


std::string toStr(char* arr)  //Convert array of characters to string
{
    std::string ans="";
    for(int i=0;i<strlen(arr)&&arr[i]!='\0';i++)
    {
        ans+=arr[i];
    }
    return ans;
}

std::string FileName(std::string filename)
{
    std::string ans="";
    for(int i=filename.size()-1;i>=0;i--)
    {
        if(filename[i]!='/')
            ans=filename[i]+ans;
        else
            break;
    }
    return ans;
}

char* ToArr(std::string str)  //Convert string to array of character
{
    char* ans=new char[str.size()];
    for(int i=0;i<str.size();i++)
    {
        ans[i]=str[i];
    }
    return ans;
}

int ExecuteInstruction(Instruction ins)
{
    // 0 is no change,
    // 1 is newer modification client,
    // 2 is newer modification server, 
    // 3 is new client file, 
    // 4 is new server file,
    // 5 is delete file on user
    // 6 is remove file from server
    // 7 is UserLogin 
    // 8 is New user
    // 9 is user exists
    // 10 is exit
    // 11 is GetServerFiles
    std::string temp;
    int bytes_recieved;
    int bytes_sent;
    if(ins.modification==3)
        ins.modification=1;
    if(ins.modification==4)
        ins.modification=2;

    char num[2];
    sprintf(num,"%lld",(long long)ins.modification);
    bytes_sent=SSL_write(ssl, num,2);
    switch(ins.modification)
    {
        case 0:
            {
                // #ignore
                return 1;
            }
        case 8: // Add user
            {
                std::cout<<"Username\n";
                temp=ins.data1;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp.size());
                char* msg1=ToArr(temp);
                std::cout<<temp.size()<<"   "<<strlen(msg1)<<std::endl;
                bytes_sent=SSL_write(ssl, size1,20);
                bytes_sent=SSL_write(ssl,msg1,temp.size());
                std::cout<<"Password\n";
                temp=ins.data2;
                char size2[20];
                sprintf(size2,"%lld",(long long)temp.size());
                char* msg2=ToArr(temp);
                bytes_sent=SSL_write(ssl, size2,20);
                bytes_sent=SSL_write(ssl,msg2,temp.size());
                std::cout<<"User Successfully added!\n";
                return 1;
            }
        case 7: // Login
            {
                std::cout<<"Username\n";
                temp=ins.data1;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp.size());
                char* msg1=ToArr(temp);
                bytes_sent=SSL_write(ssl, size1,20);
                bytes_sent=SSL_write(ssl,msg1,temp.size());
                std::cout<<"Password\n";
                temp=ins.data2;
                char size2[20];
                sprintf(size2,"%lld",(long long)temp.size());
                char* msg2=ToArr(temp);
                bytes_sent=SSL_write(ssl, size2,20);
                bytes_sent=SSL_write(ssl,msg2,temp.size());
                char msg3[1];
                bytes_recieved=SSL_read(ssl,msg3,1);
                msg3[bytes_recieved]='\0';
                if(msg3[0]=='1')
                {
                    std::cout<<"Successfully\n";
                    return 1;
                }
                else
                {
                    std::cout<<"Sorry. Please try again\n";
                    return 0;
                }
            }
        case 9: //User exists
            {
                std::cout<<"Enter Username\n";
                temp=ins.data1;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp.size());
                char* msg1=ToArr(temp);
                bytes_sent=SSL_write(ssl, size1,20);
                bytes_sent=SSL_write(ssl,msg1,temp.size());
                char msg3[1];
                bytes_recieved=SSL_read(ssl,msg3,1);
                msg3[bytes_recieved]='\0';
                if(msg3[0]=='1')
                {
                    std::cout<<"User Exists\n";
                    return 1;
                }
                else
                {
                    std::cout<<"User Does not exist\n";
                    return 0;
                }
            }
        case 1: //client to server
            {
                std::cout<<"Client address\n";
                std::string temp1=ins.data1;
                std::cout<<"Server address\n";
                std::string temp2=ins.data2;

                //filereading
                // TODO : Read files in chunks
                std::ifstream ifs(temp1, std::ios::binary|std::ios::ate);
                std::ifstream::pos_type pos = ifs.tellg();
                std::vector<char>  ans(pos);
                ifs.seekg(0, std::ios::beg);
                ifs.read(&ans[0], pos);
                ifs.close();

                char msg[4];
                char size1[20];
                sprintf(size1,"%lld",(long long)temp2.size());
                bytes_sent=SSL_write(ssl, size1,20);
                char* filepath=ToArr(temp2);
                bytes_sent=SSL_write(ssl,filepath,temp2.size());
                
                char size2[20];
                sprintf(size2,"%lld",(long long)ans.size());
                bytes_sent=SSL_write(ssl, size2,20);

                int dataLen=0;
                int packetCounter=0;
                while(1)
                {
                    char *file2=new char[SIZE];
                    for(int l=0 ;l<SIZE&&dataLen<ans.size();l++,dataLen++)
                    {
                        file2[l]=ans[dataLen];
                    }
                    std::cout<<"SSL_writeing"<<std::endl;
                    SSL_write(ssl, file2,SIZE);
                    packetCounter++;
                    std::cout<<"sent "<<packetCounter<<std::endl;

                    SSL_read(ssl, msg,4);
                    std::cout<<"conf SSL_read\n";
                    if(dataLen==ans.size())
                    {
                        break;
                    }
            
                }
                std::vector<char> tempVector;
                ans.swap(tempVector);
                std::cout<<"file sent"<<std::endl;
                return 1;
            }
        case 2: //server to client
            {
                std::cout<<"Enter client address\n";
                std::string temp1=ins.data1;
                std::cout<<"Enter server address\n";
                std::string temp2=ins.data2;

                char msg[4];
                msg[0]='1';
                char len[20];
                char size1[20];
                sprintf(size1,"%lld",(long long)temp2.size());
                bytes_sent=SSL_write(ssl, size1,20);
                char* filepath=ToArr(temp2);
                bytes_sent=SSL_write(ssl,filepath,temp2.size());
                
                bytes_recieved=SSL_read(ssl, len,20);    
                len[bytes_recieved]='\0';
                long long size=atoll(len);
                std::cout<<size<<std::endl;
                
                std::string data="";
                int packetCounter=0;
                int dataLen=0;

                std::string name=FileName(temp1);
                std::string filepath2=temp1.substr(0,temp1.size()-name.size());
                std::cout<<"Filepath:"<<filepath2<<std::endl;
                std::cout<<"Filename:"<<name<<std::endl;
                boost::filesystem::path dir(filepath2);
                if(!(boost::filesystem::exists(dir)))
                {
                    std::cout<<"Directory Doesn't Exists"<<std::endl;
                    if (boost::filesystem::create_directory(dir))
                        std::cout << "Directory Successfully Created !" << std::endl;
                }
                std::ofstream out(filepath2+name);
                while(1)
                {
                    char *file=new char[SIZE];
                    bytes_recieved=SSL_read(ssl, file,SIZE);
                    std::cout<<bytes_recieved<<std::endl;
                    packetCounter++;
                    std::cout<<"recieved "<<packetCounter<<std::endl;    
                    for(int i=0;i<bytes_recieved && dataLen<size;i++)
                    {
                        data+=file[i];
                        dataLen++;
                    }
                    out << data;
                    data="";
                    SSL_write(ssl, msg,4);
                    std::cout<<"conf sent\n";
                    if(dataLen==size)
                    {
                        std::cout<<"breaking now"<<std::endl;
                        break;
                    }
                }
                out.close();
                std::cout<<"file SSL_read"<<std::endl;
                return 1;
            }
        case 5: //Delete file on user.
            {
                boost::filesystem::wpath file(ins.data1);
                if(boost::filesystem::exists(file))
                    boost::filesystem::remove(file);
                return 1;
            }
        case 6: //Delete file on server.
            {
                std::cout<<"Server address\n";
                std::string temp2=ins.data1;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp2.size());
                bytes_sent=SSL_write(ssl, size1,20);
                char* filepath=ToArr(temp2);
                bytes_sent=SSL_write(ssl,filepath,temp2.size());
                return 1;
            }
        case 10: // quit
            {
                freeaddrinfo(host_info_list);
                close(sockID);
                SSL_free(ssl);
                return 1;
            }
        case 11: // get serverlist
            {
                std::cout<<"Client address\n";
                std::string temp1=ins.data1; // including '/'
                std::cout<<"Server address\n";
                std::string temp2=ins.data2; // including '/'
                std::string temp3=temp1;

                char msg[4];
                char len[20];
                char size1[20];
                sprintf(size1,"%lld",(long long)temp2.size());
                bytes_sent=SSL_write(ssl, size1,20);
                char* filepath=ToArr(temp2);
                bytes_sent=SSL_write(ssl,filepath,temp2.size());

                int fileCount=0;
                while(fileCount<3)
                {
                    bytes_recieved=SSL_read(ssl, len,20);    
                    len[bytes_recieved]='\0';
                    long long size=atoll(len);
                    std::cout<<size<<std::endl;
                    
                    std::string data="";
                    int packetCounter=0;
                    int dataLen=0;
                    switch(fileCount)
                    {

                        case 0:
                            {
                                temp1=(temp3+"receiving.txt");
                                break;
                            }
                        case 1:
                            {
                                temp1=(temp3+"giving.txt");
                                break;
                            }
                        case 2:
                            {
                                temp1=(temp3+"sehistory.txt");
                                break;
                            }
                        default:
                            {
                                break;
                            }   
                    }

                    std::string name=FileName(temp1);
                    std::string filepath2=temp1.substr(0,temp1.size()-name.size());
                    std::cout<<"Filepath:"<<filepath2<<std::endl;
                    std::cout<<"Filename:"<<name<<std::endl;
                    boost::filesystem::path dir(filepath2);
                    if(!(boost::filesystem::exists(dir)))
                    {
                        std::cout<<"Directory Doesn't Exists"<<std::endl;
                        if (boost::filesystem::create_directory(dir))
                            std::cout << "Directory Successfully Created !" << std::endl;
                    }
                    std::ofstream out(filepath2+name);
                    while(1)
                    {
                        char *file=new char[SIZE];
                        bytes_recieved=SSL_read(ssl, file,SIZE);
                        std::cout<<bytes_recieved<<std::endl;
                        packetCounter++;
                        std::cout<<"recieved "<<packetCounter<<std::endl;    
                        for(int i=0;i<bytes_recieved && dataLen<size;i++)
                        {
                            data+=file[i];
                            dataLen++;
                        }
                        out << data;
                        data="";
                        SSL_write(ssl, msg,4);
                        std::cout<<"conf sent\n";
                        if(dataLen==size)
                        {
                            std::cout<<"breaking now"<<std::endl;
                            break;
                        }
                    }
                    out.close();
                    std::cout<<"file SSL_read"<<std::endl;
                    fileCount++;
                }

            }
        default:
            {
                return 0;
            }
    }
    
}



// KG part


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
	// TODO: Consider current files on client
	// TODO: Receiving and giving files
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
						a.data2=servername;
						a.data1=CLH.GetNthName(i);
						answer.push_back(a);
					}
					else if (CLH.GetNthTime(i) > SEH.GetNthTime(j))
					{
						// newer file on client
						Instruction a;
						a.data1=CLH.GetNthName(i);
						a.data2=servername;
						a.modification=1;
						answer.push_back(a);
					}
					else
					{
						// No changes;
						Instruction a;
						a.modification=0;
						a.data1=CLH.GetNthName(i);
						a.data2=servername;
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
				a.data1=CLH.GetNthName(i);
				a.data2=" ";
				answer.push_back(a);
			}
			else
			{
				// File has been created on client
				FilesToSync.ListOfFiles.push_back(CLH.GetNthName(i));
				Instruction a;
				a.modification=3;
				a.data1=CLH.GetNthName(i);
				std::string sname=a.data1;
				int lenpath= CLH.GetFolder().size();
				sname=sname.substr(lenpath);
				a.data2=SEH.GetFolder()+sname;
				answer.push_back(a);	
				USF.AddNew(a.data1, a.data2);
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
				a.data2= SEH.GetNthName(i);
				int lenpath = SEH.GetFolder().size();
				std::string clname = a.data2;
				clname = clname.substr(lenpath);
				a.data1= CLH.GetFolder() + clname ;
				FilesToSync.ListOfFiles.push_back(a.data1);
				answer.push_back(a);
				USF.AddNew(a.data1, a.data2);
			}
			else
			{
				// File has to be deleted from server
				// TODO: Remove from sync list
				Instruction a;
				a.modification= 6;
				a.data1= SEH.GetNthName(i);
				a.data2= "TO delete file on server ";
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
	p.modification=1;
	p.data1=clpath;
	p.data2=sepath;
	return p;
}

Instruction TransferClientToServer(std::string clpath, std::string sepath)
{
	Instruction p;
	p.modification=2;
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

Instruction DoNothing()
{
	Instruction p;
	p.modification=0;
	p.data1="";
	p.data2="";
	return p;
}




int main(int argc, char const *argv[])
{
	if(argc<3)
	{
		std::cout<<"Error. Usage : ./tclient ip portnumber\n";
	}
	else
	{
	    SSL_CTX *ctx=InitSSL();
	    // SSL *ssl;

	    int status;                      // Contains the status of the server
	    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
	    // struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
	    struct sockaddr_in server;
	    int sock;
	    memset(&host_info, 0, sizeof host_info);

    	host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    	host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

	    status = getaddrinfo(argv[1], argv[2], &host_info, &host_info_list);
	    if (status != 0)  
    	    std::cout << "Getaddrinfo error" << gai_strerror(status) ;

    // int sockID ;                        // The socket descripter
   	 	sockID = socket(host_info_list->ai_family, host_info_list->ai_socktype,host_info_list->ai_protocol);
    	if (sockID == -1)  
        	std::cout << "Socket error " ;

    	int buffs = BUFFSIZE;
    	setsockopt(sockID, SOL_SOCKET, SO_RCVBUF, &buffs, sizeof(buffs));
    	std::cout << "Connecting..."  << std::endl;
    	status = connect(sockID, host_info_list->ai_addr, host_info_list->ai_addrlen);
    	if (status == -1)  
    	    std::cout << "Connection error!\n"; 
    	else 
    		std::cout<<"Connected\n";
   
    	uint32_t htonl(uint32_t hostlong);


    // bool quit =false;

	    ssl = SSL_new(ctx);      /* create new SSL connection state */
	    SSL_set_fd(ssl, sockID); 
	
	    if ( SSL_connect(ssl) <0 )   /* perform the connection */
	        ERR_print_errors_fp(stderr);
	    else
	    {
			std::cout << "Connected with ____ encryption " << SSL_get_cipher(ssl) <<"\n";
	        ShowCerts(ssl);        /* get any certs */
	        SSL_set_connect_state(ssl); 
	
			std::string usinp,uspwd;
			std::cin >> usinp;
			std::cin >> uspwd;
			Instruction newus=NewUser(usinp,uspwd);
			int k=ExecuteInstruction(newus);
			std::cout<<k<<"\n";
			ExecuteInstruction(Exit());
		}
			// SyncManager p=SyncManager("kg");
			// // p.SetUsername("kg");
			// p.StoreToDiskDB("here3");
			// p.LoadFromDiskDB("here3");
			// p.RefreshClientFolder();
			// std::vector<Instruction> v= p.GetSyncingInstructions();
			// p.SyncManager::SaveInstructionVector(v,"here2/instruction.txt");
		// p.StoreToDiskDB("here2");
	}
	return 0;
}