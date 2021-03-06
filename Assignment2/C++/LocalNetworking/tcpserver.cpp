
#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>     // Needed for closing the sockets
#include "UserBase.h"
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
int main()
{
    int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list;
    struct stat obj;
    int size,filehandle; // Pointer to the to the linked list of host_info's.

    // The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
    // to by hints must contain either 0 or a null pointer, as appropriate." When a struct
    // is created in c++, it will be given a block of memory. This memory is not nessesary
    // empty. Therefor we use the memset function to make sure all fields are NULL.
    memset(&host_info, 0, sizeof host_info);

    cout << "Setting up the structs..."  << endl;

    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.
    host_info.ai_flags = AI_PASSIVE;     // IP Wildcard

    // Now fill up the linked list of host_info structs with google's address information.
    status = getaddrinfo("10.192.10.192", "5569", &host_info, &host_info_list);
    // getaddrinfo returns 0 on succes, or some other value when an error occured.
    // (translated into human readable text by the gai_gai_strerror function).
    if (status != 0)  cout << "getaddrinfo error" << gai_strerror(status)<<endl ;


    cout << "Creating a socket..."  << endl;
    int socketfd ; // The socket descripter
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
                      host_info_list->ai_protocol);
    if (socketfd == -1)  cout << "socket error \n" ;

    cout << "Binding socket..."  << endl;
    // we use to make the setsockopt() function to make sure the port is not in use
    // by a previous execution of our code. (see man page for more information)
    int yes = 1;
    status = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    status = bind(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  
    {
        cout << "bind error" << endl ;
    }
    int reuse;
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
    {
     cout<<"Reuse port Error\n";
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
    stat("temp.txt",&obj);
    size = obj.st_size;
    send(socketfd, &size, sizeof(int),0);
    filehandle = open("temp.txt", O_RDONLY);
    sendfile(socketfd,filehandle,NULL,size);
    // char send_buffer[1000]
    // void* v;
    // cout<<(long)v<<endl;
    // recv(socketfd, &v, 1000, 0);
    // cout<<(long)v<<endl;


}


// int main()
// {
//     while (true)
//     {
//         main2();
//     }
// }