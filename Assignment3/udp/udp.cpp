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

#define PORT 5555
#define BUFSIZE 50000
std::vector< std::pair<long long,long long> > IPdata;
std::vector<std::string> Instructions;

struct IPMessage {
    long long ip;
    char* message;
    int sockid;
};

void AddPlayers(char players [])
{
	std::string s;
	for(int i=2;players[i]!=0;i++)
	{
		if(players[i]!=' ' && players[i]!='\n')
			s=s+players[i];
		else
		{	
			const char * ipchar = s.c_str();
			std::pair<long long,long long> p;
			p.first=atoll(ipchar);
			p.second=0;
			std::cout<<p.first<<std::endl;
			IPdata.push_back(p);
			s="";
		}
	}
}

int LengthNum(long long num)
{
	int ans=0;
	while(num>0)
	{
		num=num/10;
		ans++;
	}
	return ans;
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

void *SendMessage(void* id)
{
    IPMessage  *pa= (IPMessage *)id;
    long long ip=pa->ip;
    char * message=pa->message;
    int sockid=pa->sockid;

    struct sockaddr_in remaddr;
    int fd, i, slen=sizeof(remaddr);

    memset((char *) &remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_addr.s_addr=htonl(ip);
	remaddr.sin_port = htons(SERVICE_PORT);
	int bytes_sent=sendto(sockid, message, strlen(message), 0, (struct sockaddr *)&remaddr, slen);
	if(bytes_sent<=0)
	{
		bytes_sent=sendto(sockid, message, strlen(message), 0, (struct sockaddr *)&remaddr, slen);
		if(bytes_sent<0)
		{
			std::cout<<"Player disconnected:"<<ip<<std::endl;
		}
	} //TODO:Remove the the disconnected player
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
	if (setsockopt(sockid, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) 
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

	std::pair<long long,long long> myself;
	myself.first=(long long)(myaddr.sin_addr.s_addr);
	myself.second=0;
	IPdata.push_back(myself);

	memset((char *) &remaddr, 0, sizeof(remaddr));
	
	if(argc>1)
	{
		std::cout<<"sending case 0\n"<<std::endl;
		char sendmsg[BUFSIZE];
		remaddr.sin_family = AF_INET;
		remaddr.sin_port = htons(SERVICE_PORT);
		if (inet_aton(argv[1], &remaddr.sin_addr)==0) 
		{
			fprintf(stderr, "inet_aton() failed\n");
			exit(1);
		}

		std::pair<long long,long long> server;
		server.first=(long long)(remaddr.sin_addr.s_addr);
		server.second=0;
		IPdata.push_back(server);

		sendmsg[0]='0';
		sendmsg[1]=' ';
		int firstMsg=0;
		for(;firstMsg<ipadr.size();firstMsg++)
		{
			sendmsg[firstMsg+2]=ipadr[firstMsg];
		}
		sendmsg[firstMsg+2]='\n';
	
		int slen=sizeof(remaddr);
		if (sendto(sockid, sendmsg, strlen(sendmsg), 0, (struct sockaddr *)&remaddr, slen)==-1) 
		{
			perror("Sorry, player not found!\nMake sure you are connected to the network");
			exit(1);
		}

		socklen_t blen=(socklen_t)slen;
		int recvlen = recvfrom(sockid, recvmsg, BUFSIZE, 0, (struct sockaddr *)&remaddr, &blen);
    	if (recvlen >= 0) 
    	{
    	    recvmsg[recvlen] = 0;
    	    if(sendmsg[0]=='1')
    	    	AddPlayers(recvmsg);
    	}
	}

	while(true)
	{	
		socklen_t addrlen=(socklen_t)(sizeof(remaddr));
		std::cout<<"Awaiting data...\n";
		START:int recvlen = recvfrom(sockid,recvmsg , BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		if (recvlen > 0) 
		{
			recvmsg[recvlen] = 0;
			switch(recvmsg[0])
			{
				case '0':
				{	
					std::cout<<"case 0\n"<<std::cout;
					std::pair<long long,long long> p;
					p.first=(long long)remaddr.sin_addr.s_addr;
					p.second=0;
					IPdata.push_back(p);
					char sendmsg[BUFSIZE];
					sendmsg[0]='1';
					sendmsg[1]=' ';
					int j=2;
					for(int i=0;i<IPdata.size();i++)
					{
						char temp[20];
                        sprintf(temp,"%lld",IPdata[i].first);
                        int lenll=LengthNum(IPdata[i].first);
                        for(int k=0;k<lenll;k++)
                        {
                        	sendmsg[j]=temp[k];
                        	j++;
                        }
                        sendmsg[j]=' ';
					}
					sendmsg[j]='\n';
					sendmsg[j+1]='\0';
					int slen=sizeof(remaddr);
					sendto(sockid, sendmsg, strlen(sendmsg), 0, (struct sockaddr *)&remaddr, slen);
			        std::vector<pthread_t> threads= std::vector<pthread_t>(IPdata.size()-2);
			        
			        IPMessage im;
			        
			        char temp[20];
			        sprintf(temp,"%lld",(long long)remaddr.sin_addr.s_addr);
			        char* sendmsg2;
			        sendmsg2[0]='2';
			        sendmsg2[1]=' ';
			        j=2;
			        for(int k=0;k<LengthNum((long long)remaddr.sin_addr.s_addr);k++)
			        {
			        	sendmsg2[j]=temp[k];
			        	j++;
			        }
			        sendmsg2[j]='\n';
			        sendmsg2[j+1]='\0';
			        im.message=sendmsg2;
			        im.sockid=sockid;
			        std::cout<<"sendmsg2:"<<ToStr(sendmsg2)<<std::endl;
			        for(int i=0;i<threads.size();i++)
			        {
			        	im.ip=IPdata[i+1].first;
			        	pthread_create(&threads[i],NULL,SendMessage,&im);
			        }
			        break;
				}
				case '2':
				{
	    	    	AddPlayers(recvmsg);
					break;
				}
				default:
				{	
					std::cout<<ToStr(recvmsg)<<std::endl;
					Instructions.push_back(ToStr(recvmsg));
					break;
				}
			}
		}
		else
		{	
			goto START;
			// printf("You have been disconnected\n");
			// exit(0);
		}
	}

}