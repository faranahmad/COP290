#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>     // Needed for closing the sockets
#include "UserBase.h"
#include "FileHistory.h"   
#include <fstream>
#include <string>
#include <vector>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem.hpp>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <pthread.h>

#define SIZE 10000
#define JOIN 500
#define BUFFSIZE 10000000
#define THREADS 100


SSL_CTX *ctx;
bool closeServer=false;

UserBase base=UserBase();        // Loading the database of users.
int sockID ;                         // The socket descriptor

struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

std::vector<std::string> usersLog;
std::vector<std::string> allUsers; 

std::vector<std::string> GetFiles(std::string location)
{
    boost::filesystem::path p (location);
    std::vector< std::string > ans;     
    if (exists(p))    // does p actually exist?
    {
        std::vector<boost::filesystem::path> v;
        std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), back_inserter(v));
        std::sort(v.begin(), v.end());
        for (int i=0; i<v.size() ; i++ )
        {
            if (is_regular_file(v[i]))
            {
                ans.push_back(v[i].string());
            }
            else
            {
                std::cout<<"###########"<<v[i].string()<<std::endl;
                if(v[i].string().find(".data")!=std::string::npos)
                    continue;
                ans.push_back(v[i].string()+"/");
                std::vector<std::string> Merged = ans;
                std::vector<std::string> Subset = GetFiles(v[i].string());
                Merged.insert(Merged.end(), Subset.begin(), Subset.end());
                ans = Merged;
            }
        }
    }
    else
    {
        std::cout <<"folder dne \n";        
    }
    std::cout<<"Out of get files"<<std::endl;
    return ans;
}   

bool EqualVector(std::vector<char> file1, std::vector<char> file2)
{
    for(int i=0;i<file1.size();i++)
    {
        if(file1[i]!=file2[i])
        {   
            std::cout<<i<<"    "<<file1[i]<<"    "<<file2[i]<<std::endl;
            return false;
        }
    }
    return true;
}

int CompFiles(std::string file1,  std::string file2)
{
    std::ifstream ifs1(file1,std::ios::binary|std::ios::ate);
    std::ifstream ifs2(file2,std::ios::binary|std::ios::ate);

    ifs1.seekg(0, std::ios::end);
    std::ifstream::pos_type pos = ifs1.tellg();
    ifs2.seekg(0, std::ios::end);
    std::ifstream::pos_type pos2 = ifs2.tellg();
    long long counter=0;
    std::vector<char> f1;
    std::vector<char> f2;
    if((long long)pos!=(long long)pos2)
    {
        std::cout<<"Sizes dont match"<<std::endl;
        goto WRONG;
    }
    
    while(counter<pos)
    {
        ifs1.seekg(counter,std::ios::beg);
        ifs2.seekg(counter,std::ios::beg);
        if(counter+SIZE>pos)
        {   
            int temp=(long long )pos - counter;
            f1.resize(temp);
            f2.resize(temp);
            ifs1.read(&f1[0],temp);
            ifs2.read(&f2[0],temp);
        }
        else
        {
            f1.resize(SIZE);
            f2.resize(SIZE);
            ifs1.read(&f1[0],SIZE);
            ifs2.read(&f2[0],SIZE);
        }
        std::cout<<f1.size()<<f2.size()<<std::endl;
        if (EqualVector(f1,f2))
            std::cout << "success" << std::endl;
        else
        {   
            WRONG:std::cout << "Not equal"<<std::endl;
            return false;
        }
        counter+=SIZE;
    }
    std::cout<<"Equal"<<std::endl;
    return true;
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
    ans[str.size()]='\0';
    return ans;
}

int isRoot()
{
    if (getuid() != 0)
        return 0;
    else
        return 1;
}

