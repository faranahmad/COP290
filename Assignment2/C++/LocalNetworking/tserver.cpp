
#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>     // Needed for closing the sockets
#include "UserBase.h"
#include <fstream>
#define SIZE 100000
using namespace std;
bool isEmpty(char* file)
{
    for(int i=0;i<sizeof(file);i++)
    {
        if(file[i]!='\0')
            return false;
    }
    return true;
}
int main(int argc, char** argv)
{
    if(argc<3)
    {
        cout<<"Error. Usage: ./tserver portnumber extension\n";
    }
    else
    {
    int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

    memset(&host_info, 0, sizeof host_info);

    cout << "Setting up the structs..."  << endl;

    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.
    host_info.ai_flags = AI_PASSIVE;     // IP Wildcard

    status = getaddrinfo(NULL, argv[1], &host_info, &host_info_list);
    if (status != 0)  cout << "getaddrinfo error" << gai_strerror(status)<<endl ;


    cout << "Creating a socket..."  << endl;
    int socketfd ; // The socket descripter
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
                      host_info_list->ai_protocol);
    if (socketfd == -1)  cout << "socket error \n" ;

    cout << "Binding socket..."  << endl;
    int yes = 1;
    int buffsize = 10000000;
    setsockopt(socketfd, SOL_SOCKET, SO_RCVBUF, &buffsize, sizeof(buffsize));
    status = setsockopt(socketfd, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(int));
    status = bind(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  
    {
        cout<<"Reuse port Error : "<< strerror(errno)<<endl;
        close(socketfd);
        socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
                      host_info_list->ai_protocol);
        cout << "Binding socket again..."  << endl;
        setsockopt(socketfd, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(int));
        status=bind(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
        cout<<status<<endl;
    }
    
    cout << "Listening for connections..."  << endl;
    status =  listen(socketfd, 5);
    if (status == -1)  cout << "listen error" << endl ;


    int new_sd;
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    new_sd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);
    if (new_sd == -1)
    {
        cout << "listen error" << endl ;
    }
    else
    {
        cout << "Connection accepted. Using new socketfd : "  <<  new_sd << endl;
    }

    cout << "Waiting to recieve data..."  << endl;
    char len[20];
    int bytes_recieved;
    bytes_recieved=recv(new_sd, len,20,MSG_WAITALL);
    cout<<"size rec\n";
    char msg[4];
    msg[0]='1';
    // send(socketfd, msg,4, 0);
    cout<<bytes_recieved<<endl;
    uint32_t ntohl(uint32_t netlong);
    long long size=atoll(len);
    cout<<size<<endl;
    char *file=new char[SIZE];
    string data="";
    int counter=0;
    int dataLen=0;
    string filename="Anu.";
    for(int i=0;i<sizeof(argv[2]);i++)
    {
        filename+=argv[2][i];
    }
    std::ofstream out(filename);
    cout<<"FileCreated"<<endl;
    while(1)
    {
        bytes_recieved=recv(new_sd, file,SIZE, MSG_WAITALL);
        
        counter++;
        cout<<"recieved "<<counter<<endl;    
        if(isEmpty(file))
        {
            break;
        }
        for(int i=0;i<bytes_recieved && dataLen<size;i++)
        {
            data+=file[i];
            dataLen++;
        }
        out << data;
        data="";
        send(new_sd, msg,4,  MSG_CONFIRM);
        cout<<"conf sent\n";
    }
    
    cout<<"file recv"<<endl;
    
    out.close();
    freeaddrinfo(host_info_list);
    close(socketfd);
    }
    return 0;

}