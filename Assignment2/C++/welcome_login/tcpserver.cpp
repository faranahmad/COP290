
#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>     // Needed for closing the sockets
#include "UserBase.h"
using namespace std;
int main(int argc, char* argv[])
{
    if(argc<2)
    {
        std::cout<<"Error. Usage: ./a.out portnumber"
    }
    else
    {
        int status;                      // Status of the server.
        struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
        struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

        memset(&host_info, 0, sizeof host_info);

        bool quit=false;
        UserBase base=UserBase();
        base.LoadFromFile("Database.txt");

        cout << "Setting up the structs..."  << endl;

        host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
        host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.
        host_info.ai_flags = AI_PASSIVE;     // IP Wildcard

        status = getaddrinfo(NULL, argv[1], &host_info, &host_info_list);   //
        if (status != 0)  
            cout << "getaddrinfo error" << gai_strerror(status)<<endl ;

        cout << "Creating a socket..."<< endl;
        int sockID ;                          // The socket descripter
        sockID = socket(host_info_list->ai_family, host_info_list->ai_socktype,host_info_list->ai_protocol);   
        if (sockID == -1)  
            cout << "socket error \n" ;

        cout << "Binding socket..."  << endl;
        int yes = 1;
        status = setsockopt(sockID, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(int));     // Reusing port if already in use
        status = bind(sockID, host_info_list->ai_addr, host_info_list->ai_addrlen);   // Binding port
        if (status == -1)                                                               // Checking the status of the server
        {
            cout<<"Reuse port Error : "<< strerror(errno)<<endl;                        // Reuse error
            close(sockID);                                                            // Closing and opening the socket again
            sockID = socket(host_info_list->ai_family, host_info_list->ai_socktype,host_info_list->ai_protocol);
            cout << "Binding socket again..."  << endl;
            setsockopt(sockID, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(int));
            status=bind(sockID, host_info_list->ai_addr, host_info_list->ai_addrlen);
            cout<<status<<endl;
        }
        
        cout << "Listening for connections..."  << endl;                            // Waiting for connection
        status =  listen(sockID, 5);
        if (status == -1)  cout << "listen error" << endl ;


        int acceptID;                                                               // Accepting connection
        struct sockaddr_storage their_addr;
        socklen_t addr_size = sizeof(their_addr);
        acceptID = accept(sockID, (struct sockaddr *)&their_addr, &addr_size);
        if (acceptID == -1)
        {
            cout << "listen error" << endl ;
        }
        else
        {
            cout << "Connection accepted. Using new sockID : "  <<  acceptID << endl;
        }
        
        while(true)
        {
            cout << "Waiting to recieve data..."  << endl;
            ssize_t bytes_recieved;
            char incomming_data_buffer[1000];
            bytes_recieved = recv(acceptID, incomming_data_buffer,1000, 0);
            // If no data arrives, the program will just wait here until some data arrives.
            if (bytes_recieved == 0) cout << "host shut down." << endl ;
            if (bytes_recieved == -1)cout << "recieve error!" << endl ;
            cout << bytes_recieved << " bytes recieved :" << endl ;
            incomming_data_buffer[bytes_recieved] = '\0';
            cout << incomming_data_buffer<<endl;
                
            switch(incomming_data_buffer[0])
            {
                case '0':
                {

                    cout << "sending back a message..."  << endl;
                    char *msg2 = "Adding user....\nEnter Username\n";
                    int len2;
                    ssize_t bytes_sent2;
                    len2 = strlen(msg2);
                    bytes_sent2 = send(acceptID, msg2, len2, 0);

                    ssize_t bytes_recieved2;
                    char incomming_data_buffer2[1000];
                    char incomming_data_buffer3[1000];
                    bytes_recieved2 = recv(acceptID, incomming_data_buffer2,1000, 0);
                    // If no data arrives, the program will just wait here until some data arrives.
                    if (bytes_recieved2 == 0) cout << "host shut down." << endl ;
                    if (bytes_recieved2 == -1)cout << "recieve error!" << endl ;
                    cout << bytes_recieved2 << " bytes recieved :" << endl ;
                    incomming_data_buffer2[bytes_recieved2] = '\0';
                    cout << incomming_data_buffer2<<endl;
                    
                    cout << "sending back a message..."  << endl;
                    msg2 = "Enter Password\n";
                    len2 = strlen(msg2);
                    bytes_sent2 = send(acceptID, msg2, len2, 0);

                    bytes_recieved2 = recv(acceptID, incomming_data_buffer3,1000, 0);
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
                    close(acceptID);
                    close(sockID);
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

}


// int main()
// {
//     while (true)
//     {
//         main2();
//     }
// }