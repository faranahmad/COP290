#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>     // Needed for closing the sockets
#include "UserBase.h"   
#include <fstream>
#include <string>
#include <vector>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem.hpp>

#define SIZE 100000
#define JOIN 100
#define BUFFSIZE 10000000

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

char* toArr(std::string str)  //Convert string to array of character
{
    char* ans=new char[str.size()];
    for(int i=0;i<str.size();i++)
    {
        ans[i]=str[i];
    }
    return ans;
}
int main(int argc, char** argv)
{
    if(argc<2)
    {
        std::cout<<"Error. Usage: ./tserver portnumber\n";
    }
    else
    {
        int status;                      // Contains the status of the server
        int bindStatus;                  // Contains the status of the socket bind
        struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
        struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
    
        memset(&host_info, 0, sizeof host_info);
        
        UserBase base=UserBase();        // Loading the database of users.
        base.LoadFromFile("Database.txt");

        bool quit=false;

        std::cout << "Setting up the structures..."  << std::endl;
    
        host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
        host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP.
        host_info.ai_flags = AI_PASSIVE;     // IP Wildcard
    
        status = getaddrinfo(NULL, argv[1], &host_info, &host_info_list); 
        if (status != 0)  
            std::cout << "Getaddrinfo error" << gai_strerror(status)<<std::endl ;
    
        std::cout << "Creating a socket..."  << std::endl;
    
        int sockID ;                         // The socket descripter
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
            
        std::cout << "Waiting for connections..."  << std::endl;                          // Waiting for connections
        status =  listen(sockID, 5);
        if (status == -1)  
            std::cout << "Listen error" << std::endl ;


        int acceptID;                                                                     // Accepting connection
        struct sockaddr_storage their_addr;
        socklen_t addr_size = sizeof(their_addr);
        acceptID = accept(sockID, (struct sockaddr *)&their_addr, &addr_size);
        if (acceptID == -1)
        {
            std::cout << "Listen error" << std::endl ;
        }
        else
        {
            std::cout << "Connection accepted. Using new sockID : "  <<  acceptID << std::endl;
        }
        uint32_t htonl(uint32_t hostlong);


        while(!quit)
        {
            std::cout << "Waiting to recieve data..."  << std::endl;
            char command[2];
            int bytes_recieved;
            int bytes_sent;
            long long size;
            bytes_recieved=recv(acceptID, command,2,MSG_WAITALL);
            command[bytes_recieved]='\0';
            std::cout<<"Command recieved "<<atoi(command)<<std::endl;
            switch(atoi(command))
            {
                case 1: // Adding username
                    {
                        char len[20];
                        bytes_recieved=recv(acceptID,len,20,MSG_WAITALL);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        char msg1[size];
                        bytes_recieved=recv(acceptID,msg1,size,MSG_WAITALL);
                        msg1[bytes_recieved]='\0';
                        std::string username=toStr(msg1);
                        std::cout<<username<<std::endl;
                        bytes_recieved=recv(acceptID,len,20,MSG_WAITALL);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        char msg2[size];
                        bytes_recieved=recv(acceptID,msg2,size,MSG_WAITALL);
                        msg2[bytes_recieved]='\0';
                        base.InsertUser(User(username,toStr(msg2)));
                        base.StoreToFile("Database.txt");
                        std::cout<<toStr(msg2)<<std::endl;
                        break;
                    }
                case 2: // Verifying
                    {
                        std::cout<<"Case2\n";
                        char len[20];
                        bytes_recieved=recv(acceptID,len,20,MSG_WAITALL);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        char msg1[size];
                        bytes_recieved=recv(acceptID,msg1,size,MSG_WAITALL);
                        msg1[bytes_recieved]='\0';
                        std::string username=toStr(msg1);
                        std::cout<<username<<std::endl;
                        bytes_recieved=recv(acceptID,len,20,MSG_WAITALL);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        char msg2[size];
                        bytes_recieved=recv(acceptID,msg2,size,MSG_WAITALL);
                        msg2[bytes_recieved]='\0';
                        char msg3[1];
                        if(base.VerifyUserCredentials(User(username,toStr(msg2))))
                            msg3[0]='1';
                        else
                            msg3[0]='0';
                        bytes_sent=send(acceptID,msg3,1,MSG_NOSIGNAL);
                        break;
                    }
                case 3: // Exist
                    {
                        std::cout<<"Case3\n";
                        char len[20];
                        bytes_recieved=recv(acceptID,len,20,MSG_WAITALL);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        char msg1[size];
                        bytes_recieved=recv(acceptID,msg1,size,MSG_WAITALL);
                        msg1[bytes_recieved]='\0';
                        std::string username=toStr(msg1);
                        std::cout<<username<<std::endl;
                        char msg3[1];
                        if(base.CheckUserExists(User(username)))
                            msg3[0]='1';
                        else
                            msg3[0]='0';
                        bytes_sent=send(acceptID,msg3,1,MSG_NOSIGNAL);
                        break;
                    }
                case 4: // File transfer from client to server
                    {
                        char msg[4];
                        msg[0]='1';
                        char len[20];
                        bytes_recieved=recv(acceptID, len,20,MSG_WAITALL);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        std::cout<<size<<std::endl;
                        char filename[size];
                        bytes_recieved=recv(acceptID,filename,size,MSG_WAITALL);
                        filename[bytes_recieved]='\0';
                        std::cout<<toStr(filename)<<std::endl;
                        std::string name=FileName(toStr(filename));
                        std::string filepath=toStr(filename).substr(0,strlen(filename)-name.size());
                        std::cout<<"Filepath:"<<filepath<<std::endl;
                        std::cout<<"Filename:"<<name<<std::endl;
                        boost::filesystem::path dir(filepath);
                        if(!(boost::filesystem::exists(dir)))
                        {
                            std::cout<<"Directory Doesn't Exists"<<std::endl;
                            if (boost::filesystem::create_directory(dir))
                                std::cout << "Directory Successfully Created !" << std::endl;
                        }

                        bytes_recieved=recv(acceptID, len,20,MSG_WAITALL);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        std::cout<<size<<std::endl;
                        
                        std::string data="";
                        int packetCounter=0;
                        int dataLen=0;
                        int partCounter=0;
                        std::string part=std::to_string(partCounter);
                        int joined=0;
                        std::cout<<"FileCreated"<<std::endl;
                        while(1)
                        {
                            std::ofstream out(filepath+name+part);
                            while(joined<JOIN)
                            {
                                char file[SIZE];
                                bytes_recieved=recv(acceptID, file,SIZE, MSG_WAITALL);
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
                                send(acceptID, msg,4,  MSG_NOSIGNAL);
                                std::cout<<"conf sent\n";    
                                if(/*bytes_recieved<=0*/ dataLen==size)
                                {
                                    std::cout<<"breaking now"<<std::endl;
                                    out.close();
                                    goto NEXT;
                                }
                            }
                            std::cout<<"Out of loop\n";
                            out.close();
                            joined=0;
                            partCounter++;
                            part=std::to_string(partCounter);
                        }
                        NEXT:std::cout<<"file recv"<<std::endl;
                        break;
                    }
                case 5: //File transfer from server client
                    {
                        char msg[4];
                        msg[0]='1';
                        char len[20];
                        bytes_recieved=recv(acceptID, len,20,MSG_WAITALL);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        std::cout<<size<<std::endl;
                        char filename[size];
                        bytes_recieved=recv(acceptID,filename,size,MSG_WAITALL);
                        filename[bytes_recieved]='\0';
                        std::cout<<toStr(filename)<<std::endl;
                        std::string name=FileName(toStr(filename));
                        std::string filepath=toStr(filename).substr(0,strlen(filename)-name.size());
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
                        sprintf(size1,"%lld",(long long)ans.size());
                        bytes_sent=send(acceptID, size1,20,  MSG_NOSIGNAL);
                        std::cout<<"Initiating sending protocol\n";

                        int dataLen=0;
                        int packetCounter=0;
                        while(1)
                        {
                            char *file2=new char[SIZE];
                            for(int l=0 ;l<SIZE&&dataLen<ans.size();l++,dataLen++)
                            {
                                file2[l]=ans[dataLen];
                            }
                            std::cout<<"sending"<<std::endl;
                            send(acceptID, file2,SIZE, MSG_NOSIGNAL);
                            packetCounter++;
                            std::cout<<"sent "<<packetCounter<<std::endl;
    
                            recv(acceptID, msg,4,MSG_WAITALL);
                            std::cout<<"conf recv\n";
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
                default:
                    {
                        quit=true;
                        break;
                    }
            }
            if(quit)
            {
                freeaddrinfo(host_info_list);
                close(acceptID);
                close(sockID);
                break;
            }
        }
    }
    std::cout<<"Done!\n";
    return 0;
}
