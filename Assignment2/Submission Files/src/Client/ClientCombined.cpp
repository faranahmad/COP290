#include "ClientCombined.h"
#include <cstdlib>
#include "filesonserver.h"
#include <stdlib.h> 
#define SIZE 10000
#define BUFFSIZE 10000000

extern std::string inst,datafield1,datafield2,datafield3;
extern std::string reversedata1,reversedata2,reversedata3;
extern bool InstructionStarted, InstructionCompleted;
extern SyncManager MergedSyncManager;
extern bool ifconnected;
extern std::vector<Data> ReverseDataFiles;

int sockID;
SSL* ssl;
struct addrinfo *host_info_list; 

void Display(std::vector<Data> v)
{
#ifdef DEBUG
    std::cout <<"STARTING DISPLAY\n";
#endif
    for(int i=0;i<v.size();i++)
    {
#ifdef DEBUG
        std::cout<<"Data name:"<<v[i].GetName()<<std::endl;
#endif
        Display(v[i].GetListFiles());
    }
#ifdef DEBUG
    std::cout <<"ENDING DSIPLAY\n";
#endif
    return;
}

std::string GetUserName(std::string name)
{
    std::string ans;
    int i=0;
    int it=0;
    while(i<3)
    {
        ans=ans+name[it];
        if(name[it]=='/')
            i++;
        it++;
    }
#ifdef DEBUG
    std::cout<<name<<"\t"<<ans<<std::endl;
#endif
    return ans;
}

std::vector<Data> GetDataFiles(std::string location)
{
// #ifdef DEBUG
#ifdef DEBUG
    std::cout << "In get data files func\n";
#endif
// #endif
    boost::filesystem::path p (location);
    std::vector< Data > ans;        
    if (exists(p))    // does p actually exist?
    {
// #ifdef DEBUG
#ifdef DEBUG
        std::cout <<location <<"\n";
#endif
// #endif
        std::vector<boost::filesystem::path> v;
        std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), back_inserter(v));
        std::sort(v.begin(), v.end());
        for (int i=0; i<v.size() ; i++ )
        {
        	std::string s=v[i].string();
        	int pos=s.find(".temp");
        	s=s.substr(pos+5);
            if (is_regular_file(v[i]))
            {
#ifdef DEBUG
                std::cout <<"FILE FOUND: " << v[i].string() <<"\n";
#endif
                ans.push_back(Data(s,false));
            }
            else
            {
                Data d=Data(s,true);
// #ifdef DEBUG
                d.SetData(GetDataFiles(v[i].string()));
// #endif
                ans.push_back(d);
            }
        }
    }
    else
    {
#ifdef DEBUG
        std::cout <<"folder/file:"<<location<<" DNE \n";        
#endif
    }
    // Display(ans);
    return ans;

}



int GetData(std::vector<std::string> data) // "/username/.temp/..."
{
    std::vector<std::string> files;

    std::string mainpath(getenv("HOME"));
    mainpath=mainpath+"/Desktop/DeadDrop";
#ifdef DEBUG
    std::cout <<"%%%%%%%%%%%%%%%%%%%%%%%%%%starting\n";
#endif
    boost::filesystem::path dir1((mainpath+GetUserName(data[0])).c_str());
#ifdef DEBUG
    std::cout << dir1.string() <<"\n";
#endif
    if (!boost::filesystem::exists(dir1))
    	boost::filesystem::create_directories(dir1);
#ifdef DEBUG
    std::cout << "created dir\n";
#endif
    for(int i=0;i<data.size();i++)
    {
        if(data[i][(data[i]).size()-1]=='/')
        {
#ifdef DEBUG
        	std::cout <<"^^^^^^^^^^^^^ it is a folder\n";
#endif
            boost::filesystem::path dir((mainpath+data[i]).c_str());
            if(!(boost::filesystem::exists(dir)))
            {
#ifdef DEBUG
                std::cout<<"Directory Doesn't Exists\t"<<dir.string()<<  std::endl;
#endif
                if (boost::filesystem::create_directories(dir))
                {}
            }
        }
        else
        {
            files.push_back(data[i]);
        }
    }
#ifdef DEBUG
    std::cout << "out of big for1\n";
#endif
    for(int i=0;i<files.size();i++)
    {   
#ifdef DEBUG
        std::cout<<mainpath+files[i]<<std::endl;
#endif
        std::ofstream out((mainpath+files[i]).c_str());
        std::string d="DeadDrop";
        out<<d;
#ifdef DEBUG
        std::cout<<"Written\n";
#endif
        out.close();
    }
    std::string location=mainpath+GetUserName(data[0]);

    boost::filesystem::path directory_path((mainpath+GetUserName(data[0])).c_str());

    ReverseDataFiles=GetDataFiles(location);

    Display(ReverseDataFiles);

    if(boost::filesystem::exists(directory_path))
    {
        boost::filesystem::remove_all(directory_path);
    }
    return 0;
}

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
{   
	X509 *cert;
	char *line;
 
	cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
	if ( cert != NULL )
	{
#ifdef DEBUG
		std::cout<<"Server certificates:\n";
#endif
		line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
#ifdef DEBUG
		std::cout<<"Subject: "<<line<<std::endl;
#endif
		free(line);       /* free the malloc'ed string */
		line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
#ifdef DEBUG
		std::cout<<"Issuer: "<<line<<std::endl;
#endif
		free(line);       /* free the malloc'ed string */
		X509_free(cert);     /* free the malloc'ed certificate copy */
    }
	else
    {
#ifdef DEBUG
		std::cout<<"No certificates.\n";
#endif
    }
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

std::string ExecuteInstruction(Instruction ins)
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
        case 16: //change password
            {
#ifdef DEBUG
                std::cout<<"Username\n";
#endif
                temp=ins.data1;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp.size());
                char* msg1=ToArr(temp);
#ifdef DEBUG
                std::cout<<temp.size()<<"   "<<strlen(msg1)<<std::endl;
#endif
                bytes_sent=SSL_write(ssl, size1,20);
                bytes_sent=SSL_write(ssl,msg1,temp.size());
#ifdef DEBUG
                std::cout<<"Password\n";
#endif
                temp=ins.data2;
                char size2[20];
                sprintf(size2,"%lld",(long long)temp.size());
                char* msg2=ToArr(temp);
                bytes_sent=SSL_write(ssl, size2,20);
                bytes_sent=SSL_write(ssl,msg2,temp.size());
                temp=ins.data3;
                char size3[20];
                sprintf(size3,"%lld",(long long)temp.size());
                char* msg3=ToArr(temp);
                bytes_sent=SSL_write(ssl, size3,20);
                bytes_sent=SSL_write(ssl,msg3,temp.size());
                char msg4[1];
                bytes_recieved=SSL_read(ssl,msg4,1);
                msg4[bytes_recieved]='\0';
                if(msg4[0]=='1')
                {
#ifdef DEBUG
                    std::cout<<"Successfully\n";
#endif
                    return "1";
                }
                else
                {
#ifdef DEBUG
                    std::cout<<"Sorry. Please try again\n";
#endif
                    return "0";
                }
            }
        case 0:
            {
                // #ignore
                return "1";
            }
        case 8: // Add user
            {
                // std::cout<<"Username\n";
                temp=ins.data1;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp.size());
                char* msg1=ToArr(temp);