void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile)
{
    /* set the local certificate from CertFile */
    if ( SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* set the private key from KeyFile (may be the same as CertFile) */
    if ( SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* verify private key */
    if ( !SSL_CTX_check_private_key(ctx) )
    {
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }
}

void ShowCerts(SSL* ssl)
{   X509 *cert;
    char *line;
 
    cert = SSL_get_peer_certificate(ssl); /* Get certificates (if available) */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);
        X509_free(cert);
    }
    else
        printf("No certificates.\n");
}

SSL_CTX* InitSSL()
{
    SSL_load_error_strings();   /* load all error messages */
    SSL_library_init();
    OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
    SSL_CTX *ctx=SSL_CTX_new(SSLv3_server_method());
    if ( ctx == NULL )
    {
        exit(0);
    }

    char* cert=ToArr("Cert.pem");
    LoadCertificates(ctx, cert, cert);
    return ctx;
}

void *Input(void * data)
{
    int input=1;
    START:std::cin>>input;
    if(input==0)
    {
        closeServer=true;
        close(sockID);
        freeaddrinfo(host_info_list);
        SSL_CTX_free(ctx);   
        // pthread_exit(NULL);
        std::cout<<"Server Shutting Down\n";  
        exit(0);
    }
    else
    {
        goto START;
    }
}

