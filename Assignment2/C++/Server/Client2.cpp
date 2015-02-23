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



std::string ToStr(char* arr)  //Convert array of characters to string
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

char* ToArr(std::string str)  //Convert string to array of character
{
    char* ans=new char[str.size()];
    for(int i=0;i<str.size();i++)
    {
        ans[i]=str[i];
    }
    return ans;
}
int ExecuteInstruction(Instruction ins)
{
    // 0 is no change,
    // 1 is newer modification client,
    // 2 is newer modification server, 
    // 3 is new client file, 
    // 4 is new server file,
    // 5 is delete file on user
    // 6 is remove file from server
    // 7 is UserLogin 
    // 8 is New user
    // 9 is user exists
    // 10 is exit
    // 11 is GetServerFiles
    std::string temp;
    int bytes_recieved;
    int bytes_sent;
    if(ins.modification==3)
        ins.modification=1;
    if(ins.modification==4)
        ins.modification=2;

    char num[2];
    sprintf(num,"%lld",(long long)ins.modification);
    bytes_sent=SSL_write(ssl, num,2);
    switch(ins.modification)
    {
        case 0:
            {
                // #ignore
                return 1;
            }
        case 8: // Add user
            {
                std::cout<<"Username\n";
                temp=ins.data1;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp.size());
                char* msg1=ToArr(temp);
                std::cout<<temp.size()<<"   "<<strlen(msg1)<<std::endl;
                bytes_sent=SSL_write(ssl, size1,20);
                bytes_sent=SSL_write(ssl,msg1,temp.size());
                std::cout<<"Password\n";
                temp=ins.data2;
                char size2[20];
                sprintf(size2,"%lld",(long long)temp.size());
                char* msg2=ToArr(temp);
                bytes_sent=SSL_write(ssl, size2,20);
                bytes_sent=SSL_write(ssl,msg2,temp.size());
                std::cout<<"User Successfully added!\n";
                return 1;
            }
        case 7: // Login
            {
                std::cout<<"Username\n";
                temp=ins.data1;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp.size());
                char* msg1=ToArr(temp);
                bytes_sent=SSL_write(ssl, size1,20);
                bytes_sent=SSL_write(ssl,msg1,temp.size());
                std::cout<<"Password\n";
                temp=ins.data2;
                char size2[20];
                sprintf(size2,"%lld",(long long)temp.size());
                char* msg2=ToArr(temp);
                bytes_sent=SSL_write(ssl, size2,20);
                bytes_sent=SSL_write(ssl,msg2,temp.size());
                char msg3[1];
                bytes_recieved=SSL_read(ssl,msg3,1);
                msg3[bytes_recieved]='\0';
                if(msg3[0]=='1')
                {
                    std::cout<<"Successfully\n";
                    return 1;
                }
                else
                {
                    std::cout<<"Sorry. Please try again\n";
                    return 0;
                }
            }
        case 9: //User exists
            {
                std::cout<<"Enter Username\n";
                temp=ins.data1;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp.size());
                char* msg1=ToArr(temp);
                bytes_sent=SSL_write(ssl, size1,20);
                bytes_sent=SSL_write(ssl,msg1,temp.size());
                char msg3[1];
                bytes_recieved=SSL_read(ssl,msg3,1);
                msg3[bytes_recieved]='\0';
                if(msg3[0]=='1')
                {
                    std::cout<<"User Exists\n";
                    return 1;
                }
                else
                {
                    std::cout<<"User Does not exist\n";
                    return 0;
                }
            }
        case 1: //client to server
            {
                std::cout<<"Client address\n";
                std::string temp1=ins.data1;
                std::cout<<"Server address\n";
                std::string temp2=ins.data2;

                //filereading
                // TODO : Read files in chunks
                std::ifstream ifs(temp1, std::ios::binary|std::ios::ate);
                if(!ifs.is_open())
                    return 0;
                std::ifstream::pos_type pos = ifs.tellg();
                std::vector<char>  ans(pos);
                ifs.seekg(0, std::ios::beg);
                ifs.read(&ans[0], pos);
                ifs.close();

                char msg[4];
                char size1[20];
                sprintf(size1,"%lld",(long long)temp2.size());
                bytes_sent=SSL_write(ssl, size1,20);
                char* filepath=ToArr(temp2);
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
                return 1;
            }
        case 2: //server to client
            {
                std::cout<<"Enter client address\n";
                std::string temp1=ins.data1;
                std::cout<<"Enter server address\n";
                std::string temp2=ins.data2;

                char msg[4];
                msg[0]='1';
                char len[20];
                char size1[20];
                sprintf(size1,"%lld",(long long)temp2.size());
                bytes_sent=SSL_write(ssl, size1,20);
                char* filepath=ToArr(temp2);
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
                return 1;
            }
        case 5: //Delete file on user.
            {
                boost::filesystem::wpath file(ins.data1);
                if(boost::filesystem::exists(file))
                    boost::filesystem::remove(file);
                return 1;
            }
        case 6: //Delete file on server.
            {
                std::cout<<"Server address\n";
                std::string temp2=ins.data1;
                char size1[20];
                sprintf(size1,"%lld",(long long)temp2.size());
                bytes_sent=SSL_write(ssl, size1,20);
                char* filepath=ToArr(temp2);
                bytes_sent=SSL_write(ssl,filepath,temp2.size());
                return 1;
            }
        case 10: // quit
            {
                freeaddrinfo(host_info_list);
                close(sockID);
                SSL_free(ssl);
                return 1;
            }
        case 11: // get serverlist
            {
                std::cout<<"Client address\n";
                std::string temp1=ins.data1; // including '/'
                std::cout<<"Server address\n";
                std::string temp2=ins.data2; // including '/'
                std::string temp3=temp1;

                char msg[4];
                char size1[20];
                sprintf(size1,"%lld",(long long)temp2.size());
                bytes_sent=SSL_write(ssl, size1,20);
                char* filepath=ToArr(temp2);
                bytes_sent=SSL_write(ssl,filepath,temp2.size());

                int fileCount=0;
                while(fileCount<3)
                {
                    bytes_recieved=SSL_read(ssl, len,20);    
                    len[bytes_recieved]='\0';
                    long long size=atoll(len);
                    std::cout<<size<<std::endl;
                    
                    std::string data="";
                    int packetCounter=0;
                    int dataLen=0;
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
                    fileCount++;
                }

            }
        default:
            {
                return 0;
            }
    }
    
}