#ifdef DEBUG
                std::cout<<temp.size()<<"   "<<strlen(msg1)<<std::endl;
#endif
                bytes_sent=SSL_write(ssl, size1,20);
                bytes_sent=SSL_write(ssl,msg1,temp.size());
                // std::cout<<"Password\n";
                temp=ins.data2;
                char size2[20];
                sprintf(size2,"%lld",(long long)temp.size());
                char* msg2=ToArr(temp);
                bytes_sent=SSL_write(ssl, size2,20);
                bytes_sent=SSL_write(ssl,msg2,temp.size());
#ifdef DEBUG
                std::cout<<"User Successfully added!\n";
#endif
                return "1";
            }
        case 7: // Login
            {
                // std::cout<<"Username\n";
                temp=ins.data1;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp.size());
                char* msg1=ToArr(temp);
                bytes_sent=SSL_write(ssl, size1,20);
                bytes_sent=SSL_write(ssl,msg1,temp.size());
                // std::cout<<"Password\n";
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
#ifdef DEBUG
                    std::cout<<"Successfully\n";
#endif
                    return "1";
                }
                else
                {
#ifdef DEBUG
                    std::cout<<"Sorry. Please try again\n";
#endif
                    return "0";
                }
            }
        case 9: //User exists
            {
                // std::cout<<"Enter Username\n";
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
                    // std::cout<<"User Exists\n";
                    return "1";
                }
                else
                {
                    // std::cout<<"User Does not exist\n";
                    return "0";
                }
            }
        case 1: //client to server
            {
                // std::cout<<"Client address\n";
                std::string temp1=ins.data1;
                // std::cout<<"Server address\n";
                std::string temp2=ins.data2;

                //filereading
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
                    // std::cout<<"SSL_writeing"<<std::endl;
                    SSL_write(ssl, file2,SIZE);
                    packetCounter++;
#ifdef DEBUG
                    std::cout<<"sent "<<packetCounter<<std::endl;
#endif

                    SSL_read(ssl, msg,4);
#ifdef DEBUG
                    std::cout<<"conf SSL_read\n";
#endif
                    if(dataLen==pos)
                    {
                        break;
                    }
                    std::vector<char> tempVector;
                    ans.swap(tempVector);
                }
                ifs.close();
#ifdef DEBUG
                std::cout<<"file sent"<<std::endl;
#endif

                char len[20];
                bytes_recieved=SSL_read(ssl, len,20);
                len[bytes_recieved]='\0';
                long long size=atoll(len);
#ifdef DEBUG
                std::cout<<size<<std::endl;
#endif
                char filename[size];
                bytes_recieved=SSL_read(ssl,filename,size);
                filename[bytes_recieved]='\0';
#ifdef DEBUG
                std::cout << ToStr(filename)<<"\n";