void *ClientService(void* data)
{
    int acceptID=(int)(long)data; 
    bool quit=false;                                                                    // Accepting connection
    if (acceptID == -1)
    {
        std::cout << "Listen error" << std::endl ;
    }
    else
    {
        std::cout << "Connection accepted. Using new sockID : "  <<  acceptID << std::endl;
    }

    std::string userID="";

    SSL* ssl = SSL_new(ctx);              /* get new SSL state with context */
    SSL_set_fd(ssl, acceptID);

    if ( SSL_accept(ssl)<0 )     /* do SSL-protocol accept */
        ERR_print_errors_fp(stderr);
    else
    {
        SSL_set_accept_state(ssl); 
        ShowCerts(ssl);
    while(!quit)
    {
         
        std::cout << "Waiting to recieve data..."  << std::endl;
        char command[2];
        int bytes_recieved;
        int bytes_sent;
        long long size;
        bytes_recieved=SSL_read(ssl, command,2);
        command[bytes_recieved]='\0';
        std::cout<<"Command recieved "<<atoi(command)<<std::endl;

        switch(atoi(command))
        {
            case 8: // Adding username
                {
                    char len[20];
                    bytes_recieved=SSL_read(ssl,len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    char msg1[size];
                    bytes_recieved=SSL_read(ssl,msg1,size);
                    msg1[bytes_recieved]='\0';
                    std::string username=ToStr(msg1);
                    std::cout<<username<<std::endl;
                    bytes_recieved=SSL_read(ssl,len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    char msg2[size];
                    bytes_recieved=SSL_read(ssl,msg2,size);
                    msg2[bytes_recieved]='\0';
                    base.InsertUser(User(username,ToStr(msg2)));
                    base.StoreToFile("Database.txt");
                    allUsers.push_back(username);
                    std::cout<<ToStr(msg2)<<std::endl;
                    break;
                }
            case 7: // Login
                {
                    char len[20];
                    bytes_recieved=SSL_read(ssl,len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    char msg1[size];
                    bytes_recieved=SSL_read(ssl,msg1,size);
                    msg1[bytes_recieved]='\0';
                    std::string username=ToStr(msg1);
                    std::cout<<username<<std::endl;
                    bytes_recieved=SSL_read(ssl,len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    char msg2[size];
                    bytes_recieved=SSL_read(ssl,msg2,size);
                    msg2[bytes_recieved]='\0';
                    char msg3[1];
                    msg3[1]='\0';
                    if(base.VerifyUserCredentials(User(username,ToStr(msg2))))
                    {
                        msg3[0]='1';
                        usersLog.push_back(username);
                        userID=username;
                    }
                    else
                    {
                        msg3[0]='0';
                    }
                    bytes_sent=SSL_write(ssl,msg3,1);
                    break;
                }
            case 9: // Exist
                {
                    char len[20];
                    bytes_recieved=SSL_read(ssl,len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    char msg1[size];
                    bytes_recieved=SSL_read(ssl,msg1,size);
                    msg1[bytes_recieved]='\0';
                    std::string username=ToStr(msg1);
                    std::cout<<username<<std::endl;
                    char msg3[1];
                    msg3[1]='\0';
                    if(base.CheckUserExists(User(username)))
                        msg3[0]='1';
                    else
                        msg3[0]='0';
                    bytes_sent=SSL_write(ssl,msg3,1);
                    break;
                }
            case 1 : // File transfer from client to server case 1 and return filepath
                {
                    char msg[4];
                    msg[4]='\0';
                    msg[0]='1';
                    char len[20];
                    bytes_recieved=SSL_read(ssl, len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    std::cout<<size<<std::endl;
                    char filename[size];
                    bytes_recieved=SSL_read(ssl,filename,size);
                    filename[bytes_recieved]='\0';
                    std::cout<<ToStr(filename)<<std::endl;
                    std::string name=FileName(ToStr(filename));
                    std::string filepath=ToStr(filename).substr(0,strlen(filename)-name.size());
                    std::cout<<"Filepath:"<<filepath<<std::endl;
                    std::cout<<"Filename:"<<name<<std::endl;
                    boost::filesystem::path dir(filepath);
                    if(!(boost::filesystem::exists(dir)))
                    {
                        std::cout<<"Directory Doesn't Exists"<<std::endl;
                        if (boost::filesystem::create_directories(dir))
                            std::cout << "Directory Successfully Created !" << std::endl;
                    }

                    bytes_recieved=SSL_read(ssl, len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    std::cout<<size<<std::endl;
                    
                    std::string data="";
                    int packetCounter=0;
                    int dataLen=0;

                    std::ofstream out(filepath+name);
                    std::cout<<"FileCreated"<<std::endl;

                    while(1)
                    {
                        char file[SIZE];
                        bytes_recieved=SSL_read(ssl, file,SIZE);
                        file[bytes_recieved]='\0';
                        std::cout<<bytes_recieved<<std::endl;
                        packetCounter++;
                        for(int i=0;i<bytes_recieved && dataLen<size;i++)
                        {
                            data+=file[i];
                            dataLen++;
                        }
                        out << data;
                        data="";
                        std::cout<<"recieved "<<packetCounter<<std::endl;
                        SSL_write(ssl, msg,4);
                        std::cout<<"conf sent\n";    
                        if(/*bytes_recieved<=0*/ dataLen==size)
                        {
                            std::cout<<"breaking now"<<std::endl;
                            out.close();
                            break;
                        }
                        
                    }
                    std::cout<<"Out of loop\n";
                    out.close();

                    std::string location="/home/skipper/Desktop/DeadDropServer/";
                    std::vector< std::pair<std::string, int> > files=GetVectorFiles(location);
                    std::string path="";
                    std::string pathReturn=filepath+name;
                    for(int i=0;i<files.size();i++)
                    {
                        path=files[i].first;
                        if(path.compare(filepath+name)==0)
                            continue;
                        if(path.find("/.data/")!=std::string::npos)
                            continue;
                        if(CompFiles(filepath+name,path))
                        {
                            pathReturn=path;
                            break;
                        }
                    }
                    if(pathReturn.compare(filepath+name)!=0)
                    {
                        if(boost::filesystem::exists(filepath+name))
                        {
                            boost::filesystem::remove(filepath+name);
                            std::cout<<"Deleted"<<std::endl;
                        }
                    }
                    std::cout<<pathReturn<<std::endl;
                    char size1[20];
                    sprintf(size1,"%lld",(long long)pathReturn.size());
                    bytes_sent=SSL_write(ssl, size1,20);
                    char* filepath2=ToArr(pathReturn);
                    bytes_sent=SSL_write(ssl,filepath2,pathReturn.size());
                    std::cout<<"file sent"<<std::endl;
                    break;
                }
            case 2: //File transfer from server to client case 2
                {
                    char msg[4];
                    msg[4]='\0';
                    msg[0]='1';
                    char len[20];
                    bytes_recieved=SSL_read(ssl, len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    std::cout<<size<<std::endl;
                    char filename[size];
                    bytes_recieved=SSL_read(ssl,filename,size);
                    filename[bytes_recieved]='\0';
                    std::cout<<ToStr(filename)<<std::endl;
                    std::string name=FileName(ToStr(filename));
                    std::string filepath=ToStr(filename).substr(0,strlen(filename)-name.size());
                    std::cout<<"Filepath:"<<filepath<<std::endl;
                    boost::filesystem::path dir(filepath);
                    std::cout<<"Filename:"<<name<<std::endl;
                    // if(!(boost::filesystem::exists(dir)))
                    // {
                    //     std::cout<<"Directory Doesn't Exists"<<std::endl;
                    //     if (boost::filesystem::create_directories(dir))
                    //         std::cout << "Directory Successfully Created !" << std::endl;
                    // }
                    std::cout<<"Dir Created"<<std::endl;
                    //filereading-> stored in ans
                    std::string loc=filepath+name;
                    std::cout<<loc<<std::endl;
                    std::ifstream ifs(loc);
                    std::cout<<"Dir Created"<<std::endl;
                    ifs.seekg(0, std::ios::end);
                    std::cout<<"Dir Created"<<std::endl;
                    std::ifstream::pos_type pos = ifs.tellg();
                    std::cout<<"Dir Created"<<std::endl;
                    std::vector<char>  ans(pos);
                    std::cout<<"Dir Created"<<std::endl;
                    ifs.seekg(0, std::ios::beg);
                    std::cout<<"Dir Created"<<std::endl;
                    ifs.read(&ans[0], pos);
                    std::cout<<"Dir Created"<<std::endl;
                    

                    std::cout<<"File read Successfully\n";
                    char size1[20];
                    size1[20]='\0';
                    sprintf(size1,"%lld",(long long)ans.size());
                    for(int i=0;i<strlen(size1);i++)
                    {
                        std::cout<<size1[i]<<std::endl;
                    }
                    bytes_sent=SSL_write(ssl, size1,20);
                    std::cout<<"Size:"<<bytes_sent<<std::endl;
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
                        file2[SIZE]='\0';
                        std::cout<<"SSL_writing"<<std::endl;
                        SSL_write(ssl, file2,SIZE);
                        packetCounter++;
                        std::cout<<"sent "<<packetCounter<<std::endl;

                        bytes_recieved=SSL_read(ssl, msg,4);
                        msg[bytes_recieved]='\0';
                        std::cout<<"conf SSL_read\n";
                        if(dataLen==ans.size())
                        {
                            break;
                        }
                
                    }
                    std::vector<char> tempVector;
                    ans.swap(tempVector);
                    std::cout<<"file sent"<<std::endl;

                    break;
                }
            case 6: // delete file on server
                {
                    char len[20];
                    bytes_recieved=SSL_read(ssl, len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    std::cout<<size<<std::endl;
                    char filename[size];
                    bytes_recieved=SSL_read(ssl,filename,size);
                    filename[bytes_recieved]='\0';
                    boost::filesystem::wpath file(ToStr(filename));
                    if(boost::filesystem::exists(file))
                        boost::filesystem::remove(file);
                    break;
                }
            case 10: //logout
                {
                    close(acceptID);
                    SSL_free(ssl);         /* release SSL state */
                    quit=true;
                    int i=0;
                    for(i=0;i<usersLog.size();i++)
                    {
                        if(usersLog[i].compare(userID)==0)
                            break;
                    }
                    usersLog.erase (usersLog.begin()+i);
                    break;
                }
            case 11: // send serverlist
                {
                    char msg[4];
                    msg[0]='1';
                    msg[4]='\0';
                    char len[20];
                    bytes_recieved=SSL_read(ssl, len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    std::cout<<size<<std::endl;
                    char filename[size];
                    bytes_recieved=SSL_read(ssl,filename,size);
                    filename[bytes_recieved]='\0';
                    std::cout<<ToStr(filename)<<std::endl;

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
                        std::string name=FileName(ToStr(filename)+temp);
                        std::string filepath=(ToStr(filename)+temp).substr(0,strlen(filename)-name.size());
                        std::cout<<"Filepath:"<<filepath<<std::endl;
                        std::cout<<"Filename:"<<name<<std::endl;
                        boost::filesystem::path dir(filepath);
                        if(!(boost::filesystem::exists(dir)))
                        {
                            std::cout<<"Directory Doesn't Exists"<<std::endl;
                            if (boost::filesystem::create_directory(dir))
                                std::cout << "Directory Successfully Created !" << std::endl;
                        }

                        //filereading(all parts)-> stored in ans
                        int part=0;
                        std::string p=std::to_string(part);
                        std::vector<char>  ans;
                        int counter=0;

                        while(1)
                        {   std::string s=filepath+name+p;
                            std::ifstream ifs(s, std::ios::binary|std::ios::ate);
                            std::cout<<ifs.is_open()<<std::endl;
                            if(!ifs.is_open())
                            {
                                ifs.close();
                                break;
                            }
                            std::ifstream::pos_type pos = ifs.tellg();
                            ans.resize(ans.size()+pos);
                            ifs.seekg(0, std::ios::beg);
                            ifs.read(&ans[counter], pos);
                            part++;
                            counter=ans.size();
                            p=std::to_string(part);
                        }

                        std::cout<<"All files read Successfully\n";
                        char size1[20];
                        size1[20]='\0';
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
                            file2[SIZE]='\0';
                            std::cout<<"SSL_writing"<<std::endl;
                            SSL_write(ssl, file2,SIZE);
                            packetCounter++;
                            std::cout<<"sent "<<packetCounter<<std::endl;

                            bytes_recieved=SSL_read(ssl, msg,4);
                            msg[bytes_recieved]='\0';
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
                    break;
                }
            case 12: // Receive a random string
                {
                    char len[20];
                    bytes_recieved=SSL_read(ssl, len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    std::cout<<size<<std::endl;
                    char data[size];
                    bytes_recieved=SSL_read(ssl,data,size);
                    data[bytes_recieved]='\0';
                    std::cout<<ToStr(data)<<std::endl;
                    std::string Location = ToStr(data);
                    FileHistory ServerFiles = GetFilesOnDisc(Location);
                    ServerFiles.StoreToFileBase(Location+"/sehistory.txt");
                    // Refresh the folder files 
                    // Store the files

                    break;
                }
            case 13: // Receive serverlist
                {
                    char msg[4];
                    msg[0]='1';
                    msg[4]='\0';
                    char len[20];
                    bytes_recieved=SSL_read(ssl, len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    std::cout<<size<<std::endl;
                    char filename[size];
                    bytes_recieved=SSL_read(ssl,filename,size);
                    filename[bytes_recieved]='\0';
                    std::cout<<ToStr(filename)<<std::endl;
                    int fileCount=0;
                    std::string temp3=ToStr(filename);
                    std::string temp1;
                    while(fileCount<3)
                    {
                        bytes_recieved=SSL_read(ssl, len,20);    
                        len[bytes_recieved]='\0';
                        long long size=atoll(len);
                        std::cout<<size<<std::endl;
                        
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
                        std::string data="";
                        int packetCounter=0;
                        int dataLen=0;
                        int partCounter=0;
                        std::string part=std::to_string(partCounter);
                        int joined=0;
                        std::cout<<"FileCreated"<<std::endl;
                        while(1)
                        {
                            std::ofstream out(filepath2+name+part);
                            while(joined<JOIN)
                            {
                                char file[SIZE];
                                bytes_recieved=SSL_read(ssl, file,SIZE);
                                file[bytes_recieved]='\0';
                                std::cout<<bytes_recieved<<std::endl;
                                packetCounter++;
                                for(int i=0;i<bytes_recieved && dataLen<size;i++)
                                {
                                    data+=file[i];
                                    dataLen++;
                                }
                                out << data;
                                data="";
                                joined++;
                                std::cout<<"recieved "<<packetCounter<<std::endl;
                                SSL_write(ssl, msg,4);
                                std::cout<<"conf sent\n";    
                                if(/*bytes_recieved<=0*/ dataLen==size)
                                {
                                    std::cout<<"breaking now"<<std::endl;
                                    out.close();
                                    goto NEXT2;
                                }
                            }
                            std::cout<<"Out of loop\n";
                            out.close();
                            joined=0;
                            partCounter++;
                            part=std::to_string(partCounter);
                        }
                        NEXT2:std::cout<<"file sent"<<std::endl;
                        fileCount++;
                    }
                    break;
                }
            case 14 : // File transfer from client to server case 1 no path returned
                { 
                    char msg[4];
                    msg[4]='\0';
                    msg[0]='1';
                    char len[20];
                    bytes_recieved=SSL_read(ssl, len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    std::cout<<size<<std::endl;
                    char filename[size];
                    bytes_recieved=SSL_read(ssl,filename,size);
                    filename[bytes_recieved]='\0';
                    std::cout<<ToStr(filename)<<std::endl;
                    std::string name=FileName(ToStr(filename));
                    std::string filepath=ToStr(filename).substr(0,strlen(filename)-name.size());
                    std::cout<<"Filepath:"<<filepath<<std::endl;
                    std::cout<<"Filename:"<<name<<std::endl;
                    boost::filesystem::path dir(filepath);
                    if(!(boost::filesystem::exists(dir)))
                    {
                        std::cout<<"Directory Doesn't Exists"<<std::endl;
                        if (boost::filesystem::create_directories(dir))
                            std::cout << "Directory Successfully Created !" << std::endl;
                    }

                    bytes_recieved=SSL_read(ssl, len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    std::cout<<size<<std::endl;
                    
                    std::string data="";
                    int packetCounter=0;
                    int dataLen=0;

                    std::ofstream out(filepath+name);
                    std::cout<<"FileCreated"<<std::endl;

                    while(1)
                    {
                        char file[SIZE];
                        bytes_recieved=SSL_read(ssl, file,SIZE);
                        file[bytes_recieved]='\0';
                        std::cout<<bytes_recieved<<std::endl;
                        packetCounter++;
                        for(int i=0;i<bytes_recieved && dataLen<size;i++)
                        {
                            data+=file[i];
                            dataLen++;
                        }
                        out << data;
                        data="";
                        std::cout<<"recieved "<<packetCounter<<std::endl;
                        SSL_write(ssl, msg,4);
                        std::cout<<"conf sent\n";    
                        if(/*bytes_recieved<=0*/ dataLen==size)
                        {
                            std::cout<<"breaking now"<<std::endl;
                            out.close();
                            break;
                        }
                        
                    }
                    std::cout<<"Out of loop\n";
                    out.close();
                    std::cout<<"file sent"<<std::endl;
                    break;
                }
            case 15: //Get server files path of a user.
                {
                    char len[20];
                    bytes_recieved=SSL_read(ssl, len,20);
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    std::cout<<size<<std::endl;
                    char filename[size];
                    bytes_recieved=SSL_read(ssl,filename,size);
                    filename[bytes_recieved]='\0';
                    std::string name=FileName(ToStr(filename));
                    std::cout<<name<<std::endl;
                    std::vector<std::string> files=GetFiles("/home/skipper/Desktop/DeadDropServer/"+name+"/");
                    for(int i=0;i<files.size();i++)
                    {
                        files[i]=files[i].substr(36);
                        int j=0;
                        int k=0;
                        while(j<2)
                        {
                            if(files[i][k]=='/')  
                                j++;
                            k++;
                        }
                        files[i].insert(k,".temp/");
                        std::cout<<files[i]<<std::endl;
                    }
                    std::ofstream outfile("/home/skipper/Desktop/DeadDropServer/"+name+"/.data/serverfiles.txt");
                    int index;
                    for(index=0;index<files.size();index++)
                    {
                        std::cout<<files[index]<<std::endl;
                        outfile<<files[index]<<"\n";
                    }
                    outfile.close();
                    std::cout<<"Done"<<std::endl;
                    break;
                }
            default:
                {
                    break;
                }
        }
        if(quit)
        {
            break;
        }
    }
    }
    std::cout<<"Ending connection with "<<acceptID<<std::endl;
}

int main(int argc, char** argv)
{
    if(argc<2)
    {
        std::cout<<"Error. Usage: ./tserver portnumber\n";
    }
    else
    {
        if(!isRoot())
        {
            printf("This program must be run as root/sudo user!!");
            exit(0);
        }

        ctx=InitSSL();

        base.LoadFromFile("Database.txt");

        int status;                      // Contains the status of the server
        int bindStatus;                  // Contains the status of the socket bind
        
        memset(&host_info, 0, sizeof host_info);

        std::cout << "Setting up the structures..."  << std::endl;
    
        host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
        host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP.
        host_info.ai_flags = AI_PASSIVE;     // IP Wildcard
    
        status = getaddrinfo(NULL, argv[1], &host_info, &host_info_list); 
        if (status != 0)  
            std::cout << "Getaddrinfo error" << gai_strerror(status)<<std::endl ;
    
        std::cout << "Creating a socket..."  << std::endl;
    
        sockID = socket(host_info_list->ai_family, host_info_list->ai_socktype,host_info_list->ai_protocol); // Getting info on the server
        if (sockID == -1)  
            std::cout << "Socket error \n" ;

        std::cout << "Binding socket..."  << std::endl;
        
        int buffs=BUFFSIZE;
        setsockopt(sockID, SOL_SOCKET, SO_RCVBUF, &buffs, sizeof(buffs));                   // Setting the maximum buffer size of the sockets
        status = setsockopt(sockID, SOL_SOCKET, SO_REUSEPORT, &bindStatus, sizeof(int));    // Reusuing the port if already in use
        status = bind(sockID, host_info_list->ai_addr, host_info_list->ai_addrlen);         // Binding socket
        if (status == -1)                                                                   // Checking status        
        {
            std::cout<<"Reuse port Error : "<< strerror(errno)<<std::endl;
            close(sockID);                                                                  // Closing and opening the socket again.
            sockID = socket(host_info_list->ai_family, host_info_list->ai_socktype,host_info_list->ai_protocol);
            std::cout << "Binding socket again..."  << std::endl;
            setsockopt(sockID, SOL_SOCKET, SO_REUSEPORT, &bindStatus, sizeof(int));
            status=bind(sockID, host_info_list->ai_addr, host_info_list->ai_addrlen);
            std::cout<<status<<std::endl;
        }

        pthread_t inputThread;
        pthread_create(&inputThread,NULL,Input,NULL);
            
        status =  listen(sockID, 5);
        if (status == -1)  
            std::cout << "Listen error" << std::endl ;

        uint32_t htonl(uint32_t hostlong);

        std::vector<pthread_t> threads= std::vector<pthread_t>(THREADS);              /* get new SSL state with context */
        int threadCount=0;
        while(!closeServer)
        {
            long id;
            struct sockaddr_storage their_addr;
            socklen_t addr_size = sizeof(their_addr);
            std::cout<<"Waiting for more clients..."<<std::endl;
            id = accept(sockID, (struct sockaddr *)&their_addr, &addr_size);
            pthread_create(&threads[threadCount],NULL,ClientService,(void *)id);
            threadCount=(threadCount+1)%THREADS;
        }
        std::cout<<"All clients served\n";
           
    }
    std::cout<<"Done!\n";
    return 0;
}
