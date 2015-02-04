#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>
#include <sys/stat.h>
  
#include <fstream>
/*for sendfile()*/
#include <sys/sendfile.h>
#define SIZE 100000
/*for O_RDONLY*/
#include <fcntl.h>
#include <vector>
using namespace std;

char* readFileBytes(const char *name)  
{  
    // ifstream fl(name);  
    // fl.seekg( 0, ios::end );  
    // size_t len = fl.tellg();  
    // char *ret = new char[len];  
    // fl.seekg(0, ios::beg);   
    // fl.read(ret, len);  
    // fl.close();  
    // return ret;  


    FILE *fileptr;
    char *buffer;
    long filelen;
    fileptr = fopen(name, "rb");  // Open the file in binary mode
    fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
    filelen = ftell(fileptr);             // Get the current byte offset in the file
    rewind(fileptr);                      // Jump back to the beginning of the file
    buffer = (char *)malloc((filelen+1)*sizeof(char)); // Enough memory for file + \0
    fread(buffer, filelen, 1, fileptr); // Read in the entire file
    fclose(fileptr); // Close the file
    buffer[filelen]='\0';
    cout<<buffer<<endl;
    cout<<sizeof(buffer)<<endl;
    return buffer;

    // ifstream ifs(filename, ios::binary|ios::ate);
    // ifstream::pos_type pos = ifs.tellg();

    // std::vector<char>  result(pos);

    // ifs.seekg(0, ios::beg);
    // ifs.read(&result[0], pos);

    // return result;
}  
int main(int argc, char** argv)
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
  
    memset(&host_info, 0, sizeof host_info);

    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

    status = getaddrinfo("127.0.0.1", "5578", &host_info, &host_info_list);
    if (status != 0)  std::cout << "getaddrinfo error" << gai_strerror(status) ;

    int socketfd ; // The socket descripter
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
                      host_info_list->ai_protocol);
    if (socketfd == -1)  std::cout << "socket error " ;


    std::cout << "Connecting..."  << std::endl;
    status = connect(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  std::cout << "connect error\n"; else cout<<"connected\n" ;
    // void* m=(void*)75;
    // char integer[4];                  // buffer
    // integer[0]='0';
    // integer[1]='0';
    // integer[2]='0';
    // integer[3]='0';
    uint32_t htonl(uint32_t hostlong);
    char* file=readFileBytes(argv[1]);
    cout<<sizeof(file)<<endl;
    cout<<file<<endl;
    send(socketfd, file,SIZE, 0);
    freeaddrinfo(host_info_list);
    close(socketfd);
  }