
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

#define BUFLEN 2048
#define MSGS 5

int main(void)
{
	system ("ifconfig | grep 'inet addr:' | grep -v '127.0.0.1' | awk '{print $2}' | cut -f2 -d: > .ip.txt");
	std::ifstream ip4(".ip.txt");
	std::string ipadr;
	std::getline(ip4,ipadr);
	std::cout<<ipadr<<std::endl;
	system("rm -rf .ip.txt");
	ip4.close();

	
	struct sockaddr_in myaddr, remaddr,dude;
	int fd, i, slen=sizeof(remaddr);
	char buf[BUFLEN];	
	int recvlen;		
	char *server = "10.192.5.249";	

	if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		printf("socket created\n");

	// struct timeval tv;
	// tv.tv_sec = 0;
	// tv.tv_usec = 100000;
	// if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
	//     perror("Error timeout");
	// }
struct sockaddr_in myaddr, remaddr
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	// myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(0);
	const char * c = ipadr.c_str();
	inet_aton(c,&myaddr.sin_addr);
	std::cout<<(long long)myaddr.sin_addr.s_addr<<std::endl;
	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) 
	{
		perror("bind failed");
		return 0;
	}       

	memset((char *) &remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_port = htons(SERVICE_PORT);
	if (inet_aton(server, &remaddr.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	for (i=0; i < MSGS; i++) 
	{
		printf("Sending packet %d to %s port %d\n", i, server, SERVICE_PORT);
		int t;
		std::cin>>t;
		sprintf(buf, "This isaddrlen packet %d", t);
		int arr[3];
		arr[5]=1;
		if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, slen)==-1) 
		{
			perror("sendto");
			exit(1);
		}
		socklen_t blen=(socklen_t)slen;
		recvlen = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *)&remaddr, &blen);
                if (recvlen >= 0) 
                {
                        buf[recvlen] = 0;
                        printf("received message: \"%s\"\n", buf);
                }
std::cout << "Connected to: " << (long long)(remaddr.sin_addr.s_addr) << std::endl;
	}
	close(fd);
	return 0;
}
