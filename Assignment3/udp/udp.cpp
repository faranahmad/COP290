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

#define PORT 5555
#define BUFSIZE 50000
vector< pair<long long,long long> > IPdata;
vector<std::string> Instructions;

void AddPlayers(char players [])
{
	string s;
	struct sockaddr_in addr;
	for(int i=2;i<strlen(players);i++)
	{
		if(players[i]!=' ')
			s=s+players[i];
		else
		{	
			const char * ipchar = s.c_str();
			inet_aton(ipchar,&addr.sin_addr);
			pair p;
			p.first=(long long)(addr.sin_addr.s_addr);
			p.second=0;
			IPdata.push_back(p);
			s="";
		}
	}
}

std::string ToStr(char* arr)  
{
    std::string ans="";
    for(int i=0;i<strlen(arr)&&arr[i]!='\0';i++)
    {
        ans+=arr[i];
    }
    return ans;
}

int main(int argc, char** argv)
{
	system ("ifconfig | grep 'inet addr:' | grep -v '127.0.0.1' | awk '{print $2}' | cut -f2 -d: > .ip.txt");
	std::ifstream ip4(".ip.txt");
	std::string ipadr;
	std::getline(ip4,ipadr);
	std::cout<<ipadr<<std::endl;
	system("rm -rf .ip.txt");
	ip4.close();

	char recvmsg[BUFSIZE];
	struct sockaddr_in myaddr, remaddr;
	int sockid=socket(AF_INET, SOCK_DGRAM, 0);
	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 100000;
	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) 
	{
	    perror("Error timeout");
	}

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(0);
	const char * ipchar = ipadr.c_str();
	inet_aton(ipchar,&myaddr.sin_addr);
	if (bind(sockid, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) 
	{
		perror("bind failed");
		return 0;
	}    

	pair myself;
	myself.first=(long long)(myaddr.sin_addr.s_addr);
	myself.second=0;
	IPdata.push_back(myself);

	memset((char *) &remaddr, 0, sizeof(remaddr));
	
	if(argc>0)
	{
		char sendmsg[BUFSIZE];
		remaddr.sin_family = AF_INET;
		remaddr.sin_port = htons(SERVICE_PORT);
		if (inet_aton(argv[1], &remaddr.sin_addr)==0) 
		{
			fprintf(stderr, "inet_aton() failed\n");
			exit(1);
		}
		sendmsg[0]='0';
		sendmsg[1]=' ';
		int firstMsg=0;
		for(;firstMsg<ipadr.size();firstMsg++)
		{
			sendmsg[firstMsg+2]=ipadr[firstMsg];
		}
		sendmsg[firstMsg+2]='\n';
	
		printf("Connecting to %s port %d\n", server, SERVICE_PORT);

		int slen=sizeof(remaddr);
		if (sendto(sockid, sendmsg, strlen(send), 0, (struct sockaddr *)&remaddr, slen)==-1) 
		{
			perror("Sorry, player not found!\nMake sure you are connected to the network");
			exit(1);
		}

		socklen_t blen=(socklen_t)slen;
		recvlen = recvfrom(sockid, recvmsg, BUFSIZE, 0, (struct sockaddr *)&remaddr, &blen);
    	if (recvlen >= 0) 
    	{
    	    recvmsg[recvlen] = 0;
    	    AddPlayers(recvmsg);
    	}
	}

	while(true)
	{
		int recvlen = recvfrom(sockid,recvmsg , BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		if (recvlen > 0) 
		{
			recvmsg[recvlen] = 0;
			switch(recvmsg[0])
			{
				case '0':
				{

					break;
				}
				default:
				{
					Instructions.push_back(ToStr(recvmsg));
					break;
				}
			}
		}
		else
		{	
			printf("You have been disconnected\n");
			exit(0);
		}
	}



}