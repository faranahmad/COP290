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


std::string ToStr(char* arr)  //Convert array of characters to string
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
                ifs.seekg(0, std::ios::beg);
                long long counter=0;

                char msg[4];
                char size1[20];
                sprintf(size1,"%lld",(long long)temp2.size());
                bytes_sent=SSL_write(ssl, size1,20);
                char* filepath=ToArr(temp2);
                bytes_sent=SSL_write(ssl,filepath,temp2.size());
                
                char size2[20];
                sprintf(size2,"%lld",(long long)pos);
                bytes_sent=SSL_write(ssl, size2,20);

                int dataLen=0;
                int packetCounter=0;
                while(counter<=pos)
                {
                    counter+=SIZE;
                    std::vector<char> ans;
                    if(counter<pos)
                    {
                        ans.resize(SIZE);
                        ifs.read(&ans[0], SIZE);
                        ifs.seekg(counter, std::ios::beg);

                    }
                    else
                    {
                        ans.resize(SIZE-counter+pos);
                        ifs.read(&ans[0],SIZE-counter+pos);
                    }

                    char *file2=new char[SIZE];
                    for(int l=0 ;l<SIZE&&dataLen<pos;l++,dataLen++)
                    {
                        file2[l]=ans[dataLen%SIZE];
                    }
                    std::cout<<"SSL_writeing"<<std::endl;
                    SSL_write(ssl, file2,SIZE);
                    packetCounter++;
                    std::cout<<"sent "<<packetCounter<<std::endl;

                    SSL_read(ssl, msg,4);
                    std::cout<<"conf SSL_read\n";
                    if(dataLen==pos)
                    {
                        break;
                    }
                    std::vector<char> tempVector;
                    ans.swap(tempVector);
                }
                ifs.close();
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
                return 1;

            }
        case 12:
            {
                std::string temp2=ins.data1;
                char len[20];
                char size1[20];
                sprintf(size1,"%lld",(long long)temp2.size());
                bytes_sent=SSL_write(ssl, size1,20);
                char* filepath=ToArr(temp2);
                bytes_sent=SSL_write(ssl,filepath,temp2.size());
                return 1;
            }
        case 13: //Send Serverlist
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
                    std::string temp;
                    switch(fileCount)
                    {
                        case 0:
                        {
                            temp="receiving.txt";
                            break;
                        }
                        case 1:
                        {
                            temp="giving.txt";
                            break;
                        }
                        case 2:
                        {
                            temp="sehistory.txt";
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    std::string name=FileName(temp1+temp);
                    std::string filepath=(temp1+temp).substr(0,temp1.size()+temp.size()-name.size());
                    std::cout<<"Filepath:"<<filepath<<std::endl;
                    std::cout<<"Filename:"<<name<<std::endl;
                    boost::filesystem::path dir(filepath);
                    if(!(boost::filesystem::exists(dir)))
                    {
                        std::cout<<"Directory Doesn't Exists"<<std::endl;
                        if (boost::filesystem::create_directory(dir))
                            std::cout << "Directory Successfully Created !" << std::endl;
                    }
                    std::ifstream ifs(temp1+temp, std::ios::binary|std::ios::ate);
                    std::ifstream::pos_type pos = ifs.tellg();
                    std::vector<char> ans(pos);
                    ifs.seekg(0, std::ios::beg);
                    ifs.read(&ans[0], pos);
                    ifs.close();

                    char size1[20];
                    sprintf(size1,"%lld",(long long)ans.size());
                    bytes_sent=SSL_write(ssl, size1,20);
                    std::cout<<"Initiating SSL_writing protocol\n";

                    int dataLen=0;
                    int packetCounter=0;
                    while(1)
                    {
                        char *file2=new char[SIZE];
                        for(int l=0 ;l<SIZE&&dataLen<ans.size();l++,dataLen++)
                        {
                            file2[l]=ans[dataLen];
                        }
                        std::cout<<"SSL_writing"<<std::endl;
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
                    fileCount++;
                }
                return 1;
            }
        default:
            {
                return 0;
            }
    }
    
}

void CreateNewUser(std::string usn, std::string pwd)
{
	// Get details
	// Send to server
	// Add to userbase
	// Create folder on user   /DeadDrop/usn
	// Create folder on server /DeadDrop/
	// Touch files on server: 
 	// Touch Files on user; 

	Instruction Newuser= NewUser(usn,pwd);
	int x= ExecuteInstruction(Newuser);
	std::string foldername="/home/kartikeya/Desktop/DeadDrop/" + usn  + "/";
	std::string serverfoldername="/home/skipper/Desktop/DeadDropServer/" + usn + "/";
	SyncManager UserManager = SyncManager(usn); 
	boost::filesystem::path dir(foldername);
	if (!(boost::filesystem::exists(dir)))
	{
		std::cout<<"creating\n";
		if (boost::filesystem::create_directories(dir))
			std::cout <<"created\n";
	}
	UserManager.StoreToDiskDB("/home/kartikeya/Desktop/DeadDrop");
	x= ExecuteInstruction(TransferClientToServer(foldername + "sehistory.txt",serverfoldername +"sehistory.txt"));
	x= ExecuteInstruction(TransferClientToServer(foldername + "giving.txt",serverfoldername +"giving.txt"));
	x= ExecuteInstruction(TransferClientToServer(foldername + "receiving.txt",serverfoldername +"receiving.txt"));
}

