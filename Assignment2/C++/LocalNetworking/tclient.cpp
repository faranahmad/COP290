#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
/*for sendfile()*/
#include <sys/sendfile.h>
#define SIZE 100000
/*for O_RDONLY*/
#include <fcntl.h>
#include <vector>

using namespace std;


int main(int argc, char** argv)
{
  if(argc<3)
  {
    cout<<"Error. Usage : ./tclient portnumber filename\n";
  }
  else
  {
  int status;
  struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
  struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
  struct sockaddr_in server;
  int sock;
  memset(&host_info, 0, sizeof host_info);

    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

    status = getaddrinfo("127.0.0.1", argv[1], &host_info, &host_info_list);
    if (status != 0)  std::cout << "getaddrinfo error" << gai_strerror(status) ;

    int socketfd ; // The socket descripter
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
                      host_info_list->ai_protocol);
    if (socketfd == -1)  std::cout << "socket error " ;

    int buffsize = 10000000;
    setsockopt(socketfd, SOL_SOCKET, SO_RCVBUF, &buffsize, sizeof(buffsize));
// setsockopt(socketfd, SOL_SOCKET, SO_NOSIGPIPE, &buffsize, sizeof(buffsize));
    std::cout << "Connecting..."  << std::endl;
    status = connect(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  std::cout << "connection error"<<endl; else cout<<"connected\n" ;
   
    uint32_t htonl(uint32_t hostlong);


    //filereading
    ifstream ifs(argv[2], ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();
    std::vector<char>  ans(pos);
    ifs.seekg(0, ios::beg);
    ifs.read(&ans[0], pos);
    //filereading


    char len[20];
    long long s=ans.size();
    // long long s=2189043569;
    cout<<s<<endl;
    sprintf(len,"%lld",s);
    send(socketfd, len,20,  MSG_NOSIGNAL);
    cout<<"\nsize sent"<<endl;
    char msg[4];
    // recv(socketfd, msg,4, 0);
    char *file=new char[ans.size()];
    cout<<"empty char*\n";
    for(int i=0;i<ans.size();i++)
    {
      file[i]=ans[i];
    }
    cout<<"conv to char*"<<endl;
    int j=0;
    int counter=0;
    while(1)
    {
        char *file2=new char[SIZE];
        for(int l=0 ;l<SIZE&&j<ans.size();l++,j++)
        {
            file2[l]=file[j];
        }
        cout<<"sending"<<endl;
        send(socketfd, file2,SIZE, MSG_NOSIGNAL);
        counter++;
        cout<<"sent "<<counter<<endl;

        recv(socketfd, msg,4, 0);
        cout<<"conf recv\n";
        if(j==ans.size())
        {
            for(int z=0;z<SIZE;z++)
             {   file2[z]='\0';}
            send(socketfd, file2,SIZE,MSG_NOSIGNAL);
            break;
        }

    }
    // recv(socketfd, msg,4, 0);
    delete[] file;
    vector<char> tempVector;
    ans.swap(tempVector);
    cout<<"file sent"<<endl;
    freeaddrinfo(host_info_list);
    close(socketfd);
    }
    return 0;
  }