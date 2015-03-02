#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>     // Needed for closing the sockets
#include "UserBase.h"
#include "FileHistory.h"   
#include <fstream>
#include <string>
#include <vector>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem.hpp>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <pthread.h>

#define SIZE 10000
#define JOIN 500
#define BUFFSIZE 10000000
#define THREADS 100

extern char input;

SSL_CTX *ctx;           //SSL_CTX object is created as a framework to establish TLS/SSL enabled connections         
bool closeServer=false; // Boolean variable for the status of the server

UserBase base=UserBase();        // Loading the database of users.
int sockID ;                         // The socket descriptor

struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

extern std::vector<std::string> usersLog;  // Users which are logged in
std::vector<std::string> allUsers; // All users


//Given a path in string format, this function
//returns a vector of string of subfolders and files
//of the given path. It is has been called recursively
std::vector<std::string> GetFiles(std::string location)
{
    boost::filesystem::path p (location); // path variable of the location
    std::vector< std::string > ans;     //ans of this function
    if (exists(p))    // does p actually exist?
    {
        std::vector<boost::filesystem::path> v; //vector of paths inside the given path
        //iterating over the directory
        std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), back_inserter(v)); 
        std::sort(v.begin(), v.end()); //sorting the vector.
        for (int i=0; i<v.size() ; i++ )
        {
            if (is_regular_file(v[i])) //if it is a regular file, no need for recursion
            {
                ans.push_back(v[i].string()); //pushing it into the vector
            }
            else
            {
                std::cout<<"###########"<<v[i].string()<<std::endl;
                if(v[i].string().find(".data")!=std::string::npos) //not including the files in .data folder
                    continue;
                ans.push_back(v[i].string()+"/"); //pushing it into the vector
                std::vector<std::string> Merged = ans; 
                std::vector<std::string> Subset = GetFiles(v[i].string()); //recursively calling the function
                Merged.insert(Merged.end(), Subset.begin(), Subset.end()); //merging the two parts.
                ans = Merged;
            }
        }
    }
    else
    {
        std::cout <<"folder dne \n";     //folder does not exists   
    }
    std::cout<<"Out of get files"<<std::endl;
    return ans;
}   


//This function accepts two vector of chars and
//returns whether they are equal index by index.
//It is used to compare to two files
bool EqualVector(std::vector<char> file1, std::vector<char> file2)
{
    for(int i=0;i<file1.size();i++)
    {
        if(file1[i]!=file2[i])
        {   
            std::cout<<i<<"    "<<file1[i]<<"    "<<file2[i]<<std::endl;
            return false;
        }
    }
    return true;
}

//This function accepts two path locations in string 
//format and checks whether these two files have the 
//same content. Used for de-duplication. The files are
//in chunks.
int CompFiles(std::string file1,  std::string file2)
{
    std::ifstream ifs1(file1,std::ios::binary|std::ios::ate); //opening the first file
    std::ifstream ifs2(file2,std::ios::binary|std::ios::ate); //opening the second file

    ifs1.seekg(0, std::ios::end); //setting the position of the end at the file
    std::ifstream::pos_type pos = ifs1.tellg(); //getting the position. Equal to bytes of the file.
    ifs2.seekg(0, std::ios::end);//setting the position of the end at the file
    std::ifstream::pos_type pos2 = ifs2.tellg(); //getting the position. Equal to bytes of the file.
    long long counter=0; //number of bytes that have been read from both the files
    std::vector<char> f1; // the bytes are read into this vector
    std::vector<char> f2;// the bytes are read into this vector
    if((long long)pos!=(long long)pos2) //if they are not of the same size then not equal.
    {
        std::cout<<"Sizes dont match"<<std::endl;
        goto WRONG;
    }
    
    while(counter<pos)
    {
        ifs1.seekg(counter,std::ios::beg); //setting the position 
        ifs2.seekg(counter,std::ios::beg); //setting the position
        if(counter+SIZE>pos) //last chunk
        {   
            int temp=(long long )pos - counter;
            f1.resize(temp);
            f2.resize(temp);
            ifs1.read(&f1[0],temp);
            ifs2.read(&f2[0],temp);
        }
        else //other chunks
        {
            f1.resize(SIZE);
            f2.resize(SIZE);
            ifs1.read(&f1[0],SIZE);
            ifs2.read(&f2[0],SIZE);
        }
        std::cout<<f1.size()<<f2.size()<<std::endl;
        if (EqualVector(f1,f2))
            std::cout << "success" << std::endl;
        else
        {   
            WRONG:std::cout << "Not equal"<<std::endl;
            return false;
        }
        counter+=SIZE;
    }
    std::cout<<"Equal"<<std::endl;
    return true;
}

