
#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>     // Needed for closing the sockets
#include "UserBase.h"
using namespace std;
int main()
{
    int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

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
    status = getaddrinfo(NULL, "5599", &host_info, &host_info_list);
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
    bool quit=false;
    UserBase base=UserBase();
    base.LoadFromFile("Database.txt");
    while(true)
    {
        cout << "Waiting to recieve data..."  << endl;
        ssize_t bytes_recieved;
        char incomming_data_buffer[1000];
        bytes_recieved = recv(new_sd, incomming_data_buffer,1000, 0);
        // If no data arrives, the program will just wait here until some data arrives.
        if (bytes_recieved == 0) cout << "host shut down." << endl ;
        if (bytes_recieved == -1)cout << "recieve error!" << endl ;
        cout << bytes_recieved << " bytes recieved :" << endl ;
        incomming_data_buffer[bytes_recieved] = '\0';
        cout << incomming_data_buffer<<endl;

        // char *msg = "thank you.\n";
        // int len;
        // ssize_t bytes_sent;
        // len = strlen(msg);
        // bytes_sent = send(new_sd, msg, len, 0);

        switch(incomming_data_buffer[0])
        {
            case '0':
            {

                cout << "sending back a message..."  << endl;
                char *msg2 = "Adding user....\nEnter Username\n";
                int len2;
                ssize_t bytes_sent2;
                len2 = strlen(msg2);
                bytes_sent2 = send(new_sd, msg2, len2, 0);

                ssize_t bytes_recieved2;
                char incomming_data_buffer2[1000];
                char incomming_data_buffer3[1000];
                bytes_recieved2 = recv(new_sd, incomming_data_buffer2,1000, 0);
                // If no data arrives, the program will just wait here until some data arrives.
                if (bytes_recieved2 == 0) cout << "host shut down." << endl ;
                if (bytes_recieved2 == -1)cout << "recieve error!" << endl ;
                cout << bytes_recieved2 << " bytes recieved :" << endl ;
                incomming_data_buffer2[bytes_recieved2] = '\0';
                cout << incomming_data_buffer2<<endl;
                
                cout << "sending back a message..."  << endl;
                msg2 = "Enter Password\n";
                len2 = strlen(msg2);
                bytes_sent2 = send(new_sd, msg2, len2, 0);

                bytes_recieved2 = recv(new_sd, incomming_data_buffer3,1000, 0);
                // If no data arrives, the program will just wait here until some data arrives.
                if (bytes_recieved2 == 0) cout << "host shut down." << endl ;
                if (bytes_recieved2 == -1)cout << "recieve error!" << endl ;
                cout << bytes_recieved2 << " bytes recieved :" << endl ;
                incomming_data_buffer3[bytes_recieved2] = '\0';
                cout << incomming_data_buffer3<<endl;
                base.InsertUser(User(incomming_data_buffer2,incomming_data_buffer3));
                break;

            } 
            case '3':
            {
                cout << "Stopping server..." << endl;
                base.StoreToFile("Database.txt");
                freeaddrinfo(host_info_list);
                close(new_sd);
                close(socketfd);
                quit=true;
                break;
            }
        }
        if(quit)
        {
            break;
        }
    }



}


// int main()
// {
//     while (true)
//     {
//         main2();
//     }
// }