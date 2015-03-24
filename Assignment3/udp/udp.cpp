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

vector< pair<long long,long long> > IPdata;

int main()
{
	system ("ifconfig | grep 'inet addr:' | grep -v '127.0.0.1' | awk '{print $2}' | cut -f2 -d: > .ip.txt");
	std::ifstream ip4(".ip.txt");
	std::string ipadr;
	std::getline(ip4,ipadr);
	std::cout<<ipadr<<std::endl;
	system("rm -rf .ip.txt");
	ip4.close();

	struct sockaddr_in myaddr, remaddr;
	int sockid=socket(AF_INET, SOCK_DGRAM, 0);

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	// myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(0);
	const char * ipchar = ipadr.c_str();
	inet_aton(ipchar,&myaddr.sin_addr);
	if (bind(sockid, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) 
	{
		perror("bind failed");
		return 0;
	}       
	pair myself;
	myself.first=(long long)(myaddr.sin_addr.s_addr)
}