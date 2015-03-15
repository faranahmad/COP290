#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "port.h"
#include <unistd.h>  
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <iostream>
#define BUFSIZE 2048

int main(int argc, char **argv)
{
	struct sockaddr_in myaddr;	
	struct sockaddr_in remaddr;	
	socklen_t addrlen = sizeof(remaddr);	
	int recvlen;			
	int fd;				
	int msgcnt = 0;		
	char buf[BUFSIZE];	

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		perror("cannot create socket\n");
		return 0;
	}

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(SERVICE_PORT);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) 
	{
		perror("bind failed");
		return 0;
	}

	for (;;)//infinite loop
	 { 
		printf("waiting on port %d\n", SERVICE_PORT);
		recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		if (recvlen > 0) {
			buf[recvlen] = 0;
			printf("received message: \"%s\" (%d bytes)\n", buf, recvlen);
		}
		else
			printf("uh oh - something went wrong!\n");
		int t;
		std::cin>>t;
		sprintf(buf, "ack %d", t);

		printf("sending response \"%s\"\n", buf);

		if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, addrlen) < 0)
			perror("sendto");
	}
}