#endif
                return ToStr(filename);
            }
        case 2: //server to client
            {
                // std::cout<<"Enter client address\n";
                std::string temp1=ins.data1;
                // std::cout<<"Enter server address\n";
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
                // std::cout << "bystes recv : " << strlen(len) <<"\n";   
                len[bytes_recieved]='\0';
                long long size=atoll(len);
                for (int i=0; i< strlen(len) ; i++)
                {
#ifdef DEBUG
                    std::cout << len[i] <<"\n";
#endif
                }
                // std::cout<<size<<std::endl;
                
                std::string data="";
                int packetCounter=0;
                int dataLen=0;

                std::string name=FileName(temp1);
                std::string filepath2=temp1.substr(0,temp1.size()-name.size());
                boost::filesystem::path dir(filepath2);
                if(!(boost::filesystem::exists(dir)))
                {
                    // std::cout<<"Directory Doesn't Exists"<<std::endl;
                    if (boost::filesystem::create_directories(dir))
                    {
                        // std::cout << "Directory Successfully Created !" << std::endl;
                    }
                }
                std::string loc = filepath2 + name;
                std::ofstream outfile(loc);
                // std::cout<<filepath2<<"\t"<<name<<std::endl;
                while(1)
                {
                    char *file=new char[SIZE];
                    bytes_recieved=SSL_read(ssl, file,SIZE);
                    // std::cout<<ToStr(file)<<std::endl;
                    // std::cout<<bytes_recieved<<std::endl;
                    packetCounter++;
                    // std::cout<<"recieved "<<packetCounter<<std::endl;    
                    for(int i=0;i<bytes_recieved && dataLen<size;i++)
                    {
                        data+=file[i];
                        dataLen++;
                    }
                    outfile << data;
                    // std::cout<<data<<std::endl;
                    data="";
                    SSL_write(ssl, msg,4);
                    // std::cout<<"conf sent\n";
                    if(dataLen==size)
                    {
#ifdef DEBUG
                        std::cout<<"breaking now"<<std::endl;
#endif
                        break;
                    }
                }
                outfile.close();
#ifdef DEBUG
                std::cout<<"file SSL_read"<<std::endl;
#endif
                return "1";
            }
        case 5: //Delete file on user.
            {
                boost::filesystem::wpath file(ins.data1);
                if(boost::filesystem::exists(file))
                    boost::filesystem::remove(file);
                return "1";
            }
        case 6: //Delete file on server.
            {
#ifdef DEBUG
                std::cout<<"Server address\n";
#endif
                std::string temp2=ins.data1;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp2.size());
                bytes_sent=SSL_write(ssl, size1,20);
                char* filepath=ToArr(temp2);
                bytes_sent=SSL_write(ssl,filepath,temp2.size());
                return "1";
            }
        case 10: // quit
            {
#ifdef DEBUG
            	std::cout <<"quitting instruction starting\n";
#endif
            	char msg[1];
            	msg[0]='1';
            	bytes_sent=SSL_write(ssl,msg,1);
            	// std::cout << "sent\n";
            	bytes_recieved=SSL_read(ssl,msg,1);
                // std::cout <<"received\n";
                close(sockID);
                // std::cout <<"closed\n";
                SSL_free(ssl);
                // std::cout <<"freed\n";
                freeaddrinfo(host_info_list);
                // std::cout <<"freeaddr\n";
                return "1";
            }
        case 11: // get serverlist
            {
                // std::cout<<"Client address\n";
                std::string temp1=ins.data1; // including '/'
                // std::cout<<"Server address\n";
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
                    // std::cout<<size<<std::endl;
                    
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
                    // std::cout<<"Filepath:"<<filepath2<<std::endl;
                    // std::cout<<"Filename:"<<name<<std::endl;
                    boost::filesystem::path dir(filepath2);
                    if(!(boost::filesystem::exists(dir)))
                    {
                        // std::cout<<"Directory Doesn't Exists"<<std::endl;
                        if (boost::filesystem::create_directory(dir))
                        {
                            // std::cout << "Directory Successfully Created !" << std::endl;
                        }
                    }
                    std::ofstream outfile(filepath2+name);
                    while(1)
                    {
                        char *file=new char[SIZE];
                        bytes_recieved=SSL_read(ssl, file,SIZE);
                        // std::cout<<bytes_recieved<<std::endl;
                        packetCounter++;
                        // std::cout<<"recieved "<<packetCounter<<std::endl;    
                        for(int i=0;i<bytes_recieved && dataLen<size;i++)
                        {
                            data+=file[i];
                            dataLen++;
                        }
                        outfile << data;
                        data="";
                        SSL_write(ssl, msg,4);
                        // std::cout<<"conf sent\n";
                        if(dataLen==size)
                        {
                            // std::cout<<"breaking now"<<std::endl;
                            break;
                        }
                    }
                    outfile.close();
                    // std::cout<<"file SSL_read"<<std::endl;
                    fileCount++;
                }
                return "1";

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
                return "1";
            }
        case 13: //Send Serverlist
            {
                // std::cout<<"Client address\n";
                std::string temp1=ins.data1; // including '/'
                // std::cout<<"Server address\n";
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
                    // std::cout<<"Filepath:"<<filepath<<std::endl;
                    // std::cout<<"Filename:"<<name<<std::endl;
                    boost::filesystem::path dir(filepath);
                    if(!(boost::filesystem::exists(dir)))
                    {
                        // std::cout<<"Directory Doesn't Exists"<<std::endl;
                        if (boost::filesystem::create_directory(dir))
                        {
                            // std::cout << "Directory Successfully Created !" << std::endl;
                        }
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
                    // std::cout<<"Initiating SSL_writing protocol\n";

                    int dataLen=0;
                    int packetCounter=0;
                    while(1)
                    {
                        char *file2=new char[SIZE];
                        for(int l=0 ;l<SIZE&&dataLen<ans.size();l++,dataLen++)
                        {
                            file2[l]=ans[dataLen];
                        }
                        // std::cout<<"SSL_writing"<<std::endl;
                        SSL_write(ssl, file2,SIZE);
                        packetCounter++;
                        // std::cout<<"sent "<<packetCounter<<std::endl;

                        SSL_read(ssl, msg,4);
                        // std::cout<<"conf SSL_read\n";
                        if(dataLen==ans.size())
                        {
                            break;
                        }
                    }
                    std::vector<char> tempVector;
                    ans.swap(tempVector);
#ifdef DEBUG
                    std::cout<<"file sent"<<std::endl;
#endif
                    fileCount++;
                }
                return "1";
            }
        case 14: //client to server without filepath return
            {
#ifdef DEBUG
                std::cout<<"Client address\n";
#endif
                std::string temp1=ins.data1;
#ifdef DEBUG
                std::cout<<"Server address\n";
#endif
                std::string temp2=ins.data2;

                //filereading
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
#ifdef DEBUG
                    std::cout<<"SSL_writeing"<<std::endl;
#endif
                    SSL_write(ssl, file2,SIZE);
                    packetCounter++;
#ifdef DEBUG
                    std::cout<<"sent "<<packetCounter<<std::endl;
#endif

                    SSL_read(ssl, msg,4);
#ifdef DEBUG
                    std::cout<<"conf SSL_read\n";
#endif
                    if(dataLen==pos)
                    {
                        break;
                    }
                    std::vector<char> tempVector;
                    ans.swap(tempVector);
                }
                ifs.close();
