
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

#define BUFLEN 2048
#define MSGS 5

int main(void)
{
	struct sockaddr_in myaddr, remaddr;
	int fd, i, slen=sizeof(remaddr);
	char buf[BUFLEN];	
	int recvlen;		
	char *server = "127.0.0.1";	

	if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		printf("socket created\n");

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(0);

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
		sprintf(buf, "This is packet %d", t);
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
	}
	close(fd);
	return 0;
}
