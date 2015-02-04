#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>
#include <sys/stat.h>
 
/*for sendfile()*/
#include <sys/sendfile.h>
 
/*for O_RDONLY*/
#include <fcntl.h>
using namespace std;

int main()
{

    int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
    struct sockaddr_in server;
  struct stat obj;
  int sock;
  int choice;
  char buf[100], command[5], filename[20], *f;
  int k, size;
  int filehandle;
  
    printf("Enter filename to put to server: ");
          scanf("%s", filename);
    memset(&host_info, 0, sizeof host_info);

    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

    status = getaddrinfo("10.192.10.192", "5569", &host_info, &host_info_list);
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
    // long msg=734;
    // int len;
    // void* v= (void*)msg;
    // cout<<(long)v<<endl;
    // send(socketfd,&v, 1000, 0);
    // cout<<(long)v<<endl;
    // freeaddrinfo(host_info_list);
    // close(socketfd);
    recv(socketfd, &size, sizeof(int), 0);
      if(!size)
        {
          printf("No such file on the remote directory\n\n");
          exit(0);
        }
      f = (char*)malloc(size);
      recv(socketfd, f, size, 0);
      while(1)
        {
          filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
          if(filehandle == -1)
        {
          sprintf(filename + strlen(filename), "%d", 1);//needed only if same directory is used for both server and client
        }
          else break;
        }
      write(filehandle, f, size);
      close(filehandle);
      strcpy(buf, "cat ");
      strcat(buf, filename);
      system(buf);

}
