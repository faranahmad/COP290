#include <iostream>
#include <cstring>      
#include <sys/socket.h>     
#include <netdb.h>      
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <vector>

#define SIZE 1000
#define BUFFSIZE 10000000

using namespace std;

std::string toStr(char* arr)  //Convert array of characters to string
{
    std::string ans="";
    for(int i=0;i<strlen(arr)&&arr[i]!='\0';i++)
    {
        ans+=arr[i];
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
  if(argc<3)
  {
    cout<<"Error. Usage : ./tclient ip portnumber\n";
  }
  else
  {
    int status;                      // Contains the status of the server
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
    struct sockaddr_in server;
    int sock;
    memset(&host_info, 0, sizeof host_info);

    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

    status = getaddrinfo(argv[1], argv[2], &host_info, &host_info_list);
    if (status != 0)  
        std::cout << "Getaddrinfo error" << gai_strerror(status) ;

    int sockID ;                        // The socket descripter
    sockID = socket(host_info_list->ai_family, host_info_list->ai_socktype,host_info_list->ai_protocol);
    if (sockID == -1)  
        std::cout << "Socket error " ;

    int buffs = BUFFSIZE;
    setsockopt(sockID, SOL_SOCKET, SO_RCVBUF, &buffs, sizeof(buffs));
    std::cout << "Connecting..."  << std::endl;
    status = connect(sockID, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  
        std::cout << "Connection error!"<<endl; 
    else std::cout<<"Connected\n";
   
    uint32_t htonl(uint32_t hostlong);


    //filereading
    // ifstream ifs(argv[3], ios::binary|ios::ate);
    // ifstream::pos_type pos = ifs.tellg();
    // std::vector<char>  ans(pos);
    // ifs.seekg(0, ios::beg);
    // ifs.read(&ans[0], pos);
    //filereading

    bool quit =false;

    while(!quit)
    {
        std::cout<<"Choose from the following.\n";
        std::cout<<"1.Add User\n";
        std::cout<<"2.Verifying Credentials\n";
        std::cout<<"3.User Exist\n";
        std::cout<<"4.Quit\n";
        std::string temp;
        int bytes_recieved;
        int bytes_sent;
        int inp;
        cin>>inp;
        char num[2];
        sprintf(num,"%lld",(long long)inp);
        bytes_sent=send(sockID, num,2, MSG_NOSIGNAL);
        switch(inp)
        {
            case 1:
            {
                // bytes_recieved=recv(sockID,msg,SIZE,MSG_WAITALL);
                // // std::cout<<strerror(errno)<<std::endl;
                // if(bytes_recieved)
                // {
                //     temp=toStr(msg);
                //     std::cout<<temp<<endl;
                //     cin>>temp;
                //     msg=toArr(temp);
                //     for(int i=0;i<strlen(msg);i++)
                //     {
                //         std::cout<<msg[i];
                //     }
                //     std::cout<<"\n";
                //     bytes_sent=send(sockID,msg,SIZE,MSG_NOSIGNAL);
                //     std::cout<<bytes_sent<<std::endl;
                //     if(bytes_sent)
                //     {
                //         bytes_recieved=recv(sockID,msg,SIZE,MSG_WAITALL);
                //         temp=toStr(msg);
                //         cout<<temp;
                //         if(bytes_recieved)
                //         {
                //             cin>>temp;
                //             msg=toArr(temp);
                //             bytes_sent=send(sockID,msg,SIZE,MSG_NOSIGNAL);
                //             if(bytes_sent)
                //             {
                //                 bytes_recieved=recv(sockID,msg,SIZE,MSG_WAITALL);
                //                 temp=toStr(msg);
                //                 cout<<temp;
                //             }
                //         }

                //     }

                // }
                std::cout<<"Enter Username\n";
                cin>>temp;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp.size());
                char* msg1=toArr(temp);
                std::cout<<temp.size()<<"   "<<strlen(msg1)<<std::endl;
                bytes_sent=send(sockID, size1,20,  MSG_NOSIGNAL);
                bytes_sent=send(sockID,msg1,temp.size(),MSG_NOSIGNAL);
                std::cout<<"Enter Password\n";
                cin>>temp;
                char size2[20];
                sprintf(size2,"%lld",(long long)temp.size());
                char* msg2=toArr(temp);
                bytes_sent=send(sockID, size2,20,  MSG_NOSIGNAL);
                bytes_sent=send(sockID,msg2,temp.size(),MSG_NOSIGNAL);
                std::cout<<"User Successfully added!\n";
                break;
            }
            case 2:
                {
                    std::cout<<"Enter Username\n";
                    cin>>temp;
                    char size1[20];
                    sprintf(size1,"%lld",(long long)temp.size());
                    char* msg1=toArr(temp);
                    bytes_sent=send(sockID, size1,20,  MSG_NOSIGNAL);
                    bytes_sent=send(sockID,msg1,temp.size(),MSG_NOSIGNAL);
                    std::cout<<"Enter Password\n";
                    cin>>temp;
                    char size2[20];
                    sprintf(size2,"%lld",(long long)temp.size());
                    char* msg2=toArr(temp);
                    bytes_sent=send(sockID, size2,20,  MSG_NOSIGNAL);
                    bytes_sent=send(sockID,msg2,temp.size(),MSG_NOSIGNAL);
                    char msg3[1];
                    bytes_recieved=recv(sockID,msg3,1,MSG_WAITALL);
                    msg3[bytes_recieved]='\0';
                    if(msg3[0]=='1')
                        std::cout<<"Successfully logged in\n";
                    else
                        std::cout<<"Sorry. Please try again\n";
                    break;
                }
            case 3:
            {
                std::cout<<"Enter Username\n";
                cin>>temp;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp.size());
                char* msg1=toArr(temp);
                bytes_sent=send(sockID, size1,20,  MSG_NOSIGNAL);
                bytes_sent=send(sockID,msg1,temp.size(),MSG_NOSIGNAL);
                char msg3[1];
                bytes_recieved=recv(sockID,msg3,1,MSG_WAITALL);
                msg3[bytes_recieved]='\0';
                if(msg3[0]=='1')
                    std::cout<<"User Exists\n";
                else
                    std::cout<<"User Does not exist\n";
                break;
            }
            default:
                {
                    quit=true;
                    freeaddrinfo(host_info_list);
                    close(sockID);
                    break;
                }
        }
    }
    std::cout<<"ThankYou!\n";
    return 0;
  }
}