#ifdef DEBUG
                std::cout<<"file sent"<<std::endl;
#endif
                return "1";
            }
        case 15:
            {
#ifdef DEBUG
                std::cout <<"In 15\n";
#endif
                temp=ins.data1;
                char size1[20];
#ifdef DEBUG
                std::cout <<" in 15th instruction\n";
#endif
                sprintf(size1,"%lld",(long long)temp.size());
                bytes_sent=SSL_write(ssl, size1,20);
#ifdef DEBUG
                std::cout << std::atoi(size1) <<"\n";
#endif
                char* msg1=ToArr(temp);
                bytes_sent=SSL_write(ssl,msg1,temp.size());
#ifdef DEBUG
                std::cout <<"In between\n"<<ToStr(msg1)<<std::endl;;
#endif
                return "1";
            }
        default:
            {
                return "0";
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
 	// Touch Files on user; 
	// Touch files on server: 

	Instruction Newuser= NewUser(usn,pwd);
    if (CheckUserExists(usn))
    {
        reversedata3="NO";
    }
    else
    {
        reversedata3="YES";
    	std::string x= ExecuteInstruction(Newuser);
        std::string mainpath(getenv("HOME")); 
    	std::string foldername=mainpath + "/Desktop/DeadDrop/" + usn  + "/";
    	std::string folder2 = foldername + "/.data/";
    	std::string serverfoldername="/home/faran/Desktop/DeadDropServer/" + usn + "/";
    	SyncManager UserManager = SyncManager(usn); 
    	boost::filesystem::path dir(folder2);
    	if (!(boost::filesystem::exists(dir)))
    	{
    		// std::cout<<"creating\n";
    		if (boost::filesystem::create_directories(dir))
            {}
        		// std::cout <<"created\n";
    	}
    	UserManager.StoreToDiskDB(mainpath + "/Desktop/DeadDrop");
    	x= ExecuteInstruction(DoNormalSending(foldername + ".data/sehistory.txt",serverfoldername +".data/sehistory.txt"));
    	x= ExecuteInstruction(DoNormalSending(foldername + ".data/giving.txt",   serverfoldername +".data/giving.txt"));
    	x= ExecuteInstruction(DoNormalSending(foldername + ".data/receiving.txt",serverfoldername +".data/receiving.txt"));
    }
}

bool UserLogin(std::string usn, std::string pwd)
{
	// Send login credentials
	// Receive Confirmation
	std::string x=ExecuteInstruction(DoLogin(usn,pwd));
	// std::cout << "Got ins for login\n";
	if (x=="0")
	{
		// std::cout<"Incorrect credentials\n";
		return false;
	}
	else
	{
		std::string mainpath(getenv("HOME")); 
		std::string foldername=mainpath + "/Desktop/DeadDrop/" + usn  + "/";
		std::string folder2 = foldername + ".data/";
		boost::filesystem::path dir(folder2);
		SyncManager UserMan = SyncManager(usn);
		if (boost::filesystem::exists(dir))
		{
		    // User already had logged in before on this machine
		    // std::cout <<"User existed already on pc\n";
		}
		else
		{
			// User logging in on new machine for the 1st time
			// Need to touch up files on client
			if (boost::filesystem::create_directories(dir))
			{
				// std::cout <<"created\n";
				// SyncManager UserMan= SyncManager(usn);
				UserMan.StoreToDiskDB(mainpath + "/Desktop/DeadDrop/");
			}
		}
		// std::cout<<"Welcome to dead drop\n";
		PerformSync(UserMan);
        MergedSyncManager=UserMan;
		// Perform Sync
		return true;
    }
}

bool CheckUserExists(std::string usname)
{
	// Send instruction to check if user is there in db
	std::string x=ExecuteInstruction(UserExists(usname));
	if (x=="1")
		return true;
	else
		return false;
}

