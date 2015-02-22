
#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>     // Needed for closing the sockets
#include "UserBase.h"
#include <fstream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <vector>
#include <pthread.h>
#define SIZE 10000
using namespace std;


SSL_CTX* ctx;
int isRoot()
{
    if (getuid() != 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
 
}


bool isEmpty(char* file)
{
    for(int i=0;i<sizeof(file);i++)
    {
        if(file[i]!='\0')
            return false;
    }
    return true;
}



void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile)
{
    /* set the local certificate from CertFile */
    if ( SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* set the private key from KeyFile (may be the same as CertFile) */
    if ( SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* verify private key */
    if ( !SSL_CTX_check_private_key(ctx) )
    {
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }
}

void ShowCerts(SSL* ssl)
{   X509 *cert;
    char *line;
 
    cert = SSL_get_peer_certificate(ssl); /* Get certificates (if available) */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);
        X509_free(cert);
    }
    else
        printf("No certificates.\n");
}

SSL_CTX* InitSSL()
{
    SSL_load_error_strings();   /* load all error messages */
    SSL_library_init();
    OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
    SSL_CTX *ctx=SSL_CTX_new(SSLv3_server_method());
    if ( ctx == NULL )
    {
        exit(0);
    }

    LoadCertificates(ctx, "Cert.pem", "Cert.pem");
    return ctx;
}




    

void *acceptor(void* data)
{
    long new_sd=(long)data;
    if (new_sd == -1)
    {
        cout << "listen error" << endl ;
    }
    else
    {
        cout << "Connection accepted. Using new socketfd : "  <<  new_sd << endl;
    }

    SSL* ssl = SSL_new(ctx);;
SSL_set_fd(ssl, new_sd);
 if ( SSL_accept(ssl)<0 )     /* do SSL-protocol accept */
        ERR_print_errors_fp(stderr);
    else
    {   
        SSL_set_accept_state(ssl); 
        ShowCerts(ssl); 

    cout << "Waiting to recieve data..."  << endl;
    char len[20];
    int bytes_recieved;
    bytes_recieved=SSL_read(ssl, len,20);
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
    string filename="Anu"+std::to_string(new_sd);
    std::ofstream out(filename);
    cout<<"FileCreated"<<endl;
    while(1)
    {
        bytes_recieved=SSL_read(ssl, file,SIZE);
        cout<<bytes_recieved<<endl;
        counter++;
        cout<<"recieved "<<counter<<endl;    
        if(bytes_recieved<=0)
        {
            cout<<"breaking now"<<endl;
            break;
        }
        for(int i=0;i<bytes_recieved && dataLen<size;i++)
        {
            data+=file[i];
            dataLen++;
        }
        out << data;
        data="";
        SSL_write(ssl, msg,4);
        cout<<"conf sent\n";
    }
    
    cout<<"file recv"<<endl;
    
    out.close();
    SSL_free(ssl);             /* release context */

    }
}

int main(int argc, char** argv)
{
    if(argc<3)
    {
        cout<<"Error. Usage: ./tserver portnumber extension\n";
    }
    else
    {

    if(!isRoot())
    {
        printf("This program must be run as root/sudo user!!");
        exit(0);
    }


   ctx=InitSSL();



    SSL *ssl;
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


    std::vector<pthread_t> threads= std::vector<pthread_t>(10);              /* get new SSL state with context */
    

    int k=0;
while(k<10)
    {

    long new_sd;
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);

    new_sd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);
    int l=pthread_create(&threads[k],NULL,acceptor,(void *)new_sd);
    k++;
}
    
}
    return 0;

}