//This function accepts an array of 
//characters to string
std::string ToStr(char* arr)  
{
    std::string ans="";
    for(int i=0;i<strlen(arr)&&arr[i]!='\0';i++)
    {
        ans+=arr[i];
    }
    return ans;
}

//This function accepts a parameter 
//in the string format and returns the 
//name of the file
std::string FileName(std::string filename)
{
    std::string ans=""; //answer of this function
    for(int i=filename.size()-1;i>=0;i--)
    {
        if(filename[i]!='/')
            ans=filename[i]+ans;
        else
            break;
    }
    return ans;
}


//This function accepts a string
//and converts it into an array of
//characters
char* ToArr(std::string str)  
{
    char* ans=new char[str.size()]; //answer of this function
    for(int i=0;i<str.size();i++)
    {
        ans[i]=str[i];
    }
    ans[str.size()]='\0';
    return ans;
}

//This function checks whether it is run as
//root or not. This is required for certificate
//authentication
int isRoot() 
{
    if (getuid() != 0)
        return 0;
    else
        return 1;
}

//This function accpets a SSL_CTX Object, Certificate file
//and a key file and loads them. Aborts if the load is
//unsuccessful
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


//This function gets the certificates 
//(if available) of the client 
//and displays its contents
void ShowCerts(SSL* ssl)
{   X509 *cert; //X509 Certificate
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
        printf("No certificates.\n"); //No certificates
}

//Initialize the SSL connection with SSLv3 method
//Initializes all the algorithms and error messages
//Loads the certificates
SSL_CTX* InitSSL()
{
    SSL_load_error_strings();   /* load all error messages */
    SSL_library_init(); //initializing SSL
    OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
    SSL_CTX *ctx=SSL_CTX_new(SSLv3_server_method());
    if ( ctx == NULL )
    {
        exit(0);
    }

    char* cert=ToArr("Cert.pem"); //Certificate file
    LoadCertificates(ctx, cert, cert); //Loading certificate file
    return ctx;
}

//This function acts a terminal input
//It is run on an different thread
//The server quits if q is received
void *Input(void * data)
{
    // char input; //Input
    // START:std::cin>>input; //Taking the input from the terminal
    while(1)
    {
        if(input=='q')
        {
            closeServer=true; //making the boolean to true
            close(sockID); //closing the socket
            freeaddrinfo(host_info_list); //freeing address info
            SSL_CTX_free(ctx);   //Freeing the SSL_CTX object
            std::cout<<"Server Shutting Down\n";  
            break;
        }
    }
}