void PerformSync(SyncManager UserSyncManager)
{
	// Refresh Files From Client Db
    // Get Server DB files
	// Perform Sync
	// Store DB files on client
	// Update server DB file
	
	std::string instructionresult;
	std::string mainpath(getenv("HOME")); 
	std::string foldername=mainpath + "/Desktop/DeadDrop/" + UserSyncManager.GetUsername()  + "/";
	std::string serverfoldername="/home/faran/Desktop/DeadDropServer/" + UserSyncManager.GetUsername() +"/";

	    
#ifdef DEBUG
    std::cout << "Transferring server info files to client\n";
#endif

	instructionresult = ExecuteInstruction(TransferServerToClient(foldername + ".data/sehistory.txt" , serverfoldername +".data/sehistory.txt"));
	instructionresult = ExecuteInstruction(TransferServerToClient(foldername + ".data/giving.txt" , serverfoldername +".data/giving.txt"));
	instructionresult = ExecuteInstruction(TransferServerToClient(foldername + ".data/receiving.txt", serverfoldername +".data/receiving.txt"));

#ifdef DEBUG
    std::cout << "Transferred server info files to client\n";
#endif

    UserSyncManager.LoadFromDiskDB(mainpath+"/Desktop/DeadDrop/");
 
#ifdef DEBUG
    std::cout <<"Loaded files from disk and now will enter sync\n";
#endif
 
    std::vector<Instruction> insvect=UserSyncManager.GetSyncingInstructions();
    for (int i=0; i<insvect.size(); i++)
    {
        Instruction toexec = insvect[i];
        instructionresult=ExecuteInstruction(insvect[i]);
#ifdef DEBUG
        std::cout << instructionresult << "\t" << toexec.modification <<"\n" ;
#endif
        if (toexec.modification==0)
        {
 
        }
        else if (toexec.modification==3)
        {
            UserSyncManager.AddFileToLocalFiles(toexec.data1, instructionresult);
            UserSyncManager.AddFileToLinking(toexec.data1, instructionresult);
        }
    }
    UserSyncManager.UpdateSyncTimes();
    // std::cout << "Executed sync instructions \n";
    // 
    UserSyncManager.StoreToDiskDB(mainpath+"/Desktop/DeadDrop/");
 
    // std::cout << "Stored DB files to client\n";
 
 	Instruction b;
    b.modification = 15;
    b.data1 = UserSyncManager.GetUsername();
    ExecuteInstruction(b);
    

	instructionresult = ExecuteInstruction(TransferServerToClient(foldername + ".data/serverfiles.txt", serverfoldername +".data/serverfiles.txt"));

	std::string line1toread;
	std::ifstream myfile (foldername + ".data/serverfiles.txt");
	std::vector<std::string> readdata;
	if (myfile.is_open())
	{
	while ( getline (myfile,line1toread) )
		{	
			readdata.push_back(line1toread);
		}
		myfile.close();
	}
	if (readdata.size())
	{
    	GetData(readdata);
    }
    else
    {
        ReverseDataFiles = std::vector< Data > () ;   
    }

	Display(ReverseDataFiles);

	instructionresult = ExecuteInstruction(DoNormalSending(foldername + ".data/sehistory.txt",serverfoldername +".data/sehistory.txt"));
	instructionresult = ExecuteInstruction(DoNormalSending(foldername + ".data/giving.txt",serverfoldername +".data/giving.txt"));
	instructionresult = ExecuteInstruction(DoNormalSending(foldername + ".data/receiving.txt",serverfoldername +".data/receiving.txt"));
    // 
    // std::cout << "Updated server db files\n";
}

void DeleteFileClient(SyncManager UserSyncManager, std::string filenameclient)
{
	// Refresh client db files
	// Get server db files
	// Send delete instruction local
	// Send delete instruction on cloud
	// Remove file name from databases
	// Store data bases
	// Update server db files
	
	// TODO: Add support for shared files
	// TODO: Add support for receiving files

	std::string instructionresult;

	std::string mainpath(getenv("HOME")); 
	std::string foldername=mainpath + "/Desktop/DeadDrop/" + UserSyncManager.GetUsername()  + "/";
	std::string serverfoldername="/home/faran/Desktop/DeadDropServer/" + UserSyncManager.GetUsername() +"/";

	instructionresult = ExecuteInstruction(TransferServerToClient(foldername + ".data/sehistory.txt" , serverfoldername +".data/sehistory.txt"));
    instructionresult = ExecuteInstruction(TransferServerToClient(foldername + ".data/giving.txt" ,    serverfoldername +".data/giving.txt"));
    instructionresult = ExecuteInstruction(TransferServerToClient(foldername + ".data/receiving.txt",  serverfoldername +".data/receiving.txt"));

	// std::cout << "Transferred server info files to client\n";

	UserSyncManager.LoadFromDiskDB(mainpath+"/Desktop/DeadDrop/");
	
	std::string filenameserver = UserSyncManager.GetServerMappingForFile(filenameclient);

	instructionresult = ExecuteInstruction(DeleteFileOnClient(filenameclient));
	instructionresult = ExecuteInstruction(DeleteFileOnServer(filenameserver));

	UserSyncManager.RemoveFileFromSync(filenameclient);

	UserSyncManager.RemoveFromClientBase(filenameclient);

	UserSyncManager.StoreToDiskDB(mainpath+"/Desktop/DeadDrop/");

	instructionresult = ExecuteInstruction(DoNormalSending(foldername + ".data/sehistory.txt",serverfoldername +".data/sehistory.txt"));
	instructionresult = ExecuteInstruction(DoNormalSending(foldername + ".data/giving.txt",   serverfoldername +".data/giving.txt"));
	instructionresult = ExecuteInstruction(DoNormalSending(foldername + ".data/receiving.txt",serverfoldername +".data/receiving.txt"));
    
}

void DeleteFileServer(SyncManager UserSyncManager, std::string filenameserver)
{
	// Get server db files
	// Refresh client db files
	// Send delete instruction on cloud
	// Send delete instruction local
	// Remove file name from databases
	// Store data bases
	// Update server db files
	
	// TODO: Add support for shared files
	// TODO: Add support for receiving files

	std::string instructionresult;

	std::string mainpath(getenv("HOME")); 
	std::string foldername=mainpath + "/Desktop/DeadDrop/" + UserSyncManager.GetUsername()  + "/";
	std::string serverfoldername="/home/faran/Desktop/DeadDropServer/" + UserSyncManager.GetUsername() +"/";

	instructionresult = ExecuteInstruction(TransferServerToClient(foldername + ".data/sehistory.txt" , serverfoldername +".data/sehistory.txt"));
	instructionresult = ExecuteInstruction(TransferServerToClient(foldername + ".data/giving.txt" ,    serverfoldername +".data/giving.txt"));
	instructionresult = ExecuteInstruction(TransferServerToClient(foldername + ".data/receiving.txt",  serverfoldername +".data/receiving.txt"));

	// std::cout << "Transferred server info files to client\n";

	UserSyncManager.LoadFromDiskDB(mainpath+"/Desktop/DeadDrop/");

	instructionresult = ExecuteInstruction(DeleteFileOnServer(filenameserver));
	// TODO: Get server mapping for file
	std::string filenameclient = UserSyncManager.GetClientMappingForFile(filenameserver);
	instructionresult = ExecuteInstruction(DeleteFileOnClient(filenameclient));

	UserSyncManager.RemoveFileFromSync(filenameclient);

	// TODO: Remove From Server Base
	UserSyncManager.RemoveFromServerBase(filenameserver);

	UserSyncManager.StoreToDiskDB(mainpath+"/Desktop/DeadDrop/");


}

