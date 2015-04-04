#ifndef UDP_H
#define UDP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include "port.h"
#include <unistd.h>  
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <iostream>
#include <fstream>
#include <vector>
#include <pthread.h>
#include <math.h>
#include <algorithm>
#include <queue>    

#define BUFSIZE 50000



bool IsBaap();
std::string ToStr(char* arr);
int GetNumPlayers();
void AddPlayers(char players []);
int LengthNum(long long num);
int FindIndex(long long ip);
void *SendMessage(void* id);
char* ToArr(std::string str); 
void SendMessageToAll(std::string message);
void* RemovePlayer(void* input);
void* OutMessage(void* input);
int networkmain(int argc, char** argv);

#endif