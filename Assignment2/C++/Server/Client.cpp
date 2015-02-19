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

#define SIZE 100000
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


    bool quit =false;

    while(!quit)
    {
        std::cout<<"Choose from the following.\n";
        std::cout<<"1.Add User\n";
        std::cout<<"2.Verifying Credentials\n";
        std::cout<<"3.User Exist\n";
        std::cout<<"4.File transfer from client to server\n";
        std::cout<<"5.Quit\n";
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
            case 4:
                {
                    std::string temp1;
                    std::string temp2;
                    std::cout<<"Enter client address\n";
                    cin>>temp1;
                    std::cout<<"Enter server address\n";
                    cin>>temp2;

                    //filereading
                    ifstream ifs(temp1, ios::binary|ios::ate);
                    ifstream::pos_type pos = ifs.tellg();
                    std::vector<char>  ans(pos);
                    ifs.seekg(0, ios::beg);
                    ifs.read(&ans[0], pos);

                    char msg[4];
                    char size1[20];
                    sprintf(size1,"%lld",(long long)temp2.size());
                    bytes_sent=send(sockID, size1,20,  MSG_NOSIGNAL);
                    char* filepath=toArr(temp2);
                    bytes_sent=send(sockID,filepath,temp2.size(),MSG_NOSIGNAL);
                    
                    char size2[20];
                    sprintf(size2,"%lld",(long long)ans.size());
                    bytes_sent=send(sockID, size2,20,  MSG_NOSIGNAL);

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
                        send(sockID, file2,SIZE, MSG_NOSIGNAL);
                        packetCounter++;
                        std::cout<<"sent "<<packetCounter<<std::endl;

                        recv(sockID, msg,4,MSG_WAITALL);
                        std::cout<<"conf recv\n";
                        if(dataLen==ans.size())
                        {
                            // char* file3;
                            // send(sockID, file2,0,MSG_NOSIGNAL);
                            break;
                        }
                
                    }
                    vector<char> tempVector;
                    ans.swap(tempVector);
                    cout<<"file sent"<<endl;
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