void GetFileFromServer(SyncManager UserSyncManager, std::string filename)
{
	// Get server db files
	// Refresh client db files
	// Add file to synclist
	// Transfer file from server to client
	// Add to other mapping files
	// Store DB files to client
	// Update db files on server

	std::string instructionresult;

	std::string mainpath(getenv("HOME")); 
	std::string foldername=mainpath + "/Desktop/DeadDrop/" + UserSyncManager.GetUsername()  + "/";
	std::string serverfoldername="/home/faran/Desktop/DeadDropServer/" + UserSyncManager.GetUsername() +"/";

	instructionresult = ExecuteInstruction(TransferServerToClient(foldername + ".data/sehistory.txt", serverfoldername +".data/sehistory.txt"));
	instructionresult = ExecuteInstruction(TransferServerToClient(foldername + ".data/giving.txt"   , serverfoldername +".data/giving.txt"));
	instructionresult = ExecuteInstruction(TransferServerToClient(foldername + ".data/receiving.txt", serverfoldername +".data/receiving.txt"));

	// LOTS OF CHANGES

	UserSyncManager.LoadFromDiskDB(mainpath+"/Desktop/DeadDrop/");
	UserSyncManager.AddFileToSync(filename);
	// TODO: Add file to main files server



	// UserSyncManager.AddFileToMainFilesClient(filenamecl,filename);
	
	std::string filenameclient = UserSyncManager.GetClientMappingForFile(filename);
	instructionresult = ExecuteInstruction(TransferServerToClient(filenameclient,filename));

	UserSyncManager.StoreToDiskDB(mainpath+"/Desktop/DeadDrop/");

	instructionresult = ExecuteInstruction(DoNormalSending(foldername + ".data/sehistory.txt",serverfoldername +".data/sehistory.txt"));
	instructionresult = ExecuteInstruction(DoNormalSending(foldername + ".data/giving.txt",serverfoldername    +".data/giving.txt"));
	instructionresult = ExecuteInstruction(DoNormalSending(foldername + ".data/receiving.txt",serverfoldername +".data/receiving.txt"));

}

void GetSharedFileFromServer(std::string serverfname)
{
	std::string p = "/home/faran/Desktop/DeadDropServer/";
    // std::cout <<serverfname <<"\n";
	std::string lpath = serverfname.substr(p.size());
	// std::cout <<"&&&&&&&&&&&&\t" << lpath <<"\n"; 
	std::string mainpath(getenv("HOME")); 
	std::string foldername=mainpath + "/Desktop/DeadDrop/" + MergedSyncManager.GetUsername()  + "/Shared/";
	std::string filelpath = foldername + lpath;
	// std::cout << "*******\t" << filelpath <<"\n";
	std::string instructionresult= ExecuteInstruction(TransferServerToClient(filelpath, serverfname));
}

int GetShareType(SyncManager UserSyncManager, std::string sefname)
{
	// 0 is read and write only
	// 1 is read only
	std::vector<Sharing> recvfiles= UserSyncManager.GetReceivingFiles().GetSharingList();
	for (int i=0; i<recvfiles.size() ; i++)
	{
		if (recvfiles[i].FilePath == sefname)
		{
			return recvfiles[i].ShareType;
		}
	}
}

bool ShareSendFileToServer(std::string clfname)
{
	std::string mainpath(getenv("HOME")); 
	std::string foldername = mainpath + "/Desktop/DeadDrop/" + MergedSyncManager.GetUsername()  + "/Shared/";
	std::string serverfname = "/home/faran/Desktop/DeadDropServer/" + clfname.substr(foldername.size());
	
	int stype = GetShareType(MergedSyncManager, serverfname);
	if (stype == 0)
	{
        
        // Get sehistory for serverfname
        // modify time in sehistory
        // Upload sehistory
		
#ifdef DEBUG
		std::cout <<clfname<<"\t" << serverfname<<"\n";
#endif
		std::string instructionresult = ExecuteInstruction(DoNormalSending(clfname, serverfname));
		
        int pos1=clfname.substr(foldername.size()).find("/");

        std::string serverfnameforf = clfname.substr(foldername.size()).substr(0,pos1);
        std::string locforfilehistory=   "/home/faran/Desktop/DeadDropServer/" + serverfnameforf +"/.data/sehistory.txt";
        std::string locfortemp = mainpath + "/.temp.txt" ;

        // std::cout <<"LOCATION TEMP \t" << locfortemp <<"\n";
        // std::cout <<"LOCATION SERVER \t" << locforfilehistory <<"\n";

        instructionresult=ExecuteInstruction(TransferServerToClient(locfortemp,locforfilehistory));

        FileHistory xyz = FileHistory(locfortemp);
        xyz.LoadFromFileBase(locfortemp);
        for (int i=0; i<xyz.GetNumberOfFiles(); i++)
        {
        	if (xyz.GetNthName(i) == serverfname)
        	{
        		xyz.SetNthTime(i,std::time(0));	
        	}
        }
        xyz.StoreToFileBase(locfortemp);

        instructionresult=ExecuteInstruction(DoNormalSending(locfortemp,locforfilehistory));
        // std::cout <<instructionresult << "\n";

		return true;
    }
    else
    {
        // Cannot upload a read only file
        return false;
    }
}