bool UserLogin(std::string usn, std::string pwd)
{
	// Send login credentials
	// Receive Confirmation
	int x=ExecuteInstruction(DoLogin(usn,pwd));
	if (x==0)
    {
		std::cout<"Incorrect credentials\n";
        return false;
    }
	else
    {
		std::cout<<"Welcome to dead drop\n";
        return true;
    }
}

bool CheckUserExists(std::string usname)
{
	int x=ExecuteInstruction(UserExists(usname));
	if (x==1)
		return true;
	else
		return false;
}

void PerformSync(SyncManager UserSyncManager)
{
	int x;
    std::string foldername="/home/kartikeya/Desktop/DeadDrop/" + UserSyncManager.GetUsername() +"/";
    std::string serverfoldername="/home/skipper/Desktop/DeadDropServer/" + UserSyncManager.GetUsername() +"/";

    std::cout << "Transferring server info files to client\n";

    x= ExecuteInstruction(TransferServerToClient(foldername + "sehistory.txt",serverfoldername +"sehistory.txt"));
    x= ExecuteInstruction(TransferServerToClient(foldername + "giving.txt",serverfoldername +"giving.txt"));
    x= ExecuteInstruction(TransferServerToClient(foldername + "receiving.txt",serverfoldername +"receiving.txt"));

    std::cout << "Transferred server info files to client\n";

    UserSyncManager.LoadFromDiskDB("/home/kartikeya/Desktop/Deadrop");

    std::cout <<"Loaded files from disk\n";

    std::vector<Instruction> insvect=UserSyncManager.GetSyncingInstructions();
    for (int i=0; i<insvect.size(); i++)
    {
        x=ExecuteInstruction(insvect[i]);
    }

    std::cout << "Executed sync instructions \n";
    
    UserSyncManager.StoreToDiskDB("/home/kartikeya/Desktop/DeadDrop");

    std::cout << "Stored DB files to client\n";

    x= ExecuteInstruction(TransferClientToServer(foldername + "sehistory.txt",serverfoldername +"sehistory.txt"));
    x= ExecuteInstruction(TransferClientToServer(foldername + "giving.txt",serverfoldername +"giving.txt"));
    x= ExecuteInstruction(TransferClientToServer(foldername + "receiving.txt",serverfoldername +"receiving.txt"));
    
    x= ExecuteInstruction(RefreshServerDB(serverfoldername));
    
    std::cout << "Updated server db files\n";

    // TODO: Get Server DB files
	// TODO: Store DB files on client
	// TODO: Update server DB file
}

void DeleteFileServer(SyncManager UserSyncManager, std::string filenameclient)
{

    // TODO: Send delete instruction on cloud
    // TODO: Send delete instruction local
    // TODO: Remove file name from databases
    // TODO: Store data bases

}

void GetFileFromServer(SyncManager UserSyncManager, std::string filename)
{
    std::string foldername="/home/kartikeya/Desktop/DeadDrop/" + UserSyncManager.GetUsername() +"/";
    UserSyncManager.AddFileToSync(filename);
    PerformSync(UserSyncManager);
           
    // TODO: Add filename to sync list
    // TODO: Perform getting instruction
    // TODO: Store DB files on client
}

void DeleteFileClient(SyncManager UserSyncManager, std::string filename)
{
    // TODO: remove file from sync list
    // TODO: send delete file client instruction
    // TODO: send delete file server instruction
    // TODO: Update server db files
    // TODO: Update client db files
}

void KeepOnlineOnly(SyncManager UserSyncManager, std::string filename)
{
    std::string foldername="/home/kartikeya/Desktop/DeadDrop/" + UserSyncManager.GetUsername() +"/";
    UserSyncManager.RemoveFileFromSync(filename);
    UserSyncManager.StoreToDiskDB(foldername);
    int x=ExecuteInstruction(DeleteFileOnClient(filename));
    // TODO: remove file from sync list
    // TODO: send delete client file instruction
    // TODO: Update client db files
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
			std::string x;
            std::cout << "0: NEWUSER \n 1: LOGIN \n 2: USER EXISTS \n 3: SYNC\n";
			std::cin >>x;

			std::string usinp,uspwd;
            if (x=="0")
            {
                std::cin >> usinp;
                std::cin >> uspwd;
            	CreateNewUser(usinp,uspwd);
            }
			else if (x=="1")
			{
                std::cin >> usinp;
                std::cin >> uspwd;
            	UserLogin(usinp,uspwd);
            }
			else if (x=="2")
			{
                std::cin >> usinp;
            	std::cout << CheckUserExists(usinp);
            }
            else if (x=="3")
            {
                // TODO: Implement Syncing
                std::cin >> usinp;
                std::cout <<"Starting\n";
                SyncManager l=SyncManager(usinp);
                std::cout << "Initialised\n";
                l.LoadFromDiskDB("/home/kartikeya/Desktop/DeadDrop/");
                std::cout << "Got basic data\n";
                PerformSync(l);
            }

    		// std::cin >> usinp;
			// std::cin >> uspwd;
			// Instruction newus=NewUser(usinp,uspwd);
			// int k=ExecuteInstruction(newus);
			// std::cout<<k<<"\n";
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