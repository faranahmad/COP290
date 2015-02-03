#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
using namespace std;
int main()
{

    int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

    memset(&host_info, 0, sizeof host_info);

    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

    status = getaddrinfo("127.0.0.1", "5555", &host_info, &host_info_list);
    if (status != 0)  std::cout << "getaddrinfo error" << gai_strerror(status) ;

    int socketfd ; // The socket descripter
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
                      host_info_list->ai_protocol);
    if (socketfd == -1)  std::cout << "socket error " ;


    std::cout << "Connecting..."  << std::endl;
    status = connect(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  std::cout << "connect error\n"; else cout<<"connected\n" ;


    std::cout << "sending message..."  << std::endl;
    // char *msg = "GET / HTTP/1.1\nhost: www.google.com\n\n";
    int msg=69;
    int len;
    ssize_t bytes_sent;
    len = 4;
    bytes_sent = send(socketfd,(void*) msg, len, 0);

    std::cout << "Waiting to recieve data..."  << std::endl;
    ssize_t bytes_recieved;
    char incomming_data_buffer[1000];
    bytes_recieved = recv(socketfd, incomming_data_buffer,1000, 0);
    // If no data arrives, the program will just wait here until some data arrives.
    if (bytes_recieved == 0) std::cout << "host shut down." << std::endl ;
    if (bytes_recieved == -1)std::cout << "recieve error!" << std::endl ;
    std::cout << bytes_recieved << " bytes recieved :" << std::endl ;
    incomming_data_buffer[bytes_recieved] = '\0' ;
    std::cout << incomming_data_buffer << std::endl;
    std::cout << "Receiving complete. Closing socket..." << std::endl;
    cout<<incomming_data_buffer<<endl;
    freeaddrinfo(host_info_list);
    // close(socketfd);

}