void KeepOnlineOnly(SyncManager UserSyncManager, std::string filename)
{
	// Load disk db
	// Remove from sync list
	// Remove from disk client
	// Store db

	std::string mainpath(getenv("HOME")); 
	std::string foldername=mainpath + "/Desktop/DeadDrop/" + UserSyncManager.GetUsername()  + "/";
	std::string serverfoldername="/home/faran/Desktop/DeadDropServer/" + UserSyncManager.GetUsername() +"/";

	UserSyncManager.LoadFromDiskDB(mainpath+"/Desktop/DeadDrop/");

	UserSyncManager.RemoveFileFromSync(filename);
    std::string instructionresult=ExecuteInstruction(DeleteFileOnClient(filename));
	UserSyncManager.StoreToDiskDB(mainpath+"/Desktop/DeadDrop/");

}

void ShareFile(std::string username,std::string filepath, int perms)
{
	// Add file to sharing list
	// Move sharing file to server
	// Get the recvfiles of the user
	// Add the file to the recv files 
	// Move the recv files to server

	std::string mainpath(getenv("HOME")); 
	std::string foldername=mainpath + "/Desktop/DeadDrop/" + MergedSyncManager.GetUsername()  + "/";
	std::string serverfoldername="/home/faran/Desktop/DeadDropServer/" + MergedSyncManager.GetUsername() +"/";

	MergedSyncManager.LoadFromDiskDB(mainpath + "/Desktop/DeadDrop");

	std::string serverfnameforf = MergedSyncManager.GetClientMappingForFile(filepath);
	// std::cout << "filepath to share \t" <<filepath <<"\n";
#ifdef DEBUG
	std::cout << serverfnameforf <<"\n";
#endif

	FileSharing sharingf= MergedSyncManager.GetGivingFiles();
	sharingf.AddNewGivingLocationType(serverfnameforf, username, perms);
	MergedSyncManager.SetGivingFiles(sharingf);
	MergedSyncManager.StoreToDiskDB(mainpath + "/Desktop/DeadDrop");
	std::string instructionresult;
	instructionresult = ExecuteInstruction(DoNormalSending(foldername + ".data/giving.txt",serverfoldername    +".data/giving.txt"));

	std::string serverfilenamerecv = "/home/faran/Desktop/DeadDropServer/" + username + "/.data/receiving.txt";
	std::string tempname = foldername + "/.data/temp.txt";
	instructionresult = ExecuteInstruction(TransferServerToClient(tempname,serverfilenamerecv));

	FileReceiving recvtemp;
	recvtemp.LoadSharingFromDisk(tempname);
	recvtemp.AddNewLocationType( serverfnameforf, perms);
	recvtemp.StoreSharingToDisk(tempname);

	instructionresult = ExecuteInstruction(DoNormalSending(tempname,serverfilenamerecv));
}

void RemoveReceiving(std::string filepath)
{
	std::vector<Sharing> recvfiles1=MergedSyncManager.GetReceivingFiles().GetSharingList();
	bool done3= false;
#ifdef DEBUG
	std::cout << "%%%%%%%%%%" <<filepath <<"\n";
#endif
    for (int i=0; (i<recvfiles1.size()) && !(done3); i++)
    {
		if (recvfiles1[i].FilePath == filepath)
		{
#ifdef DEBUG
			std::cout <<"FOUND WHAT TO ERASE\n";
#endif
			recvfiles1.erase(recvfiles1.begin() + i);
			done3=true;
		}
	}
	FileReceiving x;
	x.SetSharingList(recvfiles1);
	MergedSyncManager.SetReceivingFiles(x);
	// std::cout << "REMOVED\n";
	std::string instructionresult;
	std::string mainpath(getenv("HOME")); 
	std::string foldername=mainpath + "/Desktop/DeadDrop/" + MergedSyncManager.GetUsername()  + "/";
	std::string serverfoldername="/home/faran/Desktop/DeadDropServer/" + MergedSyncManager.GetUsername() +"/";

	MergedSyncManager.StoreToDiskDB(mainpath+"/Desktop/DeadDrop/");
 
    // std::cout << "Stored DB files to client\n";
 
	instructionresult = ExecuteInstruction(DoNormalSending(foldername + ".data/receiving.txt",serverfoldername +".data/receiving.txt"));
}

