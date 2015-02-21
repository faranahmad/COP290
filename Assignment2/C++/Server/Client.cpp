#include <iostream>
#include <cstring>      
#include <sys/socket.h>     
#include <netdb.h>      
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
// #include <sys/SSL_writefile.h>
#include <fcntl.h>
#include <vector>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem.hpp>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define SIZE 10000
#define BUFFSIZE 10000000

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


std::string toStr(char* arr)  //Convert array of characters to string
{
    std::string ans="";
    for(int i=0;i<strlen(arr)&&arr[i]!='\0';i++)
    {
        ans+=arr[i];
    }
    return ans;
}

std::string FileName(std::string filename)
{
    std::string ans="";
    for(int i=filename.size()-1;i>=0;i--)
    {
        if(filename[i]!='/')
            ans=filename[i]+ans;
        else
            break;
    }
    return ans;
}

char* toArr(std::string str)  //Convert string to array of character
{
    char* ans=new char[str.size()];
    for(int i=0;i<str.size();i++)
    {
        ans[i]=str[i];
    }
    return ans;
}

int main(int argc, char** argv)
{
  if(argc<3)
  {
    std::cout<<"Error. Usage : ./tclient ip portnumber\n";
  }
  else
  {
    SSL_CTX *ctx=InitSSL();
    SSL *ssl;

    int status;                      // Contains the status of the server
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
    struct sockaddr_in server;
    int sock;
    memset(&host_info, 0, sizeof host_info);

    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

    status = getaddrinfo(argv[1], argv[2], &host_info, &host_info_list);
    if (status != 0)  
        std::cout << "Getaddrinfo error" << gai_strerror(status) ;

    int sockID ;                        // The socket descripter
    sockID = socket(host_info_list->ai_family, host_info_list->ai_socktype,host_info_list->ai_protocol);
    if (sockID == -1)  
        std::cout << "Socket error " ;

    int buffs = BUFFSIZE;
    setsockopt(sockID, SOL_SOCKET, SO_RCVBUF, &buffs, sizeof(buffs));
    std::cout << "Connecting..."  << std::endl;
    status = connect(sockID, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  
        std::cout << "Connection error!\n"; 
    else std::cout<<"Connected\n";
   
    uint32_t htonl(uint32_t hostlong);


    bool quit =false;

    ssl = SSL_new(ctx);      /* create new SSL connection state */
    SSL_set_fd(ssl, sockID); 

    if ( SSL_connect(ssl) <0 )   /* perform the connection */
        ERR_print_errors_fp(stderr);
    else
    { 
        ShowCerts(ssl);        /* get any certs */
        SSL_set_connect_state(ssl); 
    while(!quit)
    {
        std::cout<<"Choose from the following.\n";
        std::cout<<"1.Add User\n";
        std::cout<<"2.Verifying Credentials\n";
        std::cout<<"3.User Exist\n";
        std::cout<<"4.File transfer from client to server\n";
        std::cout<<"5.File transfer from server to client\n";
        std::cout<<"6.Quit\n";
        std::string temp;
        int bytes_recieved;
        int bytes_sent;
        int inp;
        std::cin>>inp;
        char num[2];
        sprintf(num,"%lld",(long long)inp);
        bytes_sent=SSL_write(ssl, num,2);
        switch(inp)
        {
            case 1:
            {
                std::cout<<"Enter Username\n";
                std::cin>>temp;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp.size());
                char* msg1=toArr(temp);
                std::cout<<temp.size()<<"   "<<strlen(msg1)<<std::endl;
                bytes_sent=SSL_write(ssl, size1,20);
                bytes_sent=SSL_write(ssl,msg1,temp.size());
                std::cout<<"Enter Password\n";
                std::cin>>temp;
                char size2[20];
                sprintf(size2,"%lld",(long long)temp.size());
                char* msg2=toArr(temp);
                bytes_sent=SSL_write(ssl, size2,20);
                bytes_sent=SSL_write(ssl,msg2,temp.size());
                std::cout<<"User Successfully added!\n";
                break;
            }
            case 2:
                {
                    std::cout<<"Enter Username\n";
                    std::cin>>temp;
                    char size1[20];
                    sprintf(size1,"%lld",(long long)temp.size());
                    char* msg1=toArr(temp);
                    bytes_sent=SSL_write(ssl, size1,20);
                    bytes_sent=SSL_write(ssl,msg1,temp.size());
                    std::cout<<"Enter Password\n";
                    std::cin>>temp;
                    char size2[20];
                    sprintf(size2,"%lld",(long long)temp.size());
                    char* msg2=toArr(temp);
                    bytes_sent=SSL_write(ssl, size2,20);
                    bytes_sent=SSL_write(ssl,msg2,temp.size());
                    char msg3[1];
                    bytes_recieved=SSL_read(ssl,msg3,1);
                    msg3[bytes_recieved]='\0';
                    if(msg3[0]=='1')
                        std::cout<<"Successfully\n";
                    else
                        std::cout<<"Sorry. Please try again\n";
                    break;
                }
            case 3:
                {
                    std::cout<<"Enter Username\n";
                    std::cin>>temp;
                    char size1[20];
                    sprintf(size1,"%lld",(long long)temp.size());
                    char* msg1=toArr(temp);
                    bytes_sent=SSL_write(ssl, size1,20);
                    bytes_sent=SSL_write(ssl,msg1,temp.size());
                    char msg3[1];
                    bytes_recieved=SSL_read(ssl,msg3,1);
                    msg3[bytes_recieved]='\0';
                    if(msg3[0]=='1')
                        std::cout<<"User Exists\n";
                    else
                        std::cout<<"User Does not exist\n";
                    break;
                }
            case 4:
                {
                    std::string temp1;
                    std::string temp2;
                    std::cout<<"Enter client address\n";
                    std::cin>>temp1;
                    std::cout<<"Enter server address\n";
                    std::cin>>temp2;

                    //filereading
                    std::ifstream ifs(temp1, std::ios::binary|std::ios::ate);
                    std::ifstream::pos_type pos = ifs.tellg();
                    std::vector<char>  ans(pos);
                    ifs.seekg(0, std::ios::beg);
                    ifs.read(&ans[0], pos);
                    ifs.close();

                    char msg[4];
                    char size1[20];
                    sprintf(size1,"%lld",(long long)temp2.size());
                    bytes_sent=SSL_write(ssl, size1,20);
                    char* filepath=toArr(temp2);
                    bytes_sent=SSL_write(ssl,filepath,temp2.size());
                    
                    char size2[20];
                    sprintf(size2,"%lld",(long long)ans.size());
                    bytes_sent=SSL_write(ssl, size2,20);

                    int dataLen=0;
                    int packetCounter=0;
                    while(1)
                    {
                        char *file2=new char[SIZE];
                        for(int l=0 ;l<SIZE&&dataLen<ans.size();l++,dataLen++)
                        {
                            file2[l]=ans[dataLen];
                        }
                        std::cout<<"SSL_writeing"<<std::endl;
                        SSL_write(ssl, file2,SIZE);
                        packetCounter++;
                        std::cout<<"sent "<<packetCounter<<std::endl;

                        SSL_read(ssl, msg,4);
                        std::cout<<"conf SSL_read\n";
                        if(dataLen==ans.size())
                        {
                            break;
                        }
                
                    }
                    std::vector<char> tempVector;
                    ans.swap(tempVector);
                    std::cout<<"file sent"<<std::endl;
                    break;
                }
            case 5:
                {
                    std::string temp1;
                    std::string temp2;
                    std::cout<<"Enter client address\n";
                    std::cin>>temp1;
                    std::cout<<"Enter server address\n";
                    std::cin>>temp2;

                    char msg[4];
                    msg[0]='1';
                    char len[20];
                    char size1[20];
                    sprintf(size1,"%lld",(long long)temp2.size());
                    bytes_sent=SSL_write(ssl, size1,20);
                    char* filepath=toArr(temp2);
                    bytes_sent=SSL_write(ssl,filepath,temp2.size());
                    
                    bytes_recieved=SSL_read(ssl, len,20);    
                    len[bytes_recieved]='\0';
                    long long size=atoll(len);
                    std::cout<<size<<std::endl;
                    
                    std::string data="";
                    int packetCounter=0;
                    int dataLen=0;

                    std::string name=FileName(temp1);
                    std::string filepath2=temp1.substr(0,temp1.size()-name.size());
                    std::cout<<"Filepath:"<<filepath2<<std::endl;
                    std::cout<<"Filename:"<<name<<std::endl;
                    boost::filesystem::path dir(filepath2);
                    if(!(boost::filesystem::exists(dir)))
                    {
                        std::cout<<"Directory Doesn't Exists"<<std::endl;
                        if (boost::filesystem::create_directory(dir))
                            std::cout << "Directory Successfully Created !" << std::endl;
                    }
                    std::ofstream out(filepath2+name);
                    while(1)
                    {
                        char *file=new char[SIZE];
                        bytes_recieved=SSL_read(ssl, file,SIZE);
                        std::cout<<bytes_recieved<<std::endl;
                        packetCounter++;
                        std::cout<<"recieved "<<packetCounter<<std::endl;    
                        for(int i=0;i<bytes_recieved && dataLen<size;i++)
                        {
                            data+=file[i];
                            dataLen++;
                        }
                        out << data;
                        data="";
                        SSL_write(ssl, msg,4);
                        std::cout<<"conf sent\n";
                        if(dataLen==size)
                        {
                            std::cout<<"breaking now"<<std::endl;
                            break;
                        }
                    }
                    out.close();
                    std::cout<<"file SSL_read"<<std::endl;
                    break;
                    
                }
            default:
                {
                    quit=true;
                    freeaddrinfo(host_info_list);
                    close(sockID);
                    SSL_free(ssl);
                    break;
                }
        }
    }
    }
    std::cout<<"ThankYou!\n";
    return 0;
  }
}