//This function serves a client given 
//socket id. This function is threaded
//thus more than one client can connect
//at the same time.
void *ClientService(void* data)
{
    int acceptID=(int)(long)data; //Extracting the int from data
    bool quit=false;               //quit boolean variable
    std::string userID=""; //username of the client

    SSL* ssl = SSL_new(ctx);              /* get new SSL state with context */
    SSL_set_fd(ssl, acceptID);            //setting the SSL connection to the accepted ID
    if (acceptID == -1) //error in accepting a connection
    {
        // std::cout << strerror(errno);
        // std::cout << "Listen error" << std::endl ;
        goto END;
    }
    else
    {
        std::cout << "Connection accepted. Using new sockID : "  <<  acceptID << std::endl;
    }

    if ( SSL_accept(ssl)<0 )     /* do SSL-protocol accept */
        ERR_print_errors_fp(stderr);
    else
    {
        SSL_set_accept_state(ssl); //setting the ssl state to server
        ShowCerts(ssl); //Getting certificate of the client if any
        while(!quit)
        {
             
            std::cout << "Waiting to recieve data..."  << std::endl;
            char command[2]; //the command received
            int bytes_recieved;//number of byters received
            int bytes_sent; //number of bytes sent
            long long size;//size 
            bytes_recieved=SSL_read(ssl, command,2);//reading the command to be executed
            command[bytes_recieved]='\0';
            std::cout<<"Command recieved "<<atoi(command)<<std::endl;
    
            switch(atoi(command))
            {
                case 16: //Change password
                {
    
                    char len[20];
                    bytes_recieved=SSL_read(ssl,len,20); //receiving the username size
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    char msg1[size];
                    bytes_recieved=SSL_read(ssl,msg1,size); //receiving the username
                    msg1[bytes_recieved]='\0';
                    std::string username=ToStr(msg1);
                    std::cout<<username<<std::endl;
                    bytes_recieved=SSL_read(ssl,len,20); // receiving the old password size
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    char msg2[size];
                    bytes_recieved=SSL_read(ssl,msg2,size);//receiving the old password
                    msg2[bytes_recieved]='\0';
                    std::string oldpass=ToStr(msg2);
                    std::cout<<oldpass<<std::endl;
                    bytes_recieved=SSL_read(ssl,len,20);//receiving the new password size
                    len[bytes_recieved]='\0';
                    size=atoll(len);
                    char msg3[size];
                    bytes_recieved=SSL_read(ssl,msg3,size);//receiving the new password
                    msg3[bytes_recieved]='\0';
                    std::string newpass=ToStr(msg3);
                    std::cout<<newpass<<std::endl;
                    char msg4[1];
                    if(base.ChangePassword(username,oldpass,newpass)) //changing the password
                    {
                        msg4[0]='1'; //successful change
                        base.StoreToFile("Database.txt");
    
                    }
                    else
                    {
                        msg4[0]='0'; //unsuccessful 
                    }
                    bytes_sent=SSL_write(ssl,msg4,1); //sending the answer
                    
                    break;
                }
    
    
                case 8: // Adding username
                    {
                        char len[20];
                        bytes_recieved=SSL_read(ssl,len,20); //receiving the username size
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        char msg1[size];
                        bytes_recieved=SSL_read(ssl,msg1,size); //receiving the username
                        msg1[bytes_recieved]='\0';
                        std::string username=ToStr(msg1);
                        std::cout<<username<<std::endl;
                        bytes_recieved=SSL_read(ssl,len,20);//receiving the password size
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        char msg2[size];
                        bytes_recieved=SSL_read(ssl,msg2,size);//receiving the password
                        msg2[bytes_recieved]='\0';
                        base.InsertUser(User(username,ToStr(msg2)));//inserting user
                        base.StoreToFile("Database.txt");
                        allUsers.push_back(username);
                        std::cout<<ToStr(msg2)<<std::endl;
                        break;
                    }
                case 7: // Login
                    {
                        char len[20];
                        bytes_recieved=SSL_read(ssl,len,20);//receiving the usernmae size
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        char msg1[size];
                        bytes_recieved=SSL_read(ssl,msg1,size);//receiving the username
                        msg1[bytes_recieved]='\0';
                        std::string username=ToStr(msg1);
                        std::cout<<username<<std::endl;
                        bytes_recieved=SSL_read(ssl,len,20);//receiving the password size
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        char msg2[size];
                        bytes_recieved=SSL_read(ssl,msg2,size);//receiving the password
                        msg2[bytes_recieved]='\0';
                        char msg3[1]; 
                        msg3[1]='\0';
                        if(base.VerifyUserCredentials(User(username,ToStr(msg2))))//verifying the credentials
                        {
                            msg3[0]='1'; //successful
                            usersLog.push_back(username);
                            userID=username;
                        }
                        else
                        {
                            msg3[0]='0';//unsuccessful
                        }
                        bytes_sent=SSL_write(ssl,msg3,1);//sending the answer
                        break;
                    }
                case 9: // Exist
                    {
                        char len[20];
                        bytes_recieved=SSL_read(ssl,len,20); //receiving the username size
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        char msg1[size];
                        bytes_recieved=SSL_read(ssl,msg1,size);//receiving the username
                        msg1[bytes_recieved]='\0';
                        std::string username=ToStr(msg1);
                        std::cout<<username<<std::endl;
                        char msg3[1];
                        msg3[1]='\0';
                        if(base.CheckUserExists(User(username))) //checking if the user exists
                            msg3[0]='1';//successful
                        else
                            msg3[0]='0';//unsucessful
                        bytes_sent=SSL_write(ssl,msg3,1); //sending the answer
                        break;
                    }
                case 1 : // File transfer from client to server case 1 and return filepath
                    {
                        char msg[4]; //confirmation message
                        msg[4]='\0';
                        msg[0]='1';
                        char len[20]; //receiving the size of the location
                        bytes_recieved=SSL_read(ssl, len,20);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        std::cout<<size<<std::endl;
                        char filename[size];
                        bytes_recieved=SSL_read(ssl,filename,size); //receiving the location
                        filename[bytes_recieved]='\0';
                        std::cout<<ToStr(filename)<<std::endl;
                        std::string name=FileName(ToStr(filename)); //getting the filename
                        std::string filepath=ToStr(filename).substr(0,strlen(filename)-name.size()); //getting the folder location
                        std::cout<<"Filepath:"<<filepath<<std::endl;
                        std::cout<<"Filename:"<<name<<std::endl;
                        boost::filesystem::path dir(filepath); //path variable for the directory
                        if(!(boost::filesystem::exists(dir))) //creating directory if it does not exist
                        {
                            std::cout<<"Directory Doesn't Exists"<<std::endl;
                            if (boost::filesystem::create_directories(dir))
                                std::cout << "Directory Successfully Created !" << std::endl;
                        }
    
                        bytes_recieved=SSL_read(ssl, len,20); //receiving the size of the file to be received
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        std::cout<<size<<std::endl;
                        
                        std::string data=""; //data which will be written in the file
                        int packetCounter=0; //number of packets received
                        int dataLen=0; // Length of the data which has been received
    
                        std::ofstream out(filepath+name); //ofstream object associated with the file
                        std::cout<<"FileCreated"<<std::endl; 
    
                        while(1)
                        {
                            char file[SIZE]; //receiving the file in chunks of 100KB
                            bytes_recieved=SSL_read(ssl, file,SIZE);
                            file[bytes_recieved]='\0';
                            std::cout<<bytes_recieved<<std::endl;
                            packetCounter++;
                            for(int i=0;i<bytes_recieved && dataLen<size;i++)
                            {
                                data+=file[i];
                                dataLen++;
                            }
                            out << data; //writing the data in the file
                            data="";
                            std::cout<<"recieved "<<packetCounter<<std::endl;
                            SSL_write(ssl, msg,4); //sending the confirmation
                            std::cout<<"conf sent\n";    
                            if(/*bytes_recieved<=0*/ dataLen==size) //full file received
                            {
                                std::cout<<"breaking now"<<std::endl;
                                out.close(); //closing ofstream object
                                break;
                            }
                            
                        }
                        std::cout<<"Out of loop\n";

                        //de-duplication case
                        //searching for a file with the same contents in the database
                        //if there exists then it returns the absolute path to that file
                        //otherwise it returns the path of the received path
                        std::string location="/home/skipper/Desktop/DeadDropServer/"; //location of the file where we search
                        std::vector< std::pair<std::string, int> > files=GetVectorFiles(location);
                        std::string path=""; //iterating variable
                        std::string pathReturn=filepath+name; //path to be returned
                        for(int i=0;i<files.size();i++)
                        {
                            path=files[i].first; 
                            if(path.compare(filepath+name)==0)//if same then continue
                                continue;
                            if(path.find("/.data/")!=std::string::npos) //if contains .data, continue
                                continue;
                            if(CompFiles(filepath+name,path)) //if some other file has the same contents then break
                            {
                                pathReturn=path;
                                break;
                            }
                        }
                        //deleting the file if there exists another file with the same name
                        if(pathReturn.compare(filepath+name)!=0)
                        {
                            if(boost::filesystem::exists(filepath+name))
                            {
                                boost::filesystem::remove(filepath+name);
                                std::cout<<"Deleted"<<std::endl;
                            }
                        }
                        std::cout<<pathReturn<<std::endl;
                        char size1[20]; //sending the size of the pathReturn
                        sprintf(size1,"%lld",(long long)pathReturn.size());
                        bytes_sent=SSL_write(ssl, size1,20);
                        char* filepath2=ToArr(pathReturn); //sending the pathReturn
                        bytes_sent=SSL_write(ssl,filepath2,pathReturn.size());
                        std::cout<<"file sent"<<std::endl;
                        break;
                    }
                case 2: //File transfer from server to client case 2
                    {
                        char msg[4]; //the confirmation message
                        msg[4]='\0';
                        msg[0]='1';
                        char len[20]; //receiving the size of the location of the file to be sent
                        bytes_recieved=SSL_read(ssl, len,20);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        std::cout<<size<<std::endl;
                        char filename[size]; //receiving the location of the file to be sent
                        bytes_recieved=SSL_read(ssl,filename,size);
                        filename[bytes_recieved]='\0';
                        std::cout<<ToStr(filename)<<std::endl;
                        std::string name=FileName(ToStr(filename)); //name of the file
                        std::string filepath=ToStr(filename).substr(0,strlen(filename)-name.size());//directory of the file
                        std::cout<<"Filepath:"<<filepath<<std::endl;
                        boost::filesystem::path dir(filepath);
                        std::cout<<"Filename:"<<name<<std::endl;
                        // if(!(boost::filesystem::exists(dir)))
                        // {
                        //     std::cout<<"Directory Doesn't Exists"<<std::endl;
                        //     if (boost::filesystem::create_directories(dir))
                        //         std::cout << "Directory Successfully Created !" << std::endl;
                        // }
                        std::cout<<"Dir Created"<<std::endl;
                        //filereading-> stored in ans
                        std::string loc=filepath+name; //location of the file
                        std::cout<<loc<<std::endl;
                        std::ifstream ifs(loc); //associating ifstream object with the file
                        ifs.seekg(0, std::ios::end);//setting the position at the end of the file
                        std::ifstream::pos_type pos = ifs.tellg(); //getting the position, equal to the size
                        std::vector<char>  ans(pos); //initializing a vector of size of the file where the bytes would be read
                        ifs.seekg(0, std::ios::beg); //setting the position at the start
                        ifs.read(&ans[0], pos);
                        
    
                        std::cout<<"File read Successfully\n";
                        char size1[20];
                        size1[20]='\0';//sending the size of the file to be sent
                        sprintf(size1,"%lld",(long long)ans.size());
                        for(int i=0;i<strlen(size1);i++)
                        {
                            std::cout<<size1[i]<<std::endl;
                        }
                        bytes_sent=SSL_write(ssl, size1,20);
                        std::cout<<"Size:"<<bytes_sent<<std::endl;
                        std::cout<<"Initiating SSL_writing protocol\n";
    
                        int dataLen=0; //Length of data which has been sent
                        int packetCounter=0; //Number of packets of 100 KB which has been sent.
                        while(1)
                        {
                            char *file2=new char[SIZE]; //Reading the characters from the vector in size of 100KB
                            for(int l=0 ;l<SIZE&&dataLen<ans.size();l++,dataLen++)
                            {
                                file2[l]=ans[dataLen];
                            }
                            file2[SIZE]='\0';
                            std::cout<<"SSL_writing"<<std::endl;
                            SSL_write(ssl, file2,SIZE); //Writing into the ssl connection
                            packetCounter++;
                            std::cout<<"sent "<<packetCounter<<std::endl;
    
                            bytes_recieved=SSL_read(ssl, msg,4); //Receiving the confirmation
                            msg[bytes_recieved]='\0';
                            std::cout<<"conf SSL_read\n";
                            if(dataLen==ans.size()) //Complete file sent
                            {
                                break;
                            }
                    
                        }
                        std::vector<char> tempVector; //swapping the vector with an empty vector
                        ans.swap(tempVector);          // to free up the memory occupied by ans
                        std::cout<<"file sent"<<std::endl;
    
                        break;
                    }
                case 6: // delete file on server
                    {
                        char len[20]; //receiving the size of the file location
                        bytes_recieved=SSL_read(ssl, len,20);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        std::cout<<size<<std::endl;
                        char filename[size]; //receiving the file location
                        bytes_recieved=SSL_read(ssl,filename,size);
                        filename[bytes_recieved]='\0';
                        boost::filesystem::wpath file(ToStr(filename)); 
                        if(boost::filesystem::exists(file)) //removing the file if it exists
                            boost::filesystem::remove(file);
                        break;
                    }
                case 10: //logout
                    {
                        END:int i=0; //finding the user in the usersLog and removing it
                        for(i=0;i<usersLog.size();i++)
                        {
                            if(usersLog[i].compare(userID)==0)
                                break;
                        }
                        if(i<usersLog.size())
                            usersLog.erase (usersLog.begin()+i);
                        char msg[1];
                        msg[0]='1'; //sending and receiving confirmation 
                        bytes_recieved=SSL_read(ssl,msg,1);
                        bytes_sent=SSL_write(ssl,msg,1);
                        close(acceptID); //closing connection
                        SSL_free(ssl);         /* release SSL state */
                        quit=true;
                        break;
                    }
                case 11: // send serverlist
                    {
                        char msg[4];
                        msg[0]='1';
                        msg[4]='\0';
                        char len[20];
                        bytes_recieved=SSL_read(ssl, len,20);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        std::cout<<size<<std::endl;
                        char filename[size];
                        bytes_recieved=SSL_read(ssl,filename,size);
                        filename[bytes_recieved]='\0';
                        std::cout<<ToStr(filename)<<std::endl;
    
                        int fileCount=0; // 0-receiving 1-giving 2-sehistory
                        while(fileCount<3)
                        {
                            std::string temp;
                            switch(fileCount)
                            {
                                case 0:
                                {
                                    temp="receiving.txt";
                                    break;
                                }
                                case 1:
                                {
                                    temp="giving.txt";
                                    break;
                                }
                                case 2:
                                {
                                    temp="sehistory.txt";
                                    break;
                                }
                                default:
                                {
                                    break;
                                }
                            }
                            std::string name=FileName(ToStr(filename)+temp); //extracting the file name form the location
                            std::string filepath=(ToStr(filename)+temp).substr(0,strlen(filename)-name.size()); //directory
                            std::cout<<"Filepath:"<<filepath<<std::endl;
                            std::cout<<"Filename:"<<name<<std::endl;
                            boost::filesystem::path dir(filepath); //creating directory if it does not exist
                            if(!(boost::filesystem::exists(dir)))
                            {
                                std::cout<<"Directory Doesn't Exists"<<std::endl;
                                if (boost::filesystem::create_directory(dir))
                                    std::cout << "Directory Successfully Created !" << std::endl;
                            }
    
                            //filereading(all parts)-> stored in ans
                            int part=0;
                            std::string p=std::to_string(part);
                            std::vector<char>  ans;
                            int counter=0;
    
                            while(1)
                            {   std::string s=filepath+name+p;
                                std::ifstream ifs(s, std::ios::binary|std::ios::ate);
                                std::cout<<ifs.is_open()<<std::endl;
                                if(!ifs.is_open())
                                {
                                    ifs.close();
                                    break;
                                }
                                std::ifstream::pos_type pos = ifs.tellg();
                                ans.resize(ans.size()+pos);
                                ifs.seekg(0, std::ios::beg);
                                ifs.read(&ans[counter], pos);
                                part++;
                                counter=ans.size();
                                p=std::to_string(part);
                            }
    
                            std::cout<<"All files read Successfully\n";
                            char size1[20];
                            size1[20]='\0';
                            sprintf(size1,"%lld",(long long)ans.size());
                            bytes_sent=SSL_write(ssl, size1,20);
                            std::cout<<"Initiating SSL_writing protocol\n";
        
                            int dataLen=0;
                            int packetCounter=0;
                            while(1)
                            {
                                char *file2=new char[SIZE];
                                for(int l=0 ;l<SIZE&&dataLen<ans.size();l++,dataLen++)
                                {
                                    file2[l]=ans[dataLen];
                                }
                                file2[SIZE]='\0';
                                std::cout<<"SSL_writing"<<std::endl;
                                SSL_write(ssl, file2,SIZE);
                                packetCounter++;
                                std::cout<<"sent "<<packetCounter<<std::endl;
    
                                bytes_recieved=SSL_read(ssl, msg,4);
                                msg[bytes_recieved]='\0';
                                std::cout<<"conf SSL_read\n";
                                if(dataLen==ans.size())
                                {
                                    break;
                                }
                        
                            }
                            std::vector<char> tempVector;
                            ans.swap(tempVector);
                            std::cout<<"file sent"<<std::endl;
                            fileCount++;
                        }
                        break;
                    }
                case 12: // Receive a random string
                    {
                        char len[20];
                        bytes_recieved=SSL_read(ssl, len,20);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        std::cout<<size<<std::endl;
                        char data[size];
                        bytes_recieved=SSL_read(ssl,data,size);
                        data[bytes_recieved]='\0';
                        std::cout<<ToStr(data)<<std::endl;
                        std::string Location = ToStr(data);
                        FileHistory ServerFiles = GetFilesOnDisc(Location);
                        ServerFiles.StoreToFileBase(Location+"/sehistory.txt");
                        // Refresh the folder files 
                        // Store the files
    
                        break;
                    }
                case 13: // Receive serverlist
                    {
                        char msg[4];
                        msg[0]='1';
                        msg[4]='\0';
                        char len[20];
                        bytes_recieved=SSL_read(ssl, len,20);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        std::cout<<size<<std::endl;
                        char filename[size];
                        bytes_recieved=SSL_read(ssl,filename,size);
                        filename[bytes_recieved]='\0';
                        std::cout<<ToStr(filename)<<std::endl;
                        int fileCount=0;
                        std::string temp3=ToStr(filename);
                        std::string temp1;
                        while(fileCount<3)
                        {
                            bytes_recieved=SSL_read(ssl, len,20);    
                            len[bytes_recieved]='\0';
                            long long size=atoll(len);
                            std::cout<<size<<std::endl;
                            
                            switch(fileCount)
                            {
        
                                case 0:
                                    {
                                        temp1=(temp3+"receiving.txt");
                                        break;
                                    }
                                case 1:
                                    {
                                        temp1=(temp3+"giving.txt");
                                        break;
                                    }
                                case 2:
                                    {
                                        temp1=(temp3+"sehistory.txt");
                                        break;
                                    }
                                default:
                                    {
                                        break;
                                    }   
                            }
        
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
                            std::string data="";
                            int packetCounter=0;
                            int dataLen=0;
                            int partCounter=0;
                            std::string part=std::to_string(partCounter);
                            int joined=0;
                            std::cout<<"FileCreated"<<std::endl;
                            while(1)
                            {
                                std::ofstream out(filepath2+name+part);
                                while(joined<JOIN)
                                {
                                    char file[SIZE];
                                    bytes_recieved=SSL_read(ssl, file,SIZE);
                                    file[bytes_recieved]='\0';
                                    std::cout<<bytes_recieved<<std::endl;
                                    packetCounter++;
                                    for(int i=0;i<bytes_recieved && dataLen<size;i++)
                                    {
                                        data+=file[i];
                                        dataLen++;
                                    }
                                    out << data;
                                    data="";
                                    joined++;
                                    std::cout<<"recieved "<<packetCounter<<std::endl;
                                    SSL_write(ssl, msg,4);
                                    std::cout<<"conf sent\n";    
                                    if(/*bytes_recieved<=0*/ dataLen==size)
                                    {
                                        std::cout<<"breaking now"<<std::endl;
                                        out.close();
                                        goto NEXT2;
                                    }
                                }
                                std::cout<<"Out of loop\n";
                                out.close();
                                joined=0;
                                partCounter++;
                                part=std::to_string(partCounter);
                            }
                            NEXT2:std::cout<<"file sent"<<std::endl;
                            fileCount++;
                        }
                        break;
                    }
                case 14 : // File transfer from client to server case 1 no path returned
                    { 
                        char msg[4]; //confirmation message
                        msg[4]='\0';
                        msg[0]='1';
                        char len[20]; //receiving the size of the file location
                        bytes_recieved=SSL_read(ssl, len,20);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        std::cout<<size<<std::endl;
                        char filename[size];//receiving the file location 
                        bytes_recieved=SSL_read(ssl,filename,size);
                        filename[bytes_recieved]='\0';
                        std::cout<<ToStr(filename)<<std::endl;
                        std::string name=FileName(ToStr(filename)); //extracting file name from the location
                        std::string filepath=ToStr(filename).substr(0,strlen(filename)-name.size()); //directory
                        std::cout<<"Filepath:"<<filepath<<std::endl;
                        std::cout<<"Filename:"<<name<<std::endl;
                        boost::filesystem::path dir(filepath); //creating the directory if it does not exist
                        if(!(boost::filesystem::exists(dir)))
                        {
                            std::cout<<"Directory Doesn't Exists"<<std::endl;
                            if (boost::filesystem::create_directories(dir))
                                std::cout << "Directory Successfully Created !" << std::endl;
                        }

                        bytes_recieved=SSL_read(ssl, len,20); //receiving the size of the file
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        std::cout<<size<<std::endl;
                        
                        std::string data=""; //data which will be written in the file
                        int packetCounter=0; //number of packets that are received
                        int dataLen=0; //Length of the file which has been received

                        std::ofstream out(filepath+name); //associating an object ofstream
                        std::cout<<"FileCreated"<<std::endl;

                        while(1)
                        {
                            char file[SIZE]; //receiving the file in chunks of 100 KB
                            bytes_recieved=SSL_read(ssl, file,SIZE);
                            file[bytes_recieved]='\0';
                            std::cout<<bytes_recieved<<std::endl;
                            packetCounter++;
                            for(int i=0;i<bytes_recieved && dataLen<size;i++)
                            {
                                data+=file[i];
                                dataLen++;
                            }
                            out << data; //writing data into the file
                            data="";
                            std::cout<<"recieved "<<packetCounter<<std::endl;
                            SSL_write(ssl, msg,4); //sending confirmation
                            std::cout<<"conf sent\n";    
                            if(/*bytes_recieved<=0*/ dataLen==size)
                            {
                                std::cout<<"breaking now"<<std::endl;
                                out.close();
                                break;
                            }
                            
                        }
                        std::cout<<"Out of loop\n";
                        out.close(); //closing the ofstream object
                        std::cout<<"file sent"<<std::endl;
                        break;
                    }
                case 15: //Get server files path of a user.
                    {
                        char len[20]; //receiving the length of the username
                        bytes_recieved=SSL_read(ssl, len,20);
                        len[bytes_recieved]='\0';
                        size=atoll(len);
                        std::cout<<size<<std::endl;
                        char filename[size]; //receiving the username
                        bytes_recieved=SSL_read(ssl,filename,size);
                        filename[bytes_recieved]='\0';
                        std::string name=FileName(ToStr(filename));
                        std::cout<<name<<std::endl;
                        //getting all the files in the folder of the given username
                        std::vector<std::string> files=GetFiles("/home/skipper/Desktop/DeadDropServer/"+name+"/");
                        //converting it into format /username/.temp/...
                        for(int i=0;i<files.size();i++)
                        {
                            std::string mp="/home/skipper/Desktop/DeadDropServer";
                            files[i]=files[i].substr(mp.size());
                            int j=0;
                            int k=0;
                            while(j<2)
                            {
                                if(files[i][k]=='/')  
                                    j++;
                                k++;
                            }
                            files[i].insert(k,".temp/");
                            std::cout<<files[i]<<std::endl;
                        }
                        //writing the strings in the file serverfiles.txt
                        std::ofstream outfile("/home/skipper/Desktop/DeadDropServer/"+name+"/.data/serverfiles.txt");
                        int index;
                        for(index=0;index<files.size();index++)
                        {
                            std::cout<<files[index]<<std::endl;
                            outfile<<files[index]<<"\n";
                        }
                        //closing the file
                        outfile.close();
                        std::cout<<"Done"<<std::endl;
                        break;
                    }
                default:
                    {
                        break;
                    }
            }
            if(quit)
            {
                break;
            }
        }
    }
    if(acceptID>-1)
        std::cout<<"Ending connection with "<<acceptID<<std::endl;
}


//The main server function
//It accepts IP Address(for displaying) and port number through which all clients are served
//Setups the sockets and waits for connections
int servermain(int argc, char** argv)
{
    if(argc<3)
    {
        std::cout<<"Error. Usage: ./tserver ip portnumber\n";
    }
    else
    {
        if(!isRoot()) //running it as root is required for certificate files
        {
            printf("This program must be run as root/sudo user!!");
            exit(0);
        }

        ctx=InitSSL(); //Initializing OpenSSL

        base.LoadFromFile("Database.txt"); //Loading database file containing username and password (enctrypted)

        int status;                      // Contains the status of the server
        int bindStatus;                  // Contains the status of the socket bind
        
        memset(&host_info, 0, sizeof host_info);

        std::cout << "Setting up the structures..."  << std::endl;
    
        host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
        host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP.
        host_info.ai_flags = AI_PASSIVE;     // IP Wildcard
    
        status = getaddrinfo(NULL, argv[2], &host_info, &host_info_list); //getting address info
        if (status != 0)  
            std::cout << "Getaddrinfo error" << gai_strerror(status)<<std::endl ;
    
        std::cout << "Creating a socket..."  << std::endl;
        
        // Getting info on the server
        sockID = socket(host_info_list->ai_family, host_info_list->ai_socktype,host_info_list->ai_protocol); 
        if (sockID == -1)  
            std::cout << "Socket error \n" ;

        std::cout << "Binding socket..."  << std::endl;
        
        int buffs=BUFFSIZE; //Setting the maximum size of the buffer
        setsockopt(sockID, SOL_SOCKET, SO_RCVBUF, &buffs, sizeof(buffs));                   // Setting the maximum buffer size of the sockets
        status = setsockopt(sockID, SOL_SOCKET, SO_REUSEPORT, &bindStatus, sizeof(int));    // Reusuing the port if already in use
        status = bind(sockID, host_info_list->ai_addr, host_info_list->ai_addrlen);         // Binding socket
        if (status == -1)                                                                   // Checking status        
        {
            std::cout<<"Reuse port Error : "<< strerror(errno)<<std::endl;
            close(sockID);                                                                  // Closing and opening the socket again.
            sockID = socket(host_info_list->ai_family, host_info_list->ai_socktype,host_info_list->ai_protocol);
            std::cout << "Binding socket again..."  << std::endl;
            setsockopt(sockID, SOL_SOCKET, SO_REUSEPORT, &bindStatus, sizeof(int));
            status=bind(sockID, host_info_list->ai_addr, host_info_list->ai_addrlen);
            std::cout<<status<<std::endl;
        }

        //creating a thread of for input
        pthread_t inputThread;
        pthread_create(&inputThread,NULL,Input,NULL);
        
        //listening for connections
        status =  listen(sockID, 5);
        if (status == -1)  
            std::cout << "Listen error" << std::endl ;

        uint32_t htonl(uint32_t hostlong);

        std::vector<pthread_t> threads= std::vector<pthread_t>(THREADS);              /* get new SSL state with context */
        int threadCount=0; //number of threads. Each thread corresponds to a new client
        while(!closeServer)
        {
            long id;
            struct sockaddr_storage their_addr;
            socklen_t addr_size = sizeof(their_addr);
            std::cout<<"Waiting for more clients..."<<std::endl;
            // Accepting a new connection and running the ClientService on a new thread
            id = accept(sockID, (struct sockaddr *)&their_addr, &addr_size);
            pthread_create(&threads[threadCount],NULL,ClientService,(void *)id);
            threadCount=(threadCount+1)%THREADS;
        }
        std::cout<<"All clients served\n";
        pthread_exit(NULL);
    }
    std::cout<<"Done!\n";
    return 0;
}