int clientmain(int argc, char *argv[])
{
	if(argc<3)
	{
		std::cout<<"Error. Usage : ./tclient ip portnumber\n";
	}
	else
	{
	    SSL_CTX *ctx=InitSSL();
	
	    int status;                      // Contains the status of the server
	    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
	    struct sockaddr_in server;
	    int sock;
	
	    memset(&host_info, 0, sizeof host_info);

    	host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    	host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

	    status = getaddrinfo(argv[1], argv[2], &host_info, &host_info_list);
	    if (status != 0)  
        {
#ifdef DEBUG
    	    std::cout << "Getaddrinfo error" << gai_strerror(status) ;
#endif
        }

     	sockID = socket(host_info_list->ai_family, host_info_list->ai_socktype,host_info_list->ai_protocol);
    	if (sockID == -1)  
        {
        	std::cout << "Socket error " ;
        }

    	int buffs = BUFFSIZE;
    	setsockopt(sockID, SOL_SOCKET, SO_RCVBUF, &buffs, sizeof(buffs));
#ifdef DEBUG
    	std::cout << "Connecting..."  << std::endl;
#endif
    	status = connect(sockID, host_info_list->ai_addr, host_info_list->ai_addrlen);
    	if (status == -1)  
    	{
            // std::cout << "Connection error!\n"; 
        }
    	else 
    	{
        	// std::cout<<"Connected\n";
        }
   
    	uint32_t htonl(uint32_t hostlong);

        bool ExitDone=false;
    // bool quit =false;

	    ssl = SSL_new(ctx);      /* create new SSL connection state */
	    SSL_set_fd(ssl, sockID); 
	
	    if ( SSL_connect(ssl) <0 )   /* perform the connection */
	        ERR_print_errors_fp(stderr);
	    else
	    {
#ifdef DEBUG
			std::cout << "Connected with ____ encryption " << SSL_get_cipher(ssl) <<"\n";
#endif
	        ShowCerts(ssl);        /* get any certs */
	        SSL_set_connect_state(ssl); 
			// std::string x;
#ifdef DEBUG
            std::cout << "0: NEWUSER \n 1: LOGIN \n 2: USER EXISTS \n 3: SYNC\n";
#endif
	      while (!ExitDone)
            {
            	ifconnected=true;                
                if (inst=="0")
                {
                	InstructionStarted=true;
                    // std::cout<<"Starting new user creation\t" << datafield1 <<"\t" << datafield2 <<"\n";
            	    
					std::string usinp=datafield1;
					std::string uspwd=datafield2;
            
                	CreateNewUser(usinp,uspwd);

                    inst="";
                    datafield1="";
                    datafield2="";
                    InstructionCompleted=true;
#ifdef DEBUG
                    std::cout<<"Out of inst\n";
#endif
                }
				else if (inst=="1")
				{
            		// LOGIN INSTRUCTION

            		InstructionStarted=true;

            		std::string usinp=datafield1;
					std::string uspwd=datafield2;
            
                    // std::cout <<"Login instruction to be executed\n";
            		// std::cout << ""
                	bool result=UserLogin(usinp,uspwd);

                	if (result)
                	{
                		reversedata1="YES";
                		reversedata2=usinp;
                	}
                	else
                	{
                		reversedata1="NO";
                	}

                    inst="";
                    datafield1="";
                    datafield2="";
                    InstructionCompleted=true;
                }
				else if (inst=="2")
				{
					// Check if user exists
					InstructionStarted=true;
					std::string usinp = datafield1;
#ifdef DEBUG
					std::cout << inst <<"\t" <<usinp<<"\n";
#endif
					if (CheckUserExists(usinp))
					{
						reversedata3="YES";
					}
					else
					{
						reversedata3="NO";
					}
#ifdef DEBUG
					std::cout <<reversedata3<<"\n";
#endif
					InstructionCompleted=true;
					inst="";
                }
                else if (inst=="3")
                {
                    // std::cin >> usinp;
                    std::string usinp=datafield1;
                    // std::cout <<"Starting\n";
                    SyncManager l=SyncManager(usinp);
                    // std::cout << "Initialised\n";
                    l.LoadFromDiskDB("/home/kartikeya/Desktop/DeadDrop/");
                    // std::cout << "Got basic data\n";
                    PerformSync(l);
                    inst="";
                }
                else if (inst=="4")
                {
                    // Syncing
                    InstructionStarted=true;
                    PerformSync(MergedSyncManager);
                    inst="";
                    InstructionCompleted=true;
                }
                else if (inst=="5")
                {
                	// Share file with user and permissions
                	InstructionStarted=true;
                	// std::cout << "entered sharing inst\n";
                	std::string ftoshare = datafield1;
                	std::string ustoshare = datafield2;
                	int typeshare;
                	if (datafield3=="0")
                	{	
                		typeshare=0;
                	}
                	else
                	{
                		typeshare=1;
                	}
					ShareFile(ustoshare,ftoshare,typeshare);
                	inst="";
                	InstructionCompleted=true;
                }
                else if (inst=="6")
                {
                	// Change Password
                	InstructionStarted=true;

                	std::string instructionresult=ExecuteInstruction(ChangePasswordIns(MergedSyncManager.GetUsername() ,datafield1,datafield2));
                	
                	if (instructionresult=="1")
                	{
                		reversedata1="YES";
                	}
                	else
                	{
                		reversedata1="NO";
                	}
                	inst="";

                	InstructionCompleted=true;
                }
                else if (inst=="7")
                {
                	// Get shared file from server
                	InstructionStarted=true;

                	GetSharedFileFromServer(datafield1);
                	inst="";
                	InstructionCompleted=true;
                }
                else if (inst=="8")
                {
                	// Upload shared file to server
                	InstructionStarted=true;
                	bool ans1=ShareSendFileToServer(datafield1);

                	if (ans1)
                	{
                		reversedata1="YES";
                	}
                	else
                	{
                		reversedata1="NO";
                	}
                	inst="";
                	InstructionCompleted=true;
                }
                else if (inst=="9")
                {
                	// Remove file from receiving
                	InstructionStarted=true;

                	RemoveReceiving(datafield1);

                	inst="";
                	InstructionCompleted=true;
                }
                else if (inst=="e")
                {
                	InstructionStarted=true;
#ifdef DEBUG
                    std::cout<<"Executing exit\n";
#endif
                    ExitDone=true;        
                }
            }
#ifdef DEBUG
            std::cout <<"Giving exit command\n";
#endif
            ExecuteInstruction(Exit());
			InstructionCompleted=true;
#ifdef DEBUG
            std::cout <<"Exited\n";
#endif
    	}
	}
	return 0;
}