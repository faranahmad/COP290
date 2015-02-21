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
#define SIZE 10000
/*for O_RDONLY*/
#include <fcntl.h>
#include <vector>

#include <openssl/ssl.h>
#include <openssl/err.h>

using namespace std;

SSL_CTX* InitSSL(void)
{ 
    SSL_load_error_strings();   /* Bring in and register error messages */
    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_library_init();
    SSL_CTX* ctx = SSL_CTX_new(SSLv3_client_method());   /* Create new context */
    if ( ctx == NULL )
    {
        exit(0);
    }
    return ctx;
}

void ShowCerts(SSL* ssl)
{   X509 *cert;
    char *line;
 
    cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);       /* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);       /* free the malloc'ed string */
        X509_free(cert);     /* free the malloc'ed certificate copy */
    }
    else
        printf("No certificates.\n");
}



int main(int argc, char** argv)
{
  if(argc<4)
  {
    cout<<"Error. Usage : ./tclient ip portnumber filename\n";
  }
  else
  {


    
    SSL_CTX *ctx=InitSSL();
  
    SSL *ssl;

  int status;
  struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
  struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
  struct sockaddr_in server;
  int sock;
  memset(&host_info, 0, sizeof host_info);

    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

    status = getaddrinfo(argv[1], argv[2], &host_info, &host_info_list);
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


    ssl = SSL_new(ctx);      /* create new SSL connection state */
    SSL_set_fd(ssl, socketfd); 

    if ( SSL_connect(ssl) <0 )   /* perform the connection */
        ERR_print_errors_fp(stderr);
    else
    { 
        ShowCerts(ssl);        /* get any certs */
                SSL_set_connect_state(ssl); 


    //filereading
    ifstream ifs(argv[3], ios::binary|ios::ate);
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
    SSL_write(ssl, len,20);
    cout<<"size sent"<<endl;
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
        int k=SSL_write(ssl, file2,SIZE);
        counter++;
        cout<<"sent "<<counter<<endl;
        cout<<k<<endl;

        SSL_read(ssl, msg,4);
        cout<<"conf recv\n";
        if(j==ans.size())
        {
            char* file3;
            SSL_write(ssl, file2,0);
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
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    }
    }
    return 0;
  }