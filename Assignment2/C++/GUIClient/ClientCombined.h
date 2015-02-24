#ifndef CLIENTCOMBINED_H
#define CLIENTCOMBINED_H

#include "SyncManager.h"
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



SSL_CTX* IniTSSL(void);
void ShowCerts(SSL*);
std::string ToStr(char*);

std::string FileName(std::string);
char* ToArr(std::string);

int ExecuteInstruction(Instruction);

void CreateNewUser(std::string, std::string);

bool UserLogin(std::string, std::string);

bool CheckUserExists(std::string);

void PerformSync(SyncManager);

void DeleteFileServer(SyncManager , std::string);

void GetFileFromServer(SyncManager , std::string );

void DeleteFileClient(SyncManager , std::string );

void KeepOnlineOnly(SyncManager , std::string );

int clientmain(int argc, char *argv[]);


#endif