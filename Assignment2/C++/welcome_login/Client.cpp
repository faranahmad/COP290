#include "UserBase.h"
#include <iostream>
#include <unistd.h>
#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
using namespace std;

extern bool contains;
extern string usname,passwd;
extern bool buttonclicked;

int clientmain(int argc, char* argv[])
{

    int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

    memset(&host_info, 0, sizeof host_info);

    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

    status = getaddrinfo(argv[1], argv[2], &host_info, &host_info_list);   // Get address info
    if (status != 0)  
    	std::cout << "getaddrinfo error" << gai_strerror(status) ;

    int socketfd ; // The socket descripter
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
                      host_info_list->ai_protocol);
    if (socketfd == -1)  std::cout << "socket error " ;


    std::cout << "Connecting..."  << std::endl;
    status = connect(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  std::cout << "connect error\n"; else cout<<"connected\n" ;

	char *msg = "GET / HTTP/1.1\nhost: www.google.com\n\n";
    int len;
    ssize_t bytes_sent;

	while(true)
	{
		int x;
		// cin >> x;
		if (contains)
		{
			contains=false;
			// Add User
			//Sending 0
			cout <<"Adding User\n";
			msg ="0";
			len= strlen(msg);
			bytes_sent = send (socketfd, msg, len, 0);

			//Receivng confirmation for 0
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
    
    		//Sending username
			string username,pwd;
			username=usname;
			// cin >> username;
			char * S = new char[username.length() + 1];
			std::strcpy(S,username.c_str());

			msg=S;
			len=strlen(msg);
			bytes_sent = send (socketfd, msg, len, 0);


			//Receiving confirmation for username
			std::cout << "Waiting to recieve data..."  << std::endl;
    		// ssize_t bytes_recieved;
    		// char incomming_data_buffer[1000];
    		bytes_recieved = recv(socketfd, incomming_data_buffer,1000, 0);
    		// If no data arrives, the program will just wait here until some data arrives.
    		if (bytes_recieved == 0) std::cout << "host shut down." << std::endl ;
    		if (bytes_recieved == -1)std::cout << "recieve error!" << std::endl ;
    		std::cout << bytes_recieved << " bytes recieved :" << std::endl ;
    		incomming_data_buffer[bytes_recieved] = '\0' ;
    		std::cout << incomming_data_buffer << std::endl;
    		std::cout << "Receiving complete. Closing socket..." << std::endl;
    		cout<<incomming_data_buffer<<endl;
    

    		//Sending pwd
			// cin >> pwd;
			pwd=passwd;
			S = new char[pwd.length() + 1];
			std::strcpy(S,pwd.c_str());
			msg=S;
			len=strlen(msg);
			bytes_sent = send (socketfd, msg, len, 0);
			// cout <<"Username: " << username <<" pwd: " <<pwd <<"\n";
			
		}
		else if (x==1)
		{
			// Login
			cout <<"Logging in\n";
			string username,pwd;
			cin >> username >> pwd;	
			cout <<"Username: " << username <<" pwd: " <<pwd <<"\n";
		}
		else if (x==2)
		{
			cout <<"Checking if user exists\n";
			// Check User
			string username;
			cin >> username;	
			cout <<"Username: " <<username <<"\n";
		}
		else if (buttonclicked)
		{
			buttonclicked=false;
			cout <<"Exit Case\n";
			msg ="3";
			len= strlen(msg);
			bytes_sent = send (socketfd, msg, len, 0);

			break;
			// Exit case
		}
	}


    // std::cout << "sending message..."  << std::endl;
    
    // len = 4;
    // bytes_sent = send(socketfd,(void*) msg, len, 0);

    // std::cout << "Waiting to recieve data..."  << std::endl;
    // ssize_t bytes_recieved;
    // char incomming_data_buffer[1000];
    // bytes_recieved = recv(socketfd, incomming_data_buffer,1000, 0);
    // // If no data arrives, the program will just wait here until some data arrives.
    // if (bytes_recieved == 0) std::cout << "host shut down." << std::endl ;
    // if (bytes_recieved == -1)std::cout << "recieve error!" << std::endl ;
    // std::cout << bytes_recieved << " bytes recieved :" << std::endl ;
    // incomming_data_buffer[bytes_recieved] = '\0' ;
    // std::cout << incomming_data_buffer << std::endl;
    // std::cout << "Receiving complete. Closing socket..." << std::endl;
    // cout<<incomming_data_buffer<<endl;
    freeaddrinfo(host_info_list);
    close(socketfd);

}
