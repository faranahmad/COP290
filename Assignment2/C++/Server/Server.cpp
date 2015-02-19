#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>     // Needed for closing the sockets
#include "UserBase.h"   
#include <fstream>
#include <string>

#define SIZE 1000
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
                        // msg = toArr("Adding user....\nEnter Username\n");
                        // bytes_sent=send(acceptID, msg, SIZE, MSG_NOSIGNAL);
                        // if(bytes_sent)
                        // {
                        //     std::cout<<"Adding user...\n";
                        //     char* cred=new char[SIZE];
                        //     bytes_recieved=recv(acceptID, cred,SIZE, MSG_WAITALL);
                        //     if(bytes_recieved>0)
                        //     {
                        //         cred[bytes_recieved]='\0';
                        //         std::string username=toStr(cred);
                        //         std::cout<<"Username:"<<username<<std::endl; //Username
    
                        //         msg = toArr("Enter Password\n");
                        //         bytes_sent=send(acceptID, msg, SIZE, MSG_NOSIGNAL);
                        //         if(bytes_sent>0)
                        //         {
                        //             bytes_recieved=recv(acceptID, cred,SIZE, MSG_WAITALL);
                        //             cred[bytes_recieved]='\0';
                        //             std::cout<<bytes_recieved<<std::endl;
                        //             if(bytes_recieved>0)
                        //             {
                        //                 std::cout<<"Password:"<<toStr(cred)<<std::endl; //Password
                        //                 base.InsertUser(User(username,toStr(cred)));
                                    
                        //                 msg = toArr("User successfully added\n");
                        //                 bytes_sent=send(acceptID, msg, SIZE, MSG_NOSIGNAL);
                        //             }
                        //        }
                        //     }
                        //     delete[] cred;   
                        // }
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

                // case 2: // Verifying Credentials
                //     {
                //         msg=toArr("Verifying Credentials...\nEnter Username\n");
                //         bytes_sent=send(acceptID, msg, SIZE, MSG_NOSIGNAL);
                //         if(bytes_sent>0)
                //         {
                //             char* cred=new char[SIZE];
                //             bytes_recieved=recv(acceptID, cred,SIZE, MSG_WAITALL);
                //             if(bytes_recieved>0)
                //             {
                //                 cred[bytes_recieved]='\0';
                //                 std::string username=toStr(cred);
                //                 std::cout<<"Username:"<<username<<std::endl; //Username
    
                //                 msg = toArr("Enter Password\n");
                //                 bytes_sent=send(acceptID, msg, SIZE, MSG_NOSIGNAL);
                //                 if(bytes_sent>0)
                //                 {
                //                     bytes_recieved=recv(acceptID, cred,SIZE, MSG_WAITALL);
                //                     cred[bytes_recieved]='\0';
                //                     if(bytes_recieved>0)
                //                     {
                //                         std::cout<<"Password:"<<toStr(cred)<<std::endl; //Password
                //                         if(base.VerifyUserCredentials(User(username,toStr(cred))))
                //                         {
                //                             msg = toArr("1");
                //                             bytes_sent=send(acceptID, msg, SIZE, MSG_NOSIGNAL);
                //                         }
                //                         else
                //                         {
                //                             msg = toArr("0");
                //                             bytes_sent=send(acceptID, msg, SIZE, MSG_NOSIGNAL);
                //                         }
                //                     }
                //                 }
                //             }
                //         }
                //         break;
                //     }
                // case 3: // Exists user.
                //     {
                //         msg=toArr("Verifying username...\nEnter Username\n");
                //         bytes_sent=send(acceptID, msg, SIZE, MSG_NOSIGNAL);
                //         if(bytes_sent>0)
                //         {
                //             char* cred=new char[SIZE];
                //             bytes_recieved=recv(acceptID, cred,SIZE, MSG_WAITALL);
                //             if(bytes_recieved>0)
                //             {
                //                 cred[bytes_recieved]='\0';
                //                 std::string username=toStr(cred);
                //                 std::cout<<"Username:"<<username<<std::endl; //Username
    
                //                 if(base.CheckUserExists(User(username,toStr(cred))))
                //                 {
                //                     msg = toArr("1");
                //                     bytes_sent=send(acceptID, msg, SIZE, MSG_NOSIGNAL);
                //                 }
                //                 else
                //                 {
                //                     msg = toArr("0");
                //                     bytes_sent=send(acceptID, msg, SIZE, MSG_NOSIGNAL);
                //                 }
                                
                //             }
                //         }
                //         break;
                //     }
                case 2:
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
                case 3:
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
                case 4:
